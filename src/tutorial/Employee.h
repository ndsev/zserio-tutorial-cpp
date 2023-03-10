/**
 * Automatically generated by Zserio C++ extension version 2.10.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#ifndef TUTORIAL_EMPLOYEE_H
#define TUTORIAL_EMPLOYEE_H

#include <zserio/Traits.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/AllocatorPropagatingCopy.h>
#include <memory>
#include <zserio/PackingContext.h>
#include <zserio/OptionalHolder.h>
#include <zserio/Array.h>
#include <zserio/ArrayTraits.h>
#include <zserio/String.h>
#include <zserio/Types.h>
#include <zserio/Vector.h>

#include <tutorial/Experience.h>
#include <tutorial/Role.h>

namespace tutorial
{

class Employee
{
private:
    class ZserioElementFactory_skills
    {
    public:
        explicit ZserioElementFactory_skills(Employee& owner);

        void create(::zserio::vector<::tutorial::Experience>& array,
                ::zserio::BitStreamReader& in, size_t index) const;

        void create(::zserio::PackingContextNode& contextNode,
                ::zserio::vector<::tutorial::Experience>& array,
                ::zserio::BitStreamReader& in, size_t index) const;

    private:
        std::reference_wrapper<Employee> m_ownerRef;
    };

    using ZserioArrayType_skills = ::zserio::Array<::zserio::vector<::tutorial::Experience>, ::zserio::ObjectArrayTraits<::tutorial::Experience, ZserioElementFactory_skills>, ::zserio::ArrayType::AUTO>;

public:
    using allocator_type = ::std::allocator<uint8_t>;

    Employee() noexcept :
            Employee(allocator_type())
    {}

    explicit Employee(const allocator_type& allocator) noexcept;

    template <typename ZSERIO_T_name = ::zserio::string<>,
            typename ZSERIO_T_bonus = uint16_t,
            typename ZSERIO_T_skills = ::zserio::vector<::tutorial::Experience>>
    Employee(
            uint8_t age_,
            ZSERIO_T_name&& name_,
            uint16_t salary_,
            ZSERIO_T_bonus&& bonus_,
            ::tutorial::Role role_,
            ZSERIO_T_skills&& skills_,
            const allocator_type& allocator = allocator_type()) :
            Employee(allocator)
    {
        m_age_ = age_;
        m_name_ = ::std::forward<ZSERIO_T_name>(name_);
        m_salary_ = salary_;
        m_bonus_ = ::std::forward<ZSERIO_T_bonus>(bonus_);
        m_role_ = role_;
        m_skills_ = ::zserio::createOptionalArray<ZserioArrayType_skills>(::std::forward<ZSERIO_T_skills>(skills_), ::zserio::ObjectArrayTraits<::tutorial::Experience, ZserioElementFactory_skills>());
    }

    explicit Employee(::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());
    explicit Employee(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());

    ~Employee() = default;

    Employee(const Employee&) = default;
    Employee& operator=(const Employee&) = default;

    Employee(Employee&&) = default;
    Employee& operator=(Employee&&) = default;

    Employee(::zserio::PropagateAllocatorT,
            const Employee& other, const allocator_type& allocator);

    uint8_t getAge() const;
    void setAge(uint8_t age_);

    const ::zserio::string<>& getName() const;
    ::zserio::string<>& getName();
    void setName(const ::zserio::string<>& name_);
    void setName(::zserio::string<>&& name_);

    uint16_t getSalary() const;
    void setSalary(uint16_t salary_);

    uint16_t getBonus() const;
    void setBonus(uint16_t bonus_);
    bool isBonusUsed() const;
    bool isBonusSet() const;
    void resetBonus();

    ::tutorial::Role getRole() const;
    void setRole(::tutorial::Role role_);

    const ::zserio::vector<::tutorial::Experience>& getSkills() const;
    ::zserio::vector<::tutorial::Experience>& getSkills();
    void setSkills(const ::zserio::vector<::tutorial::Experience>& skills_);
    void setSkills(::zserio::vector<::tutorial::Experience>&& skills_);
    bool isSkillsUsed() const;
    bool isSkillsSet() const;
    void resetSkills();

    static void createPackingContext(::zserio::PackingContextNode& contextNode);
    void initPackingContext(::zserio::PackingContextNode& contextNode) const;

    size_t bitSizeOf(size_t bitPosition = 0) const;
    size_t bitSizeOf(::zserio::PackingContextNode& contextNode, size_t bitPosition) const;

    size_t initializeOffsets(size_t bitPosition = 0);
    size_t initializeOffsets(::zserio::PackingContextNode& contextNode, size_t bitPosition);

    bool operator==(const Employee& other) const;
    uint32_t hashCode() const;

    void write(::zserio::BitStreamWriter& out) const;
    void write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out) const;

private:
    uint8_t readAge(::zserio::BitStreamReader& in);
    uint8_t readAge(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::zserio::string<> readName(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    uint16_t readSalary(::zserio::BitStreamReader& in);
    uint16_t readSalary(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<uint16_t> readBonus(::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<uint16_t> readBonus(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::tutorial::Role readRole(::zserio::BitStreamReader& in);
    ::tutorial::Role readRole(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<ZserioArrayType_skills> readSkills(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<ZserioArrayType_skills> readSkills(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);

    uint8_t m_age_;
    ::zserio::string<> m_name_;
    uint16_t m_salary_;
    ::zserio::InplaceOptionalHolder<uint16_t> m_bonus_;
    ::tutorial::Role m_role_;
    ::zserio::InplaceOptionalHolder<ZserioArrayType_skills> m_skills_;
};

} // namespace tutorial

#endif // TUTORIAL_EMPLOYEE_H
