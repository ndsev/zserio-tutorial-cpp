#include <zserio/pmr/MemoryResource.h>

template <size_t BUFFER_SIZE = 256>
class StaticMemoryResource : public zserio::pmr::MemoryResource
{
public:
    explicit StaticMemoryResource(const char* name) :
            m_name(name)
    {
        m_buffer.fill(0);
        m_nextPtr = m_buffer.begin();
    }

    void* doAllocate(size_t bytes, size_t align) override
    {
        const size_t alignMod = static_cast<size_t>(m_nextPtr - m_buffer.begin()) % align;
        if (alignMod != 0)
            m_nextPtr += align - alignMod;

        void* const ptr = &(*m_nextPtr);
        m_nextPtr += bytes;

        const size_t usedBytes = static_cast<size_t>(m_nextPtr - m_buffer.begin());
        if (usedBytes > BUFFER_SIZE)
            throw zserio::CppRuntimeException(m_name) << ": Buffer overflow (" << usedBytes << ")!";

        ++m_numAllocations;
        m_totalAllocatedSize += bytes;

        return ptr;
    }

    void doDeallocate(void*, size_t bytes, size_t) override
    {
        ++m_numDeallocations;
    }

    bool doIsEqual(const MemoryResource& other) const noexcept override
    {
        return this == &other;
    }

    const char* getName() const noexcept
    {
        return m_name;
    }

    size_t getNumAllocations() const noexcept
    {
        return m_numAllocations;
    }

    size_t getNumDeallocations() const noexcept
    {
        return m_numDeallocations;
    }

    size_t getTotalAllocatedSize() const noexcept
    {
        return m_totalAllocatedSize;
    }

private:
    const char* m_name;

    std::array<uint8_t, BUFFER_SIZE> m_buffer;
    typename std::array<uint8_t, BUFFER_SIZE>::iterator m_nextPtr;
    size_t m_numAllocations = 0;
    size_t m_numDeallocations = 0;
    size_t m_totalAllocatedSize = 0;
};
