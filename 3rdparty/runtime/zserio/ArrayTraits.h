#ifndef ZSERIO_ARRAY_TRAITS_H_INC
#define ZSERIO_ARRAY_TRAITS_H_INC

#include <type_traits>
#include <vector>
#include <string>

#include "zserio/BitStreamWriter.h"
#include "zserio/BitStreamReader.h"
#include "zserio/BitPositionUtil.h"
#include "zserio/VarSizeUtil.h"
#include "zserio/PreWriteAction.h"
#include "zserio/BitSizeOfCalculator.h"
#include "zserio/Enums.h"

namespace zserio
{

namespace detail
{

template <typename T>
T read_bits(BitStreamReader& in, uint8_t numBits);

template <>
inline int8_t read_bits<int8_t>(BitStreamReader& in, uint8_t numBits)
{
    return static_cast<int8_t>(in.readSignedBits(numBits));
}

template <>
inline int16_t read_bits<int16_t>(BitStreamReader& in, uint8_t numBits)
{
    return static_cast<int16_t>(in.readSignedBits(numBits));
}

template <>
inline int32_t read_bits<int32_t>(BitStreamReader& in, uint8_t numBits)
{
    return in.readSignedBits(numBits);
}

template <>
inline int64_t read_bits<int64_t>(BitStreamReader& in, uint8_t numBits)
{
    return in.readSignedBits64(numBits);
}

template <>
inline uint8_t read_bits<uint8_t>(BitStreamReader& in, uint8_t numBits)
{
    return static_cast<uint8_t>(in.readBits(numBits));
}

template <>
inline uint16_t read_bits<uint16_t>(BitStreamReader& in, uint8_t numBits)
{
    return static_cast<uint16_t>(in.readBits(numBits));
}

template <>
inline uint32_t read_bits<uint32_t>(BitStreamReader& in, uint8_t numBits)
{
    return in.readBits(numBits);
}

template <>
inline uint64_t read_bits<uint64_t>(BitStreamReader& in, uint8_t numBits)
{
    return in.readBits64(numBits);
}

template <typename T>
void write_bits(BitStreamWriter& out, T value, uint8_t numBits);

template <>
inline void write_bits<int8_t>(BitStreamWriter& out, int8_t value, uint8_t numBits)
{
    out.writeSignedBits(static_cast<int32_t>(value), numBits);
}

template <>
inline void write_bits<int16_t>(BitStreamWriter& out, int16_t value, uint8_t numBits)
{
    out.writeSignedBits(static_cast<int32_t>(value), numBits);
}

template <>
inline void write_bits<int32_t>(BitStreamWriter& out, int32_t value, uint8_t numBits)
{
    out.writeSignedBits(value, numBits);
}

template <>
inline void write_bits<int64_t>(BitStreamWriter& out, int64_t value, uint8_t numBits)
{
    out.writeSignedBits64(value, numBits);
}

template <>
inline void write_bits<uint8_t>(BitStreamWriter& out, uint8_t value, uint8_t numBits)
{
    out.writeBits(static_cast<uint32_t>(value), numBits);
}

template <>
inline void write_bits<uint16_t>(BitStreamWriter& out, uint16_t value, uint8_t numBits)
{
    out.writeBits(static_cast<uint32_t>(value), numBits);
}

template <>
inline void write_bits<uint32_t>(BitStreamWriter& out, uint32_t value, uint8_t numBits)
{
    out.writeBits(value, numBits);
}

template <>
inline void write_bits<uint64_t>(BitStreamWriter& out, uint64_t value, uint8_t numBits)
{
    out.writeBits64(value, numBits);
}

} // namespace detail

/**
 * Array traits for bit field Zserio types (int:5, bit:5, etc...).
 */
template <typename T>
class BitFieldArrayTraits
{
public:
    /** Element type. */
    using ElementType = T;

    /**
     * Constructor.
     *
     * \param numBits Num bits of the array element.
     */
    explicit BitFieldArrayTraits(uint8_t numBits) :
            m_numBits(numBits)
    {}

    /**
     * Calculates bit size of the array element.
     *
     * \return Bit size of the array element.
     */
    size_t bitSizeOf() const
    {
        return m_numBits;
    }

