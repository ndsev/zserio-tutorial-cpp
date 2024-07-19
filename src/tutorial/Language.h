/**
 * Automatically generated by Zserio C++ generator version 1.0.2 using Zserio core 2.14.1.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#ifndef TUTORIAL_LANGUAGE_H
#define TUTORIAL_LANGUAGE_H

#include <zserio/CppRuntimeVersion.h>
#if CPP_EXTENSION_RUNTIME_VERSION_NUMBER != 1000002
    #error Version mismatch between Zserio runtime library and Zserio C++ generator!
    #error Please update your Zserio runtime library to the version 1.0.2.
#endif

#include <array>

#include <zserio/Enums.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
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

    static constexpr const char* enumName = "Language";
};

template <>
size_t enumToOrdinal<::tutorial::Language>(::tutorial::Language value);

template <>
::tutorial::Language valueToEnum<::tutorial::Language>(
        typename ::std::underlying_type<::tutorial::Language>::type rawValue);

template <>
uint32_t enumHashCode<::tutorial::Language>(::tutorial::Language value);

template <>
size_t bitSizeOf<::tutorial::Language>(::tutorial::Language value);

template <>
size_t initializeOffsets<::tutorial::Language>(size_t bitPosition, ::tutorial::Language value);

template <>
::tutorial::Language read<::tutorial::Language>(::zserio::BitStreamReader& in);

template <>
void write<::tutorial::Language>(::zserio::BitStreamWriter& out, ::tutorial::Language value);

} // namespace zserio

#endif // TUTORIAL_LANGUAGE_H
