/**
 * Automatically generated by Zserio C++ extension version 2.9.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#ifndef TUTORIAL_EXPERIENCE_H
#define TUTORIAL_EXPERIENCE_H

#include <zserio/Traits.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/AllocatorPropagatingCopy.h>
#include <memory>
#include <zserio/PackingContext.h>
#include <zserio/ArrayTraits.h>
#include <zserio/Types.h>

#include <tutorial/Language.h>

namespace tutorial
{

class Experience
{
public:
    using allocator_type = ::std::allocator<uint8_t>;

    explicit Experience(const allocator_type& allocator = allocator_type()) noexcept;

    Experience(
            uint8_t yearsOfExperience_,
            ::tutorial::Language programmingLanguage_,
            const allocator_type& allocator = allocator_type()) :
            Experience(allocator)
    {
        m_yearsOfExperience_ = yearsOfExperience_;
        m_programmingLanguage_ = programmingLanguage_;
    }

    explicit Experience(::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());
    explicit Experience(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());

    ~Experience() = default;

    Experience(const Experience&) = default;
    Experience& operator=(const Experience&) = default;

    Experience(Experience&&) = default;
    Experience& operator=(Experience&&) = default;

    Experience(::zserio::PropagateAllocatorT,
            const Experience& other, const allocator_type& allocator);

    uint8_t getYearsOfExperience() const;
    void setYearsOfExperience(uint8_t yearsOfExperience_);

    ::tutorial::Language getProgrammingLanguage() const;
    void setProgrammingLanguage(::tutorial::Language programmingLanguage_);

    static void createPackingContext(::zserio::PackingContextNode& contextNode);
    void initPackingContext(::zserio::PackingContextNode& contextNode) const;

    size_t bitSizeOf(size_t bitPosition = 0) const;
    size_t bitSizeOf(::zserio::PackingContextNode& contextNode, size_t bitPosition) const;

    size_t initializeOffsets(size_t bitPosition = 0);
    size_t initializeOffsets(::zserio::PackingContextNode& contextNode, size_t bitPosition);

    bool operator==(const Experience& other) const;
    uint32_t hashCode() const;

    void write(::zserio::BitStreamWriter& out) const;
    void write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out) const;

private:
    uint8_t readYearsOfExperience(::zserio::BitStreamReader& in);
    uint8_t readYearsOfExperience(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::tutorial::Language readProgrammingLanguage(::zserio::BitStreamReader& in);
    ::tutorial::Language readProgrammingLanguage(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);

    uint8_t m_yearsOfExperience_;
    ::tutorial::Language m_programmingLanguage_;
};

} // namespace tutorial

#endif // TUTORIAL_EXPERIENCE_H
