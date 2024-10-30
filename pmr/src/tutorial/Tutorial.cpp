/**
 * Automatically generated by Zserio C++ generator version 1.1.0 using Zserio core 2.15.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, polymorphicAllocator.
 */

#include <zserio/StringConvertUtil.h>
#include <zserio/CppRuntimeException.h>

#include <tutorial/Language.h>

namespace zserio
{

// This is full specialization of enumeration traits and methods for Language enumeration.
constexpr ::std::array<const char*, 4> EnumTraits<::tutorial::Language>::names;
constexpr ::std::array<::tutorial::Language, 4> EnumTraits<::tutorial::Language>::values;
constexpr const char* EnumTraits<::tutorial::Language>::enumName;

template <>
size_t enumToOrdinal(::tutorial::Language value)
{
    switch (value)
    {
    case ::tutorial::Language::CPP:
        return 0;
    case ::tutorial::Language::JAVA:
        return 1;
    case ::tutorial::Language::PYTHON:
        return 2;
    case ::tutorial::Language::JS:
        return 3;
    default:
        throw ::zserio::CppRuntimeException("Unknown value for enumeration Language: ") <<
                static_cast<typename ::std::underlying_type<::tutorial::Language>::type>(value) << "!";
    }
}

template <>
::tutorial::Language valueToEnum(
        typename ::std::underlying_type<::tutorial::Language>::type rawValue)
{
    switch (rawValue)
    {
    case UINT8_C(0):
    case UINT8_C(1):
    case UINT8_C(2):
    case UINT8_C(3):
        return static_cast<::tutorial::Language>(rawValue);
    default:
        throw ::zserio::CppRuntimeException("Unknown value for enumeration Language: ") << rawValue << "!";
    }
}

template <>
uint32_t enumHashCode<::tutorial::Language>(::tutorial::Language value)
{
    uint32_t result = ::zserio::HASH_SEED;
    result = ::zserio::calcHashCode(result, enumToValue(value));
    return result;
}

template <>
size_t bitSizeOf(::tutorial::Language)
{
    return UINT8_C(2);
}

template <>
size_t initializeOffsets(size_t bitPosition, ::tutorial::Language value)
{
    return bitPosition + bitSizeOf(value);
}

template <>
::tutorial::Language read(::zserio::BitStreamReader& in)
{
    return valueToEnum<::tutorial::Language>(
            static_cast<typename ::std::underlying_type<::tutorial::Language>::type>(
                    in.readBits(UINT8_C(2))));
}

template <>
void write(::zserio::BitStreamWriter& out, ::tutorial::Language value)
{
    out.writeBits(::zserio::enumToValue(value), UINT8_C(2));
}

} // namespace zserio

/**
 * Automatically generated by Zserio C++ generator version 1.1.0 using Zserio core 2.15.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, polymorphicAllocator.
 */

#include <zserio/StringConvertUtil.h>
#include <zserio/CppRuntimeException.h>

#include <tutorial/Role.h>

