#ifndef ZSERIO_UNIQUE_PTR_H_INC
#define ZSERIO_UNIQUE_PTR_H_INC

#include <memory>
#include <type_traits>
#include "zserio/RebindAlloc.h"
#include "zserio/AllocatorHolder.h"

namespace zserio
{

namespace detail
{

template <class ALLOC_T>
struct UniquePtrDeleter : public AllocatorHolder<ALLOC_T>
{
    using allocator_type = ALLOC_T;
    using T = typename allocator_type::value_type;

    UniquePtrDeleter(UniquePtrDeleter&& other) = default;
    UniquePtrDeleter& operator=(UniquePtrDeleter&& other) = default;

    template <typename ALLOC_U = ALLOC_T>
    UniquePtrDeleter(const ALLOC_U& allocator = ALLOC_U()) : AllocatorHolder<ALLOC_T>(allocator)
    {
        static_assert(std::is_same<allocator_type, RebindAlloc<ALLOC_U, T>>::value,
                "UniquePtrDeleter requires same allocator in constructor!");
    }

    void operator()(T* ptr)
    {
        allocator_type alloc = this->get_allocator();
        using AllocTraits = std::allocator_traits<allocator_type>;
        AllocTraits::destroy(alloc, std::addressof(*ptr));
        AllocTraits::deallocate(alloc, ptr, 1);
    }
};

} // namespace detail

template <typename T, typename ALLOC = std::allocator<T>>
using unique_ptr = std::unique_ptr<T, detail::UniquePtrDeleter<ALLOC>>;

/**
 * Allocates memory for an object of type T using given allocator and constructs it passing args to its
 * constructor.
 *
 * \param allocator Allocator to use.
 * \param args      List of elements passed to T's constructor.
 *
 * \return Object of type zserio::unique_ptr<T, ALLOC> that owns and stores a pointer to the constructed object.
 */
template <typename T, typename ALLOC, class ...Args>
zserio::unique_ptr<T, RebindAlloc<ALLOC, T>>
allocate_unique(const ALLOC& allocator, Args&& ...args)
{
    using Allocator = RebindAlloc<ALLOC, T>;
    using AllocTraits = std::allocator_traits<Allocator>;

    Allocator typedAllocator = allocator;
    typename AllocTraits::pointer ptr = AllocTraits::allocate(typedAllocator, 1);
    try
    {
        AllocTraits::construct(typedAllocator, std::addressof(*ptr), std::forward<Args>(args)...);
        return zserio::unique_ptr<T, Allocator>(std::addressof(*ptr), typedAllocator);
    }
    catch (...)
    {
        AllocTraits::deallocate(typedAllocator, ptr, 1);
        throw;
    }
}

} // namespace zserio

#endif // ZSERIO_UNIQUE_PTR_H_INC
