/**
 * Automatically generated by Zserio C++ extension version 2.10.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#ifndef TUTORIAL_LANGUAGE_H
#define TUTORIAL_LANGUAGE_H

#include <array>

#include <zserio/Enums.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/PackingContext.h>
#include <zserio/ArrayTraits.h>
#include <zserio/Types.h>

namespace tutorial
{

enum class Language : uint8_t
{
    CPP = UINT8_C(0),
    JAVA = UINT8_C(1),
    PYTHON = UINT8_C(2),
    JS = UINT8_C(3)
};

} // namespace tutorial

namespace zserio
{

// This is full specialization of enumeration traits and methods for Language enumeration.
template <>
struct EnumTraits<::tutorial::Language>
{
    static constexpr ::std::array<const char*, 4> names =
    {{
        "CPP",
        "JAVA",
        "PYTHON",
        "JS"
    }};

    static constexpr ::std::array<::tutorial::Language, 4> values =
    {{
        ::tutorial::Language::CPP,
        ::tutorial::Language::JAVA,
        ::tutorial::Language::PYTHON,
        ::tutorial::Language::JS
    }};
};

template <>
size_t enumToOrdinal<::tutorial::Language>(::tutorial::Language value);

template <>
::tutorial::Language valueToEnum<::tutorial::Language>(
        typename ::std::underlying_type<::tutorial::Language>::type rawValue);

template <>
uint32_t enumHashCode<::tutorial::Language>(::tutorial::Language value);

template <>
void initPackingContext<::zserio::PackingContextNode, ::tutorial::Language>(
        ::zserio::PackingContextNode& contextNode, ::tutorial::Language value);

template <>
size_t bitSizeOf<::tutorial::Language>(::tutorial::Language value);

template <>
size_t bitSizeOf<::zserio::PackingContextNode, ::tutorial::Language>(
        ::zserio::PackingContextNode& contextNode, ::tutorial::Language value);

template <>
size_t initializeOffsets<::tutorial::Language>(size_t bitPosition, ::tutorial::Language value);

template <>
size_t initializeOffsets<::zserio::PackingContextNode, ::tutorial::Language>(
        ::zserio::PackingContextNode& contextNode, size_t bitPosition, ::tutorial::Language value);

template <>
::tutorial::Language read<::tutorial::Language>(::zserio::BitStreamReader& in);

template <>
::tutorial::Language read<::tutorial::Language, ::zserio::PackingContextNode>(
        ::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in);

template <>
void write<::tutorial::Language>(::zserio::BitStreamWriter& out, ::tutorial::Language value);

template <>
void write<::zserio::PackingContextNode, ::tutorial::Language>(
        ::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out, ::tutorial::Language value);

} // namespace zserio

#endif // TUTORIAL_LANGUAGE_H