namespace zserio
{

// This is full specialization of enumeration traits and methods for Role enumeration.
constexpr ::std::array<const char*, 3> EnumTraits<::tutorial::Role>::names;
constexpr ::std::array<::tutorial::Role, 3> EnumTraits<::tutorial::Role>::values;
constexpr const char* EnumTraits<::tutorial::Role>::enumName;

template <>
size_t enumToOrdinal(::tutorial::Role value)
{
    switch (value)
    {
    case ::tutorial::Role::DEVELOPER:
        return 0;
    case ::tutorial::Role::TEAM_LEAD:
        return 1;
    case ::tutorial::Role::CTO:
        return 2;
    default:
        throw ::zserio::CppRuntimeException("Unknown value for enumeration Role: ") <<
                static_cast<typename ::std::underlying_type<::tutorial::Role>::type>(value) << "!";
    }
}

template <>
::tutorial::Role valueToEnum(
        typename ::std::underlying_type<::tutorial::Role>::type rawValue)
{
    switch (rawValue)
    {
    case UINT8_C(0):
    case UINT8_C(1):
    case UINT8_C(2):
        return static_cast<::tutorial::Role>(rawValue);
    default:
        throw ::zserio::CppRuntimeException("Unknown value for enumeration Role: ") << rawValue << "!";
    }
}

template <>
uint32_t enumHashCode<::tutorial::Role>(::tutorial::Role value)
{
    uint32_t result = ::zserio::HASH_SEED;
    result = ::zserio::calcHashCode(result, enumToValue(value));
    return result;
}

template <>
size_t bitSizeOf(::tutorial::Role)
{
    return UINT8_C(8);
}

template <>
size_t initializeOffsets(size_t bitPosition, ::tutorial::Role value)
{
    return bitPosition + bitSizeOf(value);
}

template <>
::tutorial::Role read(::zserio::BitStreamReader& in)
{
    return valueToEnum<::tutorial::Role>(
            static_cast<typename ::std::underlying_type<::tutorial::Role>::type>(
                    in.readBits(UINT8_C(8))));
}

template <>
void write(::zserio::BitStreamWriter& out, ::tutorial::Role value)
{
    out.writeBits(::zserio::enumToValue(value), UINT8_C(8));
}

} // namespace zserio

/**
 * Automatically generated by Zserio C++ generator version 1.1.0 using Zserio core 2.15.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, polymorphicAllocator.
 */

#include <zserio/StringConvertUtil.h>
#include <zserio/CppRuntimeException.h>
#include <zserio/HashCodeUtil.h>
#include <zserio/BitPositionUtil.h>
#include <zserio/BitSizeOfCalculator.h>
#include <zserio/BitFieldUtil.h>
#include <zserio/ConstraintException.h>
#include <zserio/ArrayTraits.h>

#include <tutorial/Employee.h>
#include <tutorial/Role.h>

