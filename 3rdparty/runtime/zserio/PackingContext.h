#ifndef ZSERIO_PACKING_CONTEXT_H_INC
#define ZSERIO_PACKING_CONTEXT_H_INC

#include <vector>
#include <type_traits>

#include "zserio/Types.h"
#include "zserio/OptionalHolder.h"

namespace zserio
{

namespace detail
{

// calculates bit length on delta provided as an absolute number
inline uint8_t absDeltaBitLength(uint64_t absDelta)
{
    uint8_t result = 0;
    while (absDelta > 0)
    {
        result++;
        absDelta >>= 1;
    }

    return result;
}

// calculates bit length, emulates Python bit_length to keep same logic
template <typename T>
uint8_t calcBitLength(T lhs, T rhs)
{
    const uint64_t absDelta = lhs > rhs
            ? static_cast<uint64_t>(lhs) - static_cast<uint64_t>(rhs)
            : static_cast<uint64_t>(rhs) - static_cast<uint64_t>(lhs);

    return absDeltaBitLength(absDelta);
}

// calculates delta, doesn't check for possible int64_t overflow since it's used only in cases where it's
// already known that overflow cannot occur
template <typename T>
int64_t calcUncheckedDelta(T lhs, uint64_t rhs)
{
    return static_cast<int64_t>(static_cast<uint64_t>(lhs) - rhs);
}

} // namespace detail

/**
 * Context for delta packing created for each packable field.
 *
 * Contexts are always newly created for each array operation (bitSizeOfPacked, initializeOffsetsPacked,
 * readPacked, writePacked). They must be initialized at first via calling the init method for each packable
 * element present in the array. After the full initialization, only a single method (bitSizeOf, read, write)
 * can be repeatedly called for exactly the same sequence of packable elements.
 *
 * Note that *Descriptor methods doesn't change context's internal state and can be called as needed. They are
 * designed to be called once for each context before the actual operation.
 */
class DeltaContext
{
public:
    /**
     * Resets the context to it's initial state.
     *
     * Reset it needed to allow to reuse the whole context tree and thus prevent memory fragmentation
     * mainly during reading.
     */
    void reset()
    {
        m_isPacked = false;
        m_maxBitNumber = 0;
        m_previousElement.reset();
        m_processingStarted = false;
    }

    /**
     * Calls the initialization step for a single element.
     *
     * \param element Current element.
     */
    template <typename ELEMENT_TYPE>
    void init(ELEMENT_TYPE element)
    {
        if (!m_previousElement.hasValue())
        {
            m_previousElement = static_cast<uint64_t>(element);
        }
        else
        {
            if (m_maxBitNumber <= MAX_BIT_NUMBER_LIMIT)
                m_isPacked = true;
            const auto previousElement = static_cast<ELEMENT_TYPE>(m_previousElement.value());
            const uint8_t maxBitNumber = detail::calcBitLength(element, previousElement);
            if (maxBitNumber > m_maxBitNumber)
            {
                m_maxBitNumber = maxBitNumber;
                if (m_maxBitNumber > MAX_BIT_NUMBER_LIMIT)
                    m_isPacked = false;
            }
            m_previousElement = static_cast<uint64_t>(element);
        }
    }

    /**
     * Returns length of the descriptor stored in the bit stream in bits.
     *
     * \return Length of the descriptor stored in the bit stream in bits.
     */
    size_t bitSizeOfDescriptor() const
    {
        if (m_isPacked)
            return 1 + MAX_BIT_NUMBER_BITS;
        else
            return 1;
    }

    /**
     * Returns length of the packed element stored in the bit stream in bits.
     *
     * \param arrayTraits Standard array traits.
     * \param bitPosition Current bit stream position.
     * \param element Value of the current element.
     *
     * \return Length of the packed element stored in the bit stream in bits.
     */
    template <typename ARRAY_TRAITS>
    size_t bitSizeOf(const ARRAY_TRAITS& arrayTraits, size_t bitPosition,
            typename ARRAY_TRAITS::ElementType element)
    {
        if (!m_processingStarted || !m_isPacked)
        {
            m_processingStarted = true;
            return arrayTraits.bitSizeOf(bitPosition, element);
        }
        else
        {
            return m_maxBitNumber + (m_maxBitNumber > 0 ? 1 : 0);
        }
    }

    /**
     * Reads the delta packing descriptor from the bit stream. Called for all contexts before the first element
     * is read.
     *
     * \param in Bit stream reader.
     */
    void readDescriptor(BitStreamReader& in)
    {
        m_isPacked = in.readBool();
        if (m_isPacked)
            m_maxBitNumber = static_cast<uint8_t>(in.readBits(MAX_BIT_NUMBER_BITS));
    }

