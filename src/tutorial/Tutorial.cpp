/**
 * Automatically generated by Zserio C++ extension version 2.10.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#include <zserio/StringConvertUtil.h>
#include <zserio/CppRuntimeException.h>

#include <tutorial/Language.h>

namespace zserio
{

// This is full specialization of enumeration traits and methods for Language enumeration.
constexpr ::std::array<const char*, 4> EnumTraits<::tutorial::Language>::names;
constexpr ::std::array<::tutorial::Language, 4> EnumTraits<::tutorial::Language>::values;

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
        return ::tutorial::Language(rawValue);
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
void initPackingContext(::zserio::PackingContextNode& contextNode, ::tutorial::Language value)
{
    contextNode.getContext().init(::zserio::BitFieldArrayTraits<typename ::std::underlying_type<::tutorial::Language>::type>(UINT8_C(2)),
            ::zserio::enumToValue(value));
}

template <>
size_t bitSizeOf(::tutorial::Language)
{
    return UINT8_C(2);
}

template <>
size_t bitSizeOf(::zserio::PackingContextNode& contextNode, ::tutorial::Language value)
{
    return contextNode.getContext().bitSizeOf(
            ::zserio::BitFieldArrayTraits<typename ::std::underlying_type<::tutorial::Language>::type>(UINT8_C(2)),
            ::zserio::enumToValue(value));
}

template <>
size_t initializeOffsets(size_t bitPosition, ::tutorial::Language value)
{
    return bitPosition + bitSizeOf(value);
}

template <>
size_t initializeOffsets(::zserio::PackingContextNode& contextNode,
        size_t bitPosition, ::tutorial::Language value)
{
    return bitPosition + bitSizeOf(contextNode, value);
}

template <>
::tutorial::Language read(::zserio::BitStreamReader& in)
{
    return valueToEnum<::tutorial::Language>(
            static_cast<typename ::std::underlying_type<::tutorial::Language>::type>(
                    in.readBits(UINT8_C(2))));
}

template <>
::tutorial::Language read(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in)
{
    return valueToEnum<::tutorial::Language>(contextNode.getContext().read(
            ::zserio::BitFieldArrayTraits<typename ::std::underlying_type<::tutorial::Language>::type>(UINT8_C(2)), in));
}

template <>
void write(::zserio::BitStreamWriter& out, ::tutorial::Language value)
{
    out.writeBits(::zserio::enumToValue(value), UINT8_C(2));
}

template <>
void write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out, ::tutorial::Language value)
{
    contextNode.getContext().write(
            ::zserio::BitFieldArrayTraits<typename ::std::underlying_type<::tutorial::Language>::type>(UINT8_C(2)),
            out, ::zserio::enumToValue(value));
}

} // namespace zserio

/**
 * Automatically generated by Zserio C++ extension version 2.10.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#include <zserio/StringConvertUtil.h>
#include <zserio/CppRuntimeException.h>

#include <tutorial/Role.h>

namespace zserio
{

// This is full specialization of enumeration traits and methods for Role enumeration.
constexpr ::std::array<const char*, 3> EnumTraits<::tutorial::Role>::names;
constexpr ::std::array<::tutorial::Role, 3> EnumTraits<::tutorial::Role>::values;

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
        return ::tutorial::Role(rawValue);
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
void initPackingContext(::zserio::PackingContextNode& contextNode, ::tutorial::Role value)
{
    contextNode.getContext().init(::zserio::StdIntArrayTraits<typename ::std::underlying_type<::tutorial::Role>::type>(),
            ::zserio::enumToValue(value));
}

template <>
size_t bitSizeOf(::tutorial::Role)
{
    return UINT8_C(8);
}

template <>
size_t bitSizeOf(::zserio::PackingContextNode& contextNode, ::tutorial::Role value)
{
    return contextNode.getContext().bitSizeOf(
            ::zserio::StdIntArrayTraits<typename ::std::underlying_type<::tutorial::Role>::type>(),
            ::zserio::enumToValue(value));
}

template <>
size_t initializeOffsets(size_t bitPosition, ::tutorial::Role value)
{
    return bitPosition + bitSizeOf(value);
}

template <>
size_t initializeOffsets(::zserio::PackingContextNode& contextNode,
        size_t bitPosition, ::tutorial::Role value)
{
    return bitPosition + bitSizeOf(contextNode, value);
}

template <>
::tutorial::Role read(::zserio::BitStreamReader& in)
{
    return valueToEnum<::tutorial::Role>(
            static_cast<typename ::std::underlying_type<::tutorial::Role>::type>(
                    in.readBits(UINT8_C(8))));
}

template <>
::tutorial::Role read(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in)
{
    return valueToEnum<::tutorial::Role>(contextNode.getContext().read(
            ::zserio::StdIntArrayTraits<typename ::std::underlying_type<::tutorial::Role>::type>(), in));
}

template <>
void write(::zserio::BitStreamWriter& out, ::tutorial::Role value)
{
    out.writeBits(::zserio::enumToValue(value), UINT8_C(8));
}

template <>
void write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out, ::tutorial::Role value)
{
    contextNode.getContext().write(
            ::zserio::StdIntArrayTraits<typename ::std::underlying_type<::tutorial::Role>::type>(),
            out, ::zserio::enumToValue(value));
}

} // namespace zserio

/**
 * Automatically generated by Zserio C++ extension version 2.10.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#include <zserio/StringConvertUtil.h>
#include <zserio/CppRuntimeException.h>
#include <zserio/HashCodeUtil.h>
#include <zserio/BitPositionUtil.h>
#include <zserio/BitSizeOfCalculator.h>
#include <zserio/BitFieldUtil.h>
#include <zserio/ConstraintException.h>
#include <functional>
#include <zserio/ArrayTraits.h>

#include <tutorial/Employee.h>
#include <tutorial/Role.h>

namespace tutorial
{

Employee::ZserioElementFactory_skills::ZserioElementFactory_skills(Employee& owner) :
        m_ownerRef(owner)
{}

void Employee::ZserioElementFactory_skills::create(::zserio::vector<::tutorial::Experience>& array,
        ::zserio::BitStreamReader& in, size_t index) const
{
    (void)index;
    array.emplace_back(in, array.get_allocator());
}

void Employee::ZserioElementFactory_skills::create(::zserio::PackingContextNode& contextNode,
        ::zserio::vector<::tutorial::Experience>& array, ::zserio::BitStreamReader& in, size_t index) const
{
    (void)index;
    array.emplace_back(contextNode, in, array.get_allocator());
}

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

Employee::Employee(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in, const allocator_type& allocator) :
        m_age_(readAge(contextNode, in)),
        m_name_(readName(in, allocator)),
        m_salary_(readSalary(contextNode, in)),
        m_bonus_(readBonus(contextNode, in)),
        m_role_(readRole(contextNode, in)),
        m_skills_(readSkills(contextNode, in, allocator))
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

::zserio::string<>& Employee::getName()
{
    return m_name_;
}

const ::zserio::string<>& Employee::getName() const
{
    return m_name_;
}

void Employee::setName(const ::zserio::string<>& name_)
{
    m_name_ = name_;
}

void Employee::setName(::zserio::string<>&& name_)
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
    return (isBonusSet());
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

::zserio::vector<::tutorial::Experience>& Employee::getSkills()
{
    return m_skills_.value().getRawArray();
}

const ::zserio::vector<::tutorial::Experience>& Employee::getSkills() const
{
    return m_skills_.value().getRawArray();
}

void Employee::setSkills(const ::zserio::vector<::tutorial::Experience>& skills_)
{
    m_skills_ = ZserioArrayType_skills(skills_, ::zserio::ObjectArrayTraits<::tutorial::Experience, ZserioElementFactory_skills>());
}

void Employee::setSkills(::zserio::vector<::tutorial::Experience>&& skills_)
{
    m_skills_ = ZserioArrayType_skills(std::move(skills_), ::zserio::ObjectArrayTraits<::tutorial::Experience, ZserioElementFactory_skills>());
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

void Employee::createPackingContext(::zserio::PackingContextNode& contextNode)
{
    contextNode.createChild().createContext();
    contextNode.createChild();
    contextNode.createChild().createContext();
    contextNode.createChild().createContext();
    contextNode.createChild().createContext();
    contextNode.createChild();
}

void Employee::initPackingContext(::zserio::PackingContextNode& contextNode) const
{
    contextNode.getChildren()[0].getContext().init(
            ::zserio::StdIntArrayTraits<uint8_t>(), m_age_);
    contextNode.getChildren()[2].getContext().init(
            ::zserio::StdIntArrayTraits<uint16_t>(), m_salary_);
    if (isBonusSet())
    {
        contextNode.getChildren()[3].getContext().init(
                ::zserio::StdIntArrayTraits<uint16_t>(), m_bonus_.value());
    }
    ::zserio::initPackingContext(contextNode.getChildren()[4],
            m_role_);
}

size_t Employee::bitSizeOf(size_t bitPosition) const
{
    size_t endBitPosition = bitPosition;

    endBitPosition += UINT8_C(8);
    endBitPosition += ::zserio::bitSizeOfString(m_name_);
    endBitPosition += UINT8_C(16);
    endBitPosition += 1;
    if (isBonusSet())
    {
        endBitPosition += UINT8_C(16);
    }
    endBitPosition += ::zserio::bitSizeOf(m_role_);
    if (getRole() == ::tutorial::Role::DEVELOPER)
    {
        endBitPosition += m_skills_.value().bitSizeOf(endBitPosition);
    }

    return endBitPosition - bitPosition;
}

size_t Employee::bitSizeOf(::zserio::PackingContextNode& contextNode, size_t bitPosition) const
{
    size_t endBitPosition = bitPosition;

    endBitPosition += contextNode.getChildren()[0].getContext().bitSizeOf(
            ::zserio::StdIntArrayTraits<uint8_t>(), m_age_);
    endBitPosition += ::zserio::bitSizeOfString(m_name_);
    endBitPosition += contextNode.getChildren()[2].getContext().bitSizeOf(
            ::zserio::StdIntArrayTraits<uint16_t>(), m_salary_);
    endBitPosition += 1;
    if (isBonusSet())
    {
        endBitPosition += contextNode.getChildren()[3].getContext().bitSizeOf(
                ::zserio::StdIntArrayTraits<uint16_t>(), m_bonus_.value());
    }
    endBitPosition += ::zserio::bitSizeOf(
            contextNode.getChildren()[4], m_role_);
    if (getRole() == ::tutorial::Role::DEVELOPER)
    {
        endBitPosition += m_skills_.value().bitSizeOfPacked(endBitPosition);
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
    if (isBonusSet())
    {
        endBitPosition += UINT8_C(16);
    }
    endBitPosition = ::zserio::initializeOffsets(endBitPosition, m_role_);
    if (getRole() == ::tutorial::Role::DEVELOPER)
    {
        endBitPosition = m_skills_.value().initializeOffsets(
                endBitPosition);
    }

    return endBitPosition;
}

size_t Employee::initializeOffsets(::zserio::PackingContextNode& contextNode, size_t bitPosition)
{
    size_t endBitPosition = bitPosition;

    endBitPosition += contextNode.getChildren()[0].getContext().bitSizeOf(
            ::zserio::StdIntArrayTraits<uint8_t>(), m_age_);
    endBitPosition += ::zserio::bitSizeOfString(m_name_);
    endBitPosition += contextNode.getChildren()[2].getContext().bitSizeOf(
            ::zserio::StdIntArrayTraits<uint16_t>(), m_salary_);
    endBitPosition += 1;
    if (isBonusSet())
    {
        endBitPosition += contextNode.getChildren()[3].getContext().bitSizeOf(
                ::zserio::StdIntArrayTraits<uint16_t>(), m_bonus_.value());
    }
    endBitPosition = ::zserio::initializeOffsets(
            contextNode.getChildren()[4], endBitPosition, m_role_);
    if (getRole() == ::tutorial::Role::DEVELOPER)
    {
        endBitPosition = m_skills_.value().initializeOffsetsPacked(
                endBitPosition);
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
                ((!isBonusUsed()) ? !other.isBonusUsed() : (m_bonus_ == other.m_bonus_)) &&
                (m_role_ == other.m_role_) &&
                ((!isSkillsUsed()) ? !other.isSkillsUsed() : (m_skills_ == other.m_skills_));
    }

    return true;
}

uint32_t Employee::hashCode() const
{
    uint32_t result = ::zserio::HASH_SEED;

    result = ::zserio::calcHashCode(result, m_age_);
    result = ::zserio::calcHashCode(result, m_name_);
    result = ::zserio::calcHashCode(result, m_salary_);
    if (isBonusUsed())
        result = ::zserio::calcHashCode(result, m_bonus_);
    result = ::zserio::calcHashCode(result, m_role_);
    if (isSkillsUsed())
        result = ::zserio::calcHashCode(result, m_skills_);

    return result;
}

void Employee::write(::zserio::BitStreamWriter& out) const
{
    // check constraint
    if (!(getAge() <= 65))
        throw ::zserio::ConstraintException("Write: Constraint violated at Employee.age!");
    out.writeBits(m_age_, UINT8_C(8));

    out.writeString(m_name_);

    out.writeBits(m_salary_, UINT8_C(16));

    if (isBonusSet())
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
        m_skills_.value().write(out);
    }
}

void Employee::write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out) const
{
    // check constraint
    if (!(getAge() <= 65))
        throw ::zserio::ConstraintException("Write: Constraint violated at Employee.age!");
    contextNode.getChildren()[0].getContext().write(
            ::zserio::StdIntArrayTraits<uint8_t>(), out, m_age_);

    out.writeString(m_name_);

    contextNode.getChildren()[2].getContext().write(
            ::zserio::StdIntArrayTraits<uint16_t>(), out, m_salary_);

    if (isBonusSet())
    {
        out.writeBool(true);
        contextNode.getChildren()[3].getContext().write(
                ::zserio::StdIntArrayTraits<uint16_t>(), out, m_bonus_.value());
    }
    else
    {
        out.writeBool(false);
    }

    ::zserio::write(contextNode.getChildren()[4], out, m_role_);

    if (getRole() == ::tutorial::Role::DEVELOPER)
    {
        m_skills_.value().writePacked(out);
    }
}

uint8_t Employee::readAge(::zserio::BitStreamReader& in)
{
    uint8_t readField = static_cast<uint8_t>(in.readBits(UINT8_C(8)));
    // check constraint
    if (!(readField <= 65))
        throw ::zserio::ConstraintException("Read: Constraint violated at Employee.age!");

    return readField;
}

uint8_t Employee::readAge(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in)
{
    uint8_t readField = contextNode.getChildren()[0].getContext().read(::zserio::StdIntArrayTraits<uint8_t>(), in);
    // check constraint
    if (!(readField <= 65))
        throw ::zserio::ConstraintException("Read: Constraint violated at Employee.age!");

    return readField;
}

::zserio::string<> Employee::readName(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    return static_cast<::zserio::string<>>(in.readString(allocator));
}

uint16_t Employee::readSalary(::zserio::BitStreamReader& in)
{
    return static_cast<uint16_t>(in.readBits(UINT8_C(16)));
}

uint16_t Employee::readSalary(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in)
{
    return contextNode.getChildren()[2].getContext().read(::zserio::StdIntArrayTraits<uint16_t>(), in);
}

::zserio::InplaceOptionalHolder<uint16_t> Employee::readBonus(::zserio::BitStreamReader& in)
{
    if (in.readBool())
    {
        return ::zserio::InplaceOptionalHolder<uint16_t>(static_cast<uint16_t>(in.readBits(UINT8_C(16))));
    }

    return ::zserio::InplaceOptionalHolder<uint16_t>(::zserio::NullOpt);
}

::zserio::InplaceOptionalHolder<uint16_t> Employee::readBonus(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in)
{
    if (in.readBool())
    {
        return ::zserio::InplaceOptionalHolder<uint16_t>(contextNode.getChildren()[3].getContext().read(::zserio::StdIntArrayTraits<uint16_t>(), in));
    }

    return ::zserio::InplaceOptionalHolder<uint16_t>(::zserio::NullOpt);
}

::tutorial::Role Employee::readRole(::zserio::BitStreamReader& in)
{
    return ::zserio::read<::tutorial::Role>(in);
}

::tutorial::Role Employee::readRole(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in)
{
    return ::zserio::read<::tutorial::Role>(contextNode.getChildren()[4], in);
}

::zserio::InplaceOptionalHolder<Employee::ZserioArrayType_skills> Employee::readSkills(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    if (getRole() == ::tutorial::Role::DEVELOPER)
    {
        ZserioArrayType_skills readField(::zserio::ObjectArrayTraits<::tutorial::Experience, ZserioElementFactory_skills>(), allocator);
        readField.read(in, ZserioElementFactory_skills(*this));

        return ::zserio::InplaceOptionalHolder<ZserioArrayType_skills>(::std::move(readField));
    }

    return ::zserio::InplaceOptionalHolder<ZserioArrayType_skills>(::zserio::NullOpt);
}

::zserio::InplaceOptionalHolder<Employee::ZserioArrayType_skills> Employee::readSkills(::zserio::PackingContextNode&, ::zserio::BitStreamReader& in, const allocator_type& allocator)
{
    if (getRole() == ::tutorial::Role::DEVELOPER)
    {
        ZserioArrayType_skills readField(::zserio::ObjectArrayTraits<::tutorial::Experience, ZserioElementFactory_skills>(), allocator);
        readField.readPacked(in, ZserioElementFactory_skills(*this));

        return ::zserio::InplaceOptionalHolder<ZserioArrayType_skills>(::std::move(readField));
    }

    return ::zserio::InplaceOptionalHolder<ZserioArrayType_skills>(::zserio::NullOpt);
}

} // namespace tutorial

/**
 * Automatically generated by Zserio C++ extension version 2.10.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
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

Experience::Experience(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in, const allocator_type&) :
        m_yearsOfExperience_(readYearsOfExperience(contextNode, in)),
        m_programmingLanguage_(readProgrammingLanguage(contextNode, in))
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

void Experience::createPackingContext(::zserio::PackingContextNode& contextNode)
{
    contextNode.createChild().createContext();
    contextNode.createChild().createContext();
}

void Experience::initPackingContext(::zserio::PackingContextNode& contextNode) const
{
    contextNode.getChildren()[0].getContext().init(
            ::zserio::BitFieldArrayTraits<uint8_t>(static_cast<uint8_t>(UINT8_C(6))), m_yearsOfExperience_);
    ::zserio::initPackingContext(contextNode.getChildren()[1],
            m_programmingLanguage_);
}

size_t Experience::bitSizeOf(size_t bitPosition) const
{
    size_t endBitPosition = bitPosition;

    endBitPosition += UINT8_C(6);
    endBitPosition += ::zserio::bitSizeOf(m_programmingLanguage_);

    return endBitPosition - bitPosition;
}

size_t Experience::bitSizeOf(::zserio::PackingContextNode& contextNode, size_t bitPosition) const
{
    size_t endBitPosition = bitPosition;

    endBitPosition += contextNode.getChildren()[0].getContext().bitSizeOf(
            ::zserio::BitFieldArrayTraits<uint8_t>(static_cast<uint8_t>(UINT8_C(6))), m_yearsOfExperience_);
    endBitPosition += ::zserio::bitSizeOf(
            contextNode.getChildren()[1], m_programmingLanguage_);

    return endBitPosition - bitPosition;
}

size_t Experience::initializeOffsets(size_t bitPosition)
{
    size_t endBitPosition = bitPosition;

    endBitPosition += UINT8_C(6);
    endBitPosition = ::zserio::initializeOffsets(endBitPosition, m_programmingLanguage_);

    return endBitPosition;
}

size_t Experience::initializeOffsets(::zserio::PackingContextNode& contextNode, size_t bitPosition)
{
    size_t endBitPosition = bitPosition;

    endBitPosition += contextNode.getChildren()[0].getContext().bitSizeOf(
            ::zserio::BitFieldArrayTraits<uint8_t>(static_cast<uint8_t>(UINT8_C(6))), m_yearsOfExperience_);
    endBitPosition = ::zserio::initializeOffsets(
            contextNode.getChildren()[1], endBitPosition, m_programmingLanguage_);

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

void Experience::write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out) const
{
    contextNode.getChildren()[0].getContext().write(
            ::zserio::BitFieldArrayTraits<uint8_t>(static_cast<uint8_t>(UINT8_C(6))), out, m_yearsOfExperience_);
    ::zserio::write(contextNode.getChildren()[1], out, m_programmingLanguage_);
}

uint8_t Experience::readYearsOfExperience(::zserio::BitStreamReader& in)
{
    return static_cast<uint8_t>(in.readBits(UINT8_C(6)));
}

uint8_t Experience::readYearsOfExperience(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in)
{
    return contextNode.getChildren()[0].getContext().read(::zserio::BitFieldArrayTraits<uint8_t>(static_cast<uint8_t>(UINT8_C(6))), in);
}

::tutorial::Language Experience::readProgrammingLanguage(::zserio::BitStreamReader& in)
{
    return ::zserio::read<::tutorial::Language>(in);
}

::tutorial::Language Experience::readProgrammingLanguage(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in)
{
    return ::zserio::read<::tutorial::Language>(contextNode.getChildren()[1], in);
}

} // namespace tutorial