namespace tutorial
{

Employee::Employee(const allocator_type& allocator) noexcept :
        m_age_(uint8_t()),
        m_name_(allocator),
        m_salary_(uint16_t()),
        m_bonus_(::zserio::NullOpt),
        m_role_(::tutorial::Role()),
        m_skills_(::zserio::NullOpt)
{
}

Employee::Employee(::zserio::BitStreamReader& in, const allocator_type& allocator) :
        m_age_(readAge(in)),
        m_name_(readName(in, allocator)),
        m_salary_(readSalary(in)),
        m_bonus_(readBonus(in)),
        m_role_(readRole(in)),
        m_skills_(readSkills(in, allocator))
{
}

Employee::Employee(::zserio::PropagateAllocatorT,
        const Employee& other, const allocator_type& allocator) :
        m_age_(::zserio::allocatorPropagatingCopy(other.m_age_, allocator)),
        m_name_(::zserio::allocatorPropagatingCopy(other.m_name_, allocator)),
        m_salary_(::zserio::allocatorPropagatingCopy(other.m_salary_, allocator)),
        m_bonus_(::zserio::allocatorPropagatingCopy(other.m_bonus_, allocator)),
        m_role_(::zserio::allocatorPropagatingCopy(other.m_role_, allocator)),
        m_skills_(::zserio::allocatorPropagatingCopy(other.m_skills_, allocator))
{
}

uint8_t Employee::getAge() const
{
    return m_age_;
}

void Employee::setAge(uint8_t age_)
{
    m_age_ = age_;
}

::zserio::pmr::string& Employee::getName()
{
    return m_name_;
}

const ::zserio::pmr::string& Employee::getName() const
{
    return m_name_;
}

void Employee::setName(const ::zserio::pmr::string& name_)
{
    m_name_ = name_;
}

void Employee::setName(::zserio::pmr::string&& name_)
{
    m_name_ = ::std::move(name_);
}

uint16_t Employee::getSalary() const
{
    return m_salary_;
}

void Employee::setSalary(uint16_t salary_)
{
    m_salary_ = salary_;
}

uint16_t Employee::getBonus() const
{
    return m_bonus_.value();
}

void Employee::setBonus(uint16_t bonus_)
{
    m_bonus_ = bonus_;
}

bool Employee::isBonusUsed() const
{
    return (m_bonus_.hasValue());
}

bool Employee::isBonusSet() const
{
    return m_bonus_.hasValue();
}

void Employee::resetBonus()
{
    m_bonus_.reset();
}

::tutorial::Role Employee::getRole() const
{
    return m_role_;
}

void Employee::setRole(::tutorial::Role role_)
{
    m_role_ = role_;
}

::zserio::pmr::vector<::tutorial::Experience>& Employee::getSkills()
{
    return m_skills_.value().getRawArray();
}

const ::zserio::pmr::vector<::tutorial::Experience>& Employee::getSkills() const
{
    return m_skills_.value().getRawArray();
}

void Employee::setSkills(const ::zserio::pmr::vector<::tutorial::Experience>& skills_)
{
    m_skills_ = ZserioArrayType_skills(skills_);
}

void Employee::setSkills(::zserio::pmr::vector<::tutorial::Experience>&& skills_)
{
    m_skills_ = ZserioArrayType_skills(std::move(skills_));
}

bool Employee::isSkillsUsed() const
{
    return (getRole() == ::tutorial::Role::DEVELOPER);
}

bool Employee::isSkillsSet() const
{
    return m_skills_.hasValue();
}

void Employee::resetSkills()
{
    m_skills_.reset();
}

size_t Employee::bitSizeOf(size_t bitPosition) const
{
    size_t endBitPosition = bitPosition;

    endBitPosition += UINT8_C(8);
    endBitPosition += ::zserio::bitSizeOfString(m_name_);
    endBitPosition += UINT8_C(16);
    endBitPosition += 1;
    if (m_bonus_.hasValue())
    {
        endBitPosition += UINT8_C(16);
    }
    endBitPosition += ::zserio::bitSizeOf(m_role_);
    if (getRole() == ::tutorial::Role::DEVELOPER)
    {
        endBitPosition += m_skills_.value().bitSizeOf(*this, endBitPosition);
    }

    return endBitPosition - bitPosition;
}

size_t Employee::initializeOffsets(size_t bitPosition)
{
    size_t endBitPosition = bitPosition;

    endBitPosition += UINT8_C(8);
    endBitPosition += ::zserio::bitSizeOfString(m_name_);
    endBitPosition += UINT8_C(16);
    endBitPosition += 1;
    if (m_bonus_.hasValue())
    {
        endBitPosition += UINT8_C(16);
    }
    endBitPosition = ::zserio::initializeOffsets(endBitPosition, m_role_);
    if (getRole() == ::tutorial::Role::DEVELOPER)
    {
        endBitPosition = m_skills_.value().initializeOffsets(*this, endBitPosition);
    }

    return endBitPosition;
}

bool Employee::operator==(const Employee& other) const
{
    if (this != &other)
    {
        return
                (m_age_ == other.m_age_) &&
                (m_name_ == other.m_name_) &&
                (m_salary_ == other.m_salary_) &&
                (!isBonusUsed() ? !other.isBonusUsed() : (m_bonus_ == other.m_bonus_)) &&
                (m_role_ == other.m_role_) &&
                (!isSkillsUsed() ? !other.isSkillsUsed() : (m_skills_ == other.m_skills_));
    }

    return true;
}

bool Employee::operator<(const Employee& other) const
{
    if (m_age_ < other.m_age_)
    {
        return true;
    }
    if (other.m_age_ < m_age_)
    {
        return false;
    }

    if (m_name_ < other.m_name_)
    {
        return true;
    }
    if (other.m_name_ < m_name_)
    {
        return false;
    }

    if (m_salary_ < other.m_salary_)
    {
        return true;
    }
    if (other.m_salary_ < m_salary_)
    {
        return false;
    }

    if (isBonusUsed() && other.isBonusUsed())
    {
        if (m_bonus_ < other.m_bonus_)
        {
            return true;
        }
        if (other.m_bonus_ < m_bonus_)
        {
            return false;
        }
    }
    else if (isBonusUsed() != other.isBonusUsed())
    {
        return !isBonusUsed();
    }

    if (m_role_ < other.m_role_)
    {
        return true;
    }
    if (other.m_role_ < m_role_)
    {
        return false;
    }

    if (isSkillsUsed() && other.isSkillsUsed())
    {
        if (m_skills_ < other.m_skills_)
        {
            return true;
        }
        if (other.m_skills_ < m_skills_)
        {
            return false;
        }
    }
    else if (isSkillsUsed() != other.isSkillsUsed())
    {
        return !isSkillsUsed();
    }

    return false;
}

uint32_t Employee::hashCode() const
{
    uint32_t result = ::zserio::HASH_SEED;

    result = ::zserio::calcHashCode(result, m_age_);
    result = ::zserio::calcHashCode(result, m_name_);
    result = ::zserio::calcHashCode(result, m_salary_);
    if (isBonusUsed())
    {
        result = ::zserio::calcHashCode(result, m_bonus_);
    }
    result = ::zserio::calcHashCode(result, m_role_);
    if (isSkillsUsed())
    {
        result = ::zserio::calcHashCode(result, m_skills_);
    }

    return result;
}

void Employee::write(::zserio::BitStreamWriter& out) const
{
    // check constraint
    if (!(getAge() <= 65))
    {
        throw ::zserio::ConstraintException("Write: Constraint violated at Employee.age!");
    }
    out.writeBits(m_age_, UINT8_C(8));

    out.writeString(m_name_);

    out.writeBits(m_salary_, UINT8_C(16));

    if (m_bonus_.hasValue())
    {
        out.writeBool(true);
        out.writeBits(m_bonus_.value(), UINT8_C(16));
    }
    else
    {
        out.writeBool(false);
    }

    ::zserio::write(out, m_role_);

    if (getRole() == ::tutorial::Role::DEVELOPER)
    {
        m_skills_.value().write(*this, out);
    }
}

void Employee::ZserioElementFactory_skills::create(Employee&,
        ::zserio::pmr::vector<::tutorial::Experience>& array,
        ::zserio::BitStreamReader& in, size_t)
{
    array.emplace_back(in, array.get_allocator());
}

uint8_t Employee::readAge(::zserio::BitStreamReader& in)
{
    uint8_t readField = static_cast<uint8_t>(in.readBits(UINT8_C(8)));
    // check constraint
    if (!(readField <= 65))
    {
        throw ::zserio::ConstraintException("Read: Constraint violated at Employee.age!");
    }

    return readField;
}

::zserio::pmr::string Employee::readName(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    return static_cast<::zserio::pmr::string>(in.readString(allocator));
}

uint16_t Employee::readSalary(::zserio::BitStreamReader& in)
{
    return static_cast<uint16_t>(in.readBits(UINT8_C(16)));
}

::zserio::InplaceOptionalHolder<uint16_t> Employee::readBonus(::zserio::BitStreamReader& in)
{
    if (in.readBool())
    {
        return ::zserio::InplaceOptionalHolder<uint16_t>(static_cast<uint16_t>(in.readBits(UINT8_C(16))));
    }

    return ::zserio::InplaceOptionalHolder<uint16_t>(::zserio::NullOpt);
}

::tutorial::Role Employee::readRole(::zserio::BitStreamReader& in)
{
    return ::zserio::read<::tutorial::Role>(in);
}

::zserio::InplaceOptionalHolder<Employee::ZserioArrayType_skills> Employee::readSkills(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    if (getRole() == ::tutorial::Role::DEVELOPER)
    {
        ZserioArrayType_skills readField(allocator);
        readField.read(*this, in);

        return ::zserio::InplaceOptionalHolder<ZserioArrayType_skills>(::std::move(readField));
    }

    return ::zserio::InplaceOptionalHolder<ZserioArrayType_skills>(::zserio::NullOpt);
}


} // namespace tutorial