    /**
     * Reads a packed element from the bit stream.
     *
     * \param arrayTraits Standard array traits.
     * \param in Bit stream reader.
     *
     * \return Value of the packed element.
     */
    template <typename ARRAY_TRAITS>
    typename ARRAY_TRAITS::ElementType read(const ARRAY_TRAITS& arrayTraits, BitStreamReader& in)
    {
        if (!m_processingStarted || !m_isPacked)
        {
            m_processingStarted = true;
            const auto element = arrayTraits.read(in);
            m_previousElement = static_cast<uint64_t>(element);
            return element;
        }
        else
        {
            if (m_maxBitNumber > 0)
            {
                const int64_t delta = in.readSignedBits64(m_maxBitNumber + 1);
                const typename ARRAY_TRAITS::ElementType element =
                        static_cast<typename ARRAY_TRAITS::ElementType>(
                                m_previousElement.value() + static_cast<uint64_t>(delta));
                m_previousElement = static_cast<uint64_t>(element);
            }

            return static_cast<typename ARRAY_TRAITS::ElementType>(m_previousElement.value());
        }
    }

    /**
     * Writes the delta packing descriptor to the bit stream. Called for all contexts before the first element
     * is written.
     *
     * \param out Bit stream writer.
     */
    void writeDescriptor(BitStreamWriter& out) const
    {
        out.writeBool(m_isPacked);
        if (m_isPacked)
            out.writeBits(m_maxBitNumber, MAX_BIT_NUMBER_BITS);
    }

    /**
     * Writes the packed element to the bit stream.
     *
     * \param arrayTraits Standard array traits.
     * \param out Bit stream writer.
     * \param element Value of the current element.
     */
    template <typename ARRAY_TRAITS>
    void write(const ARRAY_TRAITS& arrayTraits, BitStreamWriter& out,
            typename ARRAY_TRAITS::ElementType element)
    {
        if (!m_processingStarted || !m_isPacked)
        {
            m_processingStarted = true;
            m_previousElement = static_cast<uint64_t>(element);
            arrayTraits.write(out, element);
        }
        else
        {
            if (m_maxBitNumber > 0)
            {
                // it's already checked in the init phase that the delta will fit into int64_t
                const int64_t delta = detail::calcUncheckedDelta(element, m_previousElement.value());
                out.writeSignedBits64(delta, m_maxBitNumber + 1);
                m_previousElement = static_cast<uint64_t>(element);
            }
        }
    }

private:
    static const uint8_t MAX_BIT_NUMBER_BITS = 6;
    static const uint8_t MAX_BIT_NUMBER_LIMIT = 62;

    bool m_isPacked = false;
    uint8_t m_maxBitNumber = 0;
    InplaceOptionalHolder<uint64_t> m_previousElement;
    bool m_processingStarted = false;
};

/**
 * Packing context node.
 *
 * This class is used to handle a tree of contexts created by appropriate PackedArrayTraits.
 * For built-in packable types only a single context is kept. However for Zserio objects, a tree
 * of all packable fields is created recursively.
 *
 * When the context node has no children and no context, then it's so called dummy context which is used
 * for unpackable fields or nested arrays.
 */
template <typename ALLOC = std::allocator<uint8_t>>
class BasicPackingContextNode
{
public:
    /** Allocator type. */
    using allocator_type = RebindAlloc<ALLOC, BasicPackingContextNode>;
    /** Typedef for vector of children. */
    using Children = std::vector<BasicPackingContextNode, allocator_type>;

    /**
     * Constructor.
     *
     * \param allocator Allocator to use for allocation of the vector of children.
     */
    explicit BasicPackingContextNode(const ALLOC& allocator)
    :   m_children(allocator)
    {}

    /**
     * Creates a new child.
     *
     * \return The child which was just created.
     */
    BasicPackingContextNode& createChild()
    {
        m_children.emplace_back(m_children.get_allocator());
        return m_children.back();
    }

    /**
     * Gets list of children of the current node.
     *
     * \return List of children.
     */
    Children& getChildren()
    {
        return m_children;
    }

    /**
     * Creates a new packing context within the current node.
     */
    void createContext()
    {
        m_context = DeltaContext();
    }

    /**
     * Gets whether the current node has a packing context.
     *
     * \return True when the current node has assigned a context, false otherwise.
     */
    bool hasContext() const
    {
        return m_context.hasValue();
    }

    /**
     * Gets packing context assigned to this node.
     *
     * Can be called only when the context exists!
     *
     * \return Packing context.
     */
    DeltaContext& getContext()
    {
        return m_context.value();
    }

private:
    Children m_children;
    InplaceOptionalHolder<DeltaContext> m_context;
};

using PackingContextNode = BasicPackingContextNode<>;

} // namespace zserio

#endif // ZSERIO_PACKING_CONTEXT_H_INC
