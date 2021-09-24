#ifndef ZSERIO_ALLOCATOR_HOLDER_H_INC
#define ZSERIO_ALLOCATOR_HOLDER_H_INC

namespace zserio
{

/**
 * Base class for allocator-holding classes, so that the empty base class
 * optimization may happen.
 */
template<typename ALLOC>
class AllocatorHolder
{
public:
    using allocator_type = ALLOC;

    /**
     * Constructor from given allocator.
     *
     * \param allocator Allocator to be stored.
     */
    AllocatorHolder(const allocator_type &allocator = allocator_type()) :
        m_allocator(allocator)
    {}

    /**
     * Constructor from given allocator.
     *
     * \param allocator Allocator to be stored.
     */
    explicit AllocatorHolder(allocator_type&& allocator) :
        m_allocator(std::move(allocator))
    {}

    /**
     * Allocator getter.
     *
     * \return Copy of the stored allocator.
     */
    allocator_type get_allocator() const
    {
        return get_allocator_ref();
    }

protected:
    /**
     * Allocator setter.
     *
     * \param allocator Allocator to be copy-assigned to the stored allocator.
     */
    void set_allocator(const allocator_type& allocator)
    {
        m_allocator = allocator;
    }

    /**
     * Allocator setter.
     *
     * \param allocator Allocator to be move-assigned to the stored allocator.
     */
    void set_allocator(allocator_type&& allocator)
    {
        m_allocator = std::move(allocator);
    }

    /**
     * Allocator getter.
     *
     * \return Reference to the stored allocator.
     */
    allocator_type& get_allocator_ref()
    {
        return m_allocator;
    }

    /**
     * Allocator getter.
     *
     * \return Reference to the stored allocator.
     */
    const allocator_type& get_allocator_ref() const
    {
        return m_allocator;
    }

private:
    ALLOC m_allocator;
};

} // namespace zserio

#endif // ifndef ZSERIO_ALLOCATOR_HOLDER_H_INC