/**
 * Automatically generated by Zserio C++ generator version 1.1.0 using Zserio core 2.15.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, polymorphicAllocator.
 */

#include <zserio/StringConvertUtil.h>
#include <zserio/CppRuntimeException.h>
#include <zserio/HashCodeUtil.h>
#include <zserio/BitPositionUtil.h>
#include <zserio/BitSizeOfCalculator.h>
#include <zserio/BitFieldUtil.h>

#include <tutorial/Experience.h>

namespace tutorial
{

Experience::Experience(const allocator_type&) noexcept :
        m_yearsOfExperience_(uint8_t()),
        m_programmingLanguage_(::tutorial::Language())
{
}

Experience::Experience(::zserio::BitStreamReader& in, const allocator_type&) :
        m_yearsOfExperience_(readYearsOfExperience(in)),
        m_programmingLanguage_(readProgrammingLanguage(in))
{
}

Experience::Experience(::zserio::PropagateAllocatorT,
        const Experience& other, const allocator_type& allocator) :
        m_yearsOfExperience_(::zserio::allocatorPropagatingCopy(other.m_yearsOfExperience_, allocator)),
        m_programmingLanguage_(::zserio::allocatorPropagatingCopy(other.m_programmingLanguage_, allocator))
{
}

uint8_t Experience::getYearsOfExperience() const
{
    return m_yearsOfExperience_;
}

void Experience::setYearsOfExperience(uint8_t yearsOfExperience_)
{
    m_yearsOfExperience_ = yearsOfExperience_;
}

::tutorial::Language Experience::getProgrammingLanguage() const
{
    return m_programmingLanguage_;
}

void Experience::setProgrammingLanguage(::tutorial::Language programmingLanguage_)
{
    m_programmingLanguage_ = programmingLanguage_;
}

size_t Experience::bitSizeOf(size_t bitPosition) const
{
    size_t endBitPosition = bitPosition;

    endBitPosition += UINT8_C(6);
    endBitPosition += ::zserio::bitSizeOf(m_programmingLanguage_);

    return endBitPosition - bitPosition;
}

size_t Experience::initializeOffsets(size_t bitPosition)
{
    size_t endBitPosition = bitPosition;

    endBitPosition += UINT8_C(6);
    endBitPosition = ::zserio::initializeOffsets(endBitPosition, m_programmingLanguage_);

    return endBitPosition;
}

bool Experience::operator==(const Experience& other) const
{
    if (this != &other)
    {
        return
                (m_yearsOfExperience_ == other.m_yearsOfExperience_) &&
                (m_programmingLanguage_ == other.m_programmingLanguage_);
    }

    return true;
}

bool Experience::operator<(const Experience& other) const
{
    if (m_yearsOfExperience_ < other.m_yearsOfExperience_)
    {
        return true;
    }
    if (other.m_yearsOfExperience_ < m_yearsOfExperience_)
    {
        return false;
    }

    if (m_programmingLanguage_ < other.m_programmingLanguage_)
    {
        return true;
    }
    if (other.m_programmingLanguage_ < m_programmingLanguage_)
    {
        return false;
    }

    return false;
}

uint32_t Experience::hashCode() const
{
    uint32_t result = ::zserio::HASH_SEED;

    result = ::zserio::calcHashCode(result, m_yearsOfExperience_);
    result = ::zserio::calcHashCode(result, m_programmingLanguage_);

    return result;
}

void Experience::write(::zserio::BitStreamWriter& out) const
{
    out.writeBits(m_yearsOfExperience_, UINT8_C(6));
    ::zserio::write(out, m_programmingLanguage_);
}

uint8_t Experience::readYearsOfExperience(::zserio::BitStreamReader& in)
{
    return static_cast<uint8_t>(in.readBits(UINT8_C(6)));
}

::tutorial::Language Experience::readProgrammingLanguage(::zserio::BitStreamReader& in)
{
    return ::zserio::read<::tutorial::Language>(in);
}


} // namespace tutorial