    /**
     * Calculates bit size of the array element.
     *
     * \return Bit size of the array element.
     */
    size_t bitSizeOf(size_t, ElementType) const
    {
        return m_numBits;
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    size_t initializeOffsets(size_t bitPosition, ElementType) const
    {
        return bitPosition + m_numBits;
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    ElementType read(BitStreamReader& in) const
    {
        return detail::read_bits<T>(in, m_numBits);
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    void write(BitStreamWriter& out, ElementType element) const
    {
        detail::write_bits(out, element, m_numBits);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = true;

private:
    uint8_t m_numBits;
};

/**
 * Array traits for fixed integer Zserio types (int16, uint16, int32, uint32, etc...).
 */
template <typename T>
struct StdIntArrayTraits
{
    /** Element type. */
    using ElementType = T;

    /**
     * Calculates bit size of the array element.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf()
    {
        return NUM_BITS;
    }

    /**
     * Calculates bit size of the array element.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType)
    {
        return bitSizeOf();
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType)
    {
        return bitPosition + NUM_BITS;
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return detail::read_bits<T>(in, NUM_BITS);
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        detail::write_bits(out, element, NUM_BITS);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = true;

private:
    static const uint8_t NUM_BITS = sizeof(T) * 8;
};

/**
 * Array traits for variable integer Zserio types (varint16, varuint16, etc...).
 */
template <typename T>
struct VarIntNNArrayTraits;

/**
 * Array traits specialization for Zserio varint16 type.
 */
template <>
struct VarIntNNArrayTraits<int16_t>
{
    /** Element type. */
    using ElementType = int16_t;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType element)
    {
        return zserio::bitSizeOfVarInt16(element);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readVarInt16();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        out.writeVarInt16(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

/**
 * Array traits specialization for Zserio varint32 type.
 */
template <>
struct VarIntNNArrayTraits<int32_t>
{
    /** Element type. */
    using ElementType = int32_t;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType element)
    {
        return zserio::bitSizeOfVarInt32(element);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readVarInt32();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        out.writeVarInt32(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

/**
 * Array traits specialization for Zserio varint64 type.
 */
template <>
struct VarIntNNArrayTraits<int64_t>
{
    /** Element type. */
    using ElementType = int64_t;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType element)
    {
        return zserio::bitSizeOfVarInt64(element);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readVarInt64();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        out.writeVarInt64(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

/**
 * Array traits specialization for Zserio varuint16 type.
 */
template <>
struct VarIntNNArrayTraits<uint16_t>
{
    /** Element type. */
    using ElementType = uint16_t;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType element)
    {
        return zserio::bitSizeOfVarUInt16(element);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readVarUInt16();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        out.writeVarUInt16(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

/**
 * Array traits specialization for Zserio varuint32 type.
 */
template <>
struct VarIntNNArrayTraits<uint32_t>
{
    /** Element type. */
    using ElementType = uint32_t;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType element)
    {
        return zserio::bitSizeOfVarUInt32(element);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readVarUInt32();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        out.writeVarUInt32(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

/**
 * Array traits specialization for Zserio varuint64 type.
 */
template <>
struct VarIntNNArrayTraits<uint64_t>
{
    /** Element type. */
    using ElementType = uint64_t;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType element)
    {
        return zserio::bitSizeOfVarUInt64(element);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readVarUInt64();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        out.writeVarUInt64(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

/**
 * Array traits for big variable integer Zserio types (varint, varuint).
 */
template <typename T>
struct VarIntArrayTraits;

/**
 * Array traits specialization for Zserio varint type.
 */
template <>
struct VarIntArrayTraits<int64_t>
{
    /** Element type. */
    using ElementType = int64_t;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType element)
    {
        return zserio::bitSizeOfVarInt(element);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readVarInt();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        out.writeVarInt(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

/**
 * Array traits specialization for Zserio varuint type.
 */
template <>
struct VarIntArrayTraits<uint64_t>
{
    /** Element type. */
    using ElementType = uint64_t;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType element)
    {
        return zserio::bitSizeOfVarUInt(element);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readVarUInt();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        out.writeVarUInt(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

/**
 * Array traits specialization for Zserio varsize type.
 */
struct VarSizeArrayTraits
{
    /** Element type. */
    using ElementType = uint32_t;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType element)
    {
        return zserio::bitSizeOfVarSize(element);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readVarSize();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write
     */
    void write(BitStreamWriter& out, ElementType element) const
    {
        out.writeVarSize(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

/**
 * Array traits for Zserio float16 type.
 */
struct Float16ArrayTraits
{
    /** Element type. */
    using ElementType = float;

    /**
     * Calculates bit size of the array element.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf()
    {
        return 16;
    }

    /**
     * Calculates bit size of the array element.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType)
    {
        return bitSizeOf();
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readFloat16();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        out.writeFloat16(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = true;
};

/**
 * Array traits for Zserio float32 type.
 */
struct Float32ArrayTraits
{
    /** Element type. */
    using ElementType = float;

    /**
     * Calculates bit size of the array element.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf()
    {
        return 32;
    }

    /**
     * Calculates bit size of the array element.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType)
    {
        return bitSizeOf();
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readFloat32();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        out.writeFloat32(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = true;
};

/**
 * Array traits for Zserio float64 type.
 */
struct Float64ArrayTraits
{
    /** Element type. */
    using ElementType = double;

    /**
     * Calculates bit size of the array element.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf()
    {
        return 64;
    }

    /**
     * Calculates bit size of the array element.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType)
    {
        return bitSizeOf();
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readFloat64();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        out.writeFloat64(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = true;
};

/**
 * Array traits for Zserio bool type.
 */
struct BoolArrayTraits
{
    /** Element type. */
    using ElementType = bool;

    /**
     * Calculates bit size of the array element.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf()
    {
        return 1;
    }

    /**
     * Calculates bit size of the array element.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType)
    {
        return bitSizeOf();
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return in.readBool();
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        out.writeBool(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = true;
};

/**
 * Array traits for Zserio string type.
 */
template <template <typename> class ALLOC = std::allocator>
struct BasicStringArrayTraits
{
    /** Element type. */
    using ElementType = ::zserio::string<ALLOC<char>>;

    /** Allocator type. */
    using allocator_type = typename ElementType::allocator_type;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, const ElementType& element)
    {
        return zserio::bitSizeOfString(element);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, const ElementType& element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in, const allocator_type& allocator)
    {
        return in.readString(allocator);
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, const ElementType& element)
    {
        out.writeString(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

using StringArrayTraits = BasicStringArrayTraits<>;

/**
 * Array traits for Zserio extern bit buffer type.
 */
template <template <typename> class ALLOC = std::allocator>
struct BasicBitBufferArrayTraits
{
    /** Element type. */
    using ElementType = BasicBitBuffer<ALLOC<uint8_t>>;

    /** Allocator type. */
    using allocator_type = typename ElementType::allocator_type;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, const ElementType& element)
    {
        return zserio::bitSizeOfBitBuffer(element);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, const ElementType& element)
    {
        return bitPosition + bitSizeOf(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     */
    static ElementType read(BitStreamReader& in, const allocator_type& allocator)
    {
        return in.readBitBuffer(allocator);
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, const ElementType& element)
    {
        out.writeBitBuffer(element);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

using BitBufferArrayTraits = BasicBitBufferArrayTraits<>;

/**
 * Array traits for Zserio enumeration type.
 */
template <typename T>
struct EnumArrayTraits
{
    /** Element type. */
    using ElementType = T;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType element)
    {
        return zserio::bitSizeOf(element);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return zserio::initializeOffsets(bitPosition, element);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return zserio::read<ElementType>(in);
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        zserio::write(out, element);
    }

    // Be aware that T can be varuint, so bitSizeOf cannot return constant value.
    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

/**
 * Array traits for Zserio bitmask type.
 */
template <typename T>
struct BitmaskArrayTraits
{
    /** Element type. */
    using ElementType = T;

    /**
     * Calculates bit size of the array element.
     *
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t, ElementType element)
    {
        return element.bitSizeOf();
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType element)
    {
        return element.initializeOffsets(bitPosition);
    }

    /**
     * Reads the single array element.
     *
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    static ElementType read(BitStreamReader& in)
    {
        return ElementType(in);
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType element)
    {
        element.write(out, NO_PRE_WRITE_ACTION);
    }

    // Be aware that T can be varuint, so bitSizeOf cannot return constant value.
    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

/**
 * Array traits for Zserio structure, choice and union types.
 */
template <typename T, typename ELEMENT_FACTORY>
class ObjectArrayTraits
{
public:
    /** Element type. */
    using ElementType = T;

    /**
     * Calculates bit size of the array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use for calculation.
     *
     * \return Bit size of the array element.
     */
    static size_t bitSizeOf(size_t bitPosition, const ElementType& element)
    {
        return element.bitSizeOf(bitPosition);
    }

    /**
     * Initializes indexed offsets of the single array element.
     *
     * \param bitPosition Current bit position.
     * \param element Element to use.
     *
     * \return Updated bit position which points to the first bit after the array element.
     */
    static size_t initializeOffsets(size_t bitPosition, ElementType& element)
    {
        return element.initializeOffsets(bitPosition);
    }

    /**
     * Reads the single array element.
     *
     * \param elementFactory Factory which knows how to create a single array element.
     * \param rawArray Raw array to use.
     * \param in Bit stream reader.
     * \param index Index need in case of parameterized type which depends on the current index.
     */
    template <typename RAW_ARRAY>
    static void read(const ELEMENT_FACTORY& elementFactory, RAW_ARRAY& rawArray,
            BitStreamReader& in, size_t index)
    {
        elementFactory.create(rawArray, in, index);
    }

    /**
     * Writes the single array element.
     *
     * \param out Bit stream writer to use.
     * \param element Element to write.
     */
    static void write(BitStreamWriter& out, ElementType& element)
    {
        element.write(out, NO_PRE_WRITE_ACTION);
    }

    /** Determines whether the bit size of the single element is constant. */
    static const bool IS_BITSIZEOF_CONSTANT = false;
};

/**
 * Packed array traits.
 *
 * Packed array traits are used for all packable built-in types. Works with a single DeltaContext.
 */
template <typename ARRAY_TRAITS>
class PackedArrayTraits
{
public:
    /** Element type. */
    using ElementType = typename ARRAY_TRAITS::ElementType;

    /**
     * Constructor.
     *
     * \param arrayTraits Standard array traits.
     */
    explicit PackedArrayTraits(const ARRAY_TRAITS& arrayTraits)
    :   m_arrayTraits(arrayTraits)
    {}

    /**
     * Creates packing context.
     *
     * \param contextNode Packing context node where the context is created.
     */
    template <typename PACKING_CONTEXT_NODE>
    void createContext(PACKING_CONTEXT_NODE& contextNode) const
    {
        contextNode.createContext();
    }

    /**
     * Calls context initialization step for the current element.
     *
     * \param contextNode Packing context node which keeps the context.
     * \param element Current element.
     */
    template <typename PACKING_CONTEXT_NODE>
    void initContext(PACKING_CONTEXT_NODE& contextNode, ElementType element) const
    {
        contextNode.getContext().init(element);
    }

    /**
     * Returns length of the array element stored in the bit stream in bits.
     *
     * \param contextNode Packing context node.
     * \param bitPosition Current bit stream position.
     * \param element Current element.
     *
     * \return Length of the array element stored in the bit stream in bits.
     */
    template <typename PACKING_CONTEXT_NODE>
    size_t bitSizeOf(PACKING_CONTEXT_NODE& contextNode, size_t bitPosition, ElementType element) const
    {
        return contextNode.getContext().bitSizeOf(m_arrayTraits, bitPosition, element);
    }

    /**
     * Calls indexed offsets initialization for the current element.
     *
     * \param contextNode Packing context node.
     * \param bitPosition Current bit stream position.
     * \param element Current element.
     *
     * \return Updated bit stream position which points to the first bit after this element.
     */
    template <typename PACKING_CONTEXT_NODE>
    size_t initializeOffsets(PACKING_CONTEXT_NODE& contextNode, size_t bitPosition, ElementType element) const
    {
        return bitPosition + contextNode.getContext().bitSizeOf(m_arrayTraits, bitPosition, element);
    }

    /**
     * Reads an element from the bit stream.
     *
     * \param contextNode Packing context node.
     * \param in Bit stream reader.
     *
     * \return Read element value.
     */
    template <typename PACKING_CONTEXT_NODE>
    ElementType read(PACKING_CONTEXT_NODE& contextNode, BitStreamReader& in) const
    {
        return contextNode.getContext().read(m_arrayTraits, in);
    }

    /**
     * Writes the element to the bit stream.
     *
     * \param contextNode Packing context node.
     * \param out Bit stream writer.
     * \param element Element to write.
     */
    template <typename PACKING_CONTEXT_NODE>
    void write(PACKING_CONTEXT_NODE& contextNode, BitStreamWriter& out, ElementType element) const
    {
        contextNode.getContext().write(m_arrayTraits, out, element);
    }

private:
    ARRAY_TRAITS m_arrayTraits;
};

/**
 * Specialization of packed array traits for Zserio enums.
 */
template <typename T>
class PackedArrayTraits<EnumArrayTraits<T>>
{
public:
    /** Element type. */
    using ElementType = T;

    /**
     * Constructor.
     *
     * Takes enum array traits just to be consistent with generic PackedArrayTraits
     * and also to allow template argument deduction.
     */
    explicit PackedArrayTraits(const EnumArrayTraits<T>&)
    {}

    /**
     * Creates packing context.
     *
     * \param contextNode Packing context node where the context is created.
     */
    template <typename PACKING_CONTEXT_NODE>
    void createContext(PACKING_CONTEXT_NODE& contextNode) const
    {
        contextNode.createContext();
    }

    /**
     * Calls context initialization step for the current element.
     *
     * \param contextNode Packing context node which keeps the context.
     * \param element Current element.
     */
    template <typename PACKING_CONTEXT_NODE>
    void initContext(PACKING_CONTEXT_NODE& contextNode, ElementType element) const
    {
        contextNode.getContext().init(enumToValue(element));
    }

    /**
     * Returns length of the array element stored in the bit stream in bits.
     *
     * \param contextNode Packing context node.
     * \param bitPosition Current bit stream position.
     * \param element Current element.
     *
     * \return Length of the array element stored in the bit stream in bits.
     */
    template <typename PACKING_CONTEXT_NODE>
    size_t bitSizeOf(PACKING_CONTEXT_NODE& contextNode, size_t bitPosition, ElementType element) const
    {
        return zserio::bitSizeOf(contextNode, bitPosition, element);
    }

    /**
     * Calls indexed offsets initialization for the current element.
     *
     * \param contextNode Packing context node.
     * \param bitPosition Current bit stream position.
     * \param element Current element.
     *
     * \return Updated bit stream position which points to the first bit after this element.
     */
    template <typename PACKING_CONTEXT_NODE>
    size_t initializeOffsets(PACKING_CONTEXT_NODE& contextNode, size_t bitPosition, ElementType element) const
    {
        return zserio::initializeOffsets(contextNode, bitPosition, element);
    }

    /**
     * Reads an element from the bit stream.
     *
     * \param contextNode Packing context node.
     * \param in Bit stream reader.
     *
     * \return Read element value.
     */
    template <typename PACKING_CONTEXT_NODE>
    ElementType read(PACKING_CONTEXT_NODE& contextNode, BitStreamReader& in) const
    {
        return zserio::read<ElementType>(contextNode, in);
    }

    /**
     * Writes the element to the bit stream.
     *
     * \param contextNode Packing context node.
     * \param out Bit stream writer.
     * \param element Element to write.
     */
    template <typename PACKING_CONTEXT_NODE>
    void write(PACKING_CONTEXT_NODE& contextNode, BitStreamWriter& out, ElementType element) const
    {
        zserio::write(contextNode, out, element);
    }
};

namespace detail
{

/** Object packed array tratis. */
template <typename T>
class ObjectPackedArrayTraits
{
public:
    using ElementType = T;

    /**
     * Creates packing context.
     *
     * \param contextNode Packing context node where the appropriate subtree of contexts will be created.
     */
    template <typename PACKING_CONTEXT_NODE>
    static void createContext(PACKING_CONTEXT_NODE& contextNode)
    {
        ElementType::createPackingContext(contextNode);
    }

    /**
     * Calls context initialization step for the current element.
     *
     * \param contextNode Packing context node which keeps the appropriate subtree of contexts.
     */
    template <typename PACKING_CONTEXT_NODE>
    static void initContext(PACKING_CONTEXT_NODE& contextNode, const ElementType& element)
    {
        element.initPackingContext(contextNode);
    }

    /**
     * Returns length of the array element stored in the bit stream in bits.
     *
     * \param contextNode Packing context node which keeps the appropriate subtree of contexts.
     * \param bitPosition Current bit stream position.
     * \param element Current element.
     *
     * \return Length of the array element stored in the bit stream in bits.
     */
    template <typename PACKING_CONTEXT_NODE>
    static size_t bitSizeOf(PACKING_CONTEXT_NODE& contextNode, size_t bitPosition,
            const ElementType& element)
    {
        return element.bitSizeOf(contextNode, bitPosition);
    }

    /**
     * Calls indexed offsets initialization for the current element.
     *
     * \param contextNode Packing context node which keeps the appropriate subtree of contexts.
     * \param bitPosition Current bit stream position.
     * \param element Current element.
     *
     * \returns Updated bit stream position which points to the first bit after this element.
     */
    template <typename PACKING_CONTEXT_NODE>
    static size_t initializeOffsets(PACKING_CONTEXT_NODE& contextNode, size_t bitPosition,
            ElementType& element)
    {
        return element.initializeOffsets(contextNode, bitPosition);
    }

    /**
     * Writes the element to the bit stream.
     *
     * \param contextNode Packing context node which keeps the appropriate subtree of contexts.
     * \param out Bit stream writer.
     * \param element Element to write.
     */
    template <typename PACKING_CONTEXT_NODE>
    static void write(PACKING_CONTEXT_NODE& contextNode, BitStreamWriter& out, ElementType& element)
    {
        element.write(contextNode, out);
    }
};

} // namespace detail

/**
 * Specialization of packed array traits for Zserio bitmasks.
 */
template <typename T>
class PackedArrayTraits<BitmaskArrayTraits<T>> : public detail::ObjectPackedArrayTraits<T>
{
public:
    /** Element type. */
    using ElementType = T;

    /**
     * Constructor.
     *
     * Takes bitmask array traits just to be consistent with generic PackedArrayTraits
     * and also to allow template argument deduction.
     */
    explicit PackedArrayTraits(const BitmaskArrayTraits<T>&)
    {}

    /**
     * Reads an element from the bit stream.
     *
     * \param contextNode Packing context node which keeps the appropriate subtree of contexts.
     * \param in Bit stream reader.
     *
     * \return Read element.
     */
    template <typename PACKING_CONTEXT_NODE>
    ElementType read(PACKING_CONTEXT_NODE& contextNode, BitStreamReader& in) const
    {
        return ElementType(contextNode, in);
    }
};

/**
 * Specialization of packed array traits for Zserio objects.
 */
template <typename T, typename ELEMENT_FACTORY>
class PackedArrayTraits<ObjectArrayTraits<T, ELEMENT_FACTORY>> : public detail::ObjectPackedArrayTraits<T>
{
public:
    /** Element type. */
    using ElementType = T;

    /**
     * Constructor.
     *
     * Takes object array traits just to be consistent with generic PackedArrayTraits
     * and also to allow template argument deduction.
     */
    explicit PackedArrayTraits(const ObjectArrayTraits<T, ELEMENT_FACTORY>&)
    {}

    /**
     * Reads an element from the bit stream.
     *
     * \param contextNode Packing context node which keeps the appropriate subtree of contexts.
     * \param elementFactory Factory which knows how to create a single array element from packed bit stream.
     * \param rawArray Raw array where to create the read element.
     * \param in Bit stream reader.
     * \param index Index of the current element.
     */
    template <typename PACKING_CONTEXT_NODE, typename ALLOC>
    static void read(PACKING_CONTEXT_NODE& contextNode, const ELEMENT_FACTORY& elementFactory,
            std::vector<ElementType, ALLOC>& rawArray, BitStreamReader& in, size_t index)
    {
        elementFactory.create(contextNode, rawArray, in, index);
    }
};

} // namespace zserio

#endif // ZSERIO_ARRAY_TRAITS_H_INC
