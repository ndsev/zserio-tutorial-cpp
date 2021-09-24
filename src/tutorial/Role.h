/**
 * Automatically generated by Zserio C++ extension version 2.4.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#ifndef TUTORIAL_ROLE_H
#define TUTORIAL_ROLE_H

#include <array>

#include <zserio/Enums.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/PackingContext.h>
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
};

template <>
size_t enumToOrdinal<::tutorial::Role>(::tutorial::Role value);

template <>
::tutorial::Role valueToEnum<::tutorial::Role>(
        typename ::std::underlying_type<::tutorial::Role>::type rawValue);

template <>
size_t bitSizeOf<::tutorial::Role>(::tutorial::Role);

template <>
size_t bitSizeOf<::zserio::PackingContextNode, ::tutorial::Role>(
        ::zserio::PackingContextNode& contextNode, size_t bitPosition, ::tutorial::Role value);

template <>
size_t initializeOffsets<::tutorial::Role>(size_t bitPosition, ::tutorial::Role value);

template <>
size_t initializeOffsets<::zserio::PackingContextNode, ::tutorial::Role>(
        ::zserio::PackingContextNode& contextNode, size_t bitPosition, ::tutorial::Role value);

template <>
::tutorial::Role read<::tutorial::Role>(::zserio::BitStreamReader& in);

template <>
::tutorial::Role read<::tutorial::Role, ::zserio::PackingContextNode>(
        ::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in);

template <>
void write<::tutorial::Role>(BitStreamWriter& out, ::tutorial::Role value);

template <>
void write<::zserio::PackingContextNode, ::tutorial::Role>(
        ::zserio::PackingContextNode& contextNode, BitStreamWriter& out, ::tutorial::Role value);

} // namespace zserio

#endif // TUTORIAL_ROLE_H
