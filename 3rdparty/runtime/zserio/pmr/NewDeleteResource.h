#ifndef ZSERIO_PMR_NEW_DELETE_RESOURCE_H_INC
#define ZSERIO_PMR_NEW_DELETE_RESOURCE_H_INC

#include <new>
#include "zserio/pmr/MemoryResource.h"

namespace zserio
{
namespace pmr
{
namespace detail
{

class NewDeleteResource : public MemoryResource
{
private:
    virtual void* doAllocate(size_t bytes, size_t ) override
    {
        return ::operator new(bytes);
    }

    virtual void doDeallocate(void* p, size_t, size_t) override
    {
        ::operator delete(p);
    }

    virtual bool doIsEqual(const MemoryResource& other) const noexcept override
    {
        return this == &other;
    }
};

} // namespace detail

MemoryResource* getNewDeleteResource() noexcept;

} // namespace pmr
} // namespace zserio

#endif // ZSERIO_PMR_NEW_DELETE_RESOURCE_H_INC
