/**
 * Automatically generated by Zserio C++ generator version 1.2.0 using Zserio core 2.16.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#ifndef TUTORIAL_ROLE_H
#define TUTORIAL_ROLE_H

#include <zserio/CppRuntimeVersion.h>
#if CPP_EXTENSION_RUNTIME_VERSION_NUMBER != 1002000
    #error Version mismatch between Zserio runtime library and Zserio C++ generator!
    #error Please update your Zserio runtime library to the version 1.2.0.
#endif

#include <array>

#include <zserio/Enums.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/ArrayTraits.h>
#include <zserio/Types.h>

namespace tutorial
{

enum class Role : uint8_t
{
    DEVELOPER = UINT8_C(0),
    TEAM_LEAD = UINT8_C(1),
    CTO = UINT8_C(2)
};

} // namespace tutorial

namespace zserio
{

// This is full specialization of enumeration traits and methods for Role enumeration.
template <>
struct EnumTraits<::tutorial::Role>
{
    static constexpr ::std::array<const char*, 3> names =
    {{
        "DEVELOPER",
        "TEAM_LEAD",
        "CTO"
    }};

    static constexpr ::std::array<::tutorial::Role, 3> values =
    {{
        ::tutorial::Role::DEVELOPER,
        ::tutorial::Role::TEAM_LEAD,
        ::tutorial::Role::CTO
    }};

    static constexpr const char* enumName = "Role";
};

template <>
size_t enumToOrdinal<::tutorial::Role>(::tutorial::Role value);

template <>
::tutorial::Role valueToEnum<::tutorial::Role>(
        typename ::std::underlying_type<::tutorial::Role>::type rawValue);

template <>
uint32_t enumHashCode<::tutorial::Role>(::tutorial::Role value);

template <>
size_t bitSizeOf<::tutorial::Role>(::tutorial::Role value);

template <>
size_t initializeOffsets<::tutorial::Role>(size_t bitPosition, ::tutorial::Role value);

template <>
::tutorial::Role read<::tutorial::Role>(::zserio::BitStreamReader& in);

template <>
void write<::tutorial::Role>(::zserio::BitStreamWriter& out, ::tutorial::Role value);

} // namespace zserio

#endif // TUTORIAL_ROLE_H
