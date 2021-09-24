/**
 * SerializeUtil.h is not used by generated code and is provided only for user convenience.
 *
 * \note Please note that file operations allocate memory as needed and are not designed to use allocators.
 */

#ifndef ZSERIO_SERIALIZE_UTIL_H_INC
#define ZSERIO_SERIALIZE_UTIL_H_INC

#include <type_traits>

#include "zserio/BitStreamReader.h"
#include "zserio/BitStreamWriter.h"
#include "zserio/FileUtil.h"
#include "zserio/PreWriteAction.h"

namespace zserio
{

namespace detail
{

template <typename T>
using void_t = void;

template <typename T, typename = void>
struct has_initialize_children : std::false_type
{};

template <typename T>
struct has_initialize_children<T, void_t<decltype(&T::initializeChildren)>> : std::true_type
{};

template <typename T>
void initializeChildren(std::true_type, T& object)
{
    object.initializeChildren();
}

template <typename T>
void initializeChildren(std::false_type, T&)
{}

template <typename T>
void initializeChildren(T& object)
{
    initializeChildren(has_initialize_children<T>(), object);
}

} // namespace detail

/**
 * Serializes given generated object to bit buffer.
 *
 * \param object Generated object to serialize.
 * \param allocator Allocator to use to allocate bit buffer.
 *
 * \return Bit buffer containing the serialized object.
 *
 * \throw CppRuntimeException When serialization fails.
 */
template <typename T, typename ALLOC = std::allocator<uint8_t>,
        typename std::enable_if<!std::is_enum<T>::value, int>::type = 0>
BasicBitBuffer<ALLOC> serialize(T& object, const ALLOC& allocator = ALLOC())
{
    detail::initializeChildren(object);
    BasicBitBuffer<ALLOC> bitBuffer(object.initializeOffsets(0), allocator);
    BitStreamWriter writer(bitBuffer);
    object.write(writer, PreWriteAction::NO_PRE_WRITE_ACTION);
    return bitBuffer;
}

/**
 * Serializes given generated enum to bit buffer.
 *
 * \param enumValue Generated enum to serialize.
 * \param allocator Allocator to use to allocate bit buffer.
 *
 * \return Bit buffer containing the serialized enum.
 *
 * \throw CppRuntimeException When serialization fails.
 */
template <typename T, typename ALLOC = std::allocator<uint8_t>,
        typename std::enable_if<std::is_enum<T>::value, int>::type = 0>
BasicBitBuffer<ALLOC> serialize(T enumValue, const ALLOC& allocator = ALLOC())
{
    BasicBitBuffer<ALLOC> bitBuffer(zserio::bitSizeOf(enumValue), allocator);
    BitStreamWriter writer(bitBuffer);
    zserio::write(writer, enumValue);
    return bitBuffer;
}

/**
 * Deserializes given bit buffer to instance of generated object.
 *
 * \param bitBuffer Bit buffer to use.
 * \param arguments Object's actual paramters and/or allocator (all optional).
 *
 * \return Generated object created from the given bit buffer.
 *
 * \throw CppRuntimeException When deserialization fails.
 */
template <typename T, typename ALLOC, typename ...ARGS>
typename std::enable_if<!std::is_enum<T>::value, T>::type deserialize(
        const BasicBitBuffer<ALLOC>& bitBuffer, ARGS&&... arguments)
{
    BitStreamReader reader(bitBuffer);
    return T(reader, std::forward<ARGS>(arguments)...);
}

/**
 * Deserializes given bit buffer to instance of generated enum.
 *
 * \param bitBuffer Bit buffer to use.
 *
 * \return Generated enum created from the given bit buffer.
 *
 * \throw CppRuntimeException When deserialization fails.
 */
template <typename T, typename ALLOC>
typename std::enable_if<std::is_enum<T>::value, T>::type deserialize(const BasicBitBuffer<ALLOC>& bitBuffer)
{
    BitStreamReader reader(bitBuffer);
    return zserio::read<T>(reader);
}

/**
 * Serializes given generated object to file.
 *
 * \param object Generated object to serialize.
 * \param fileName File name to write.
 *
 * \throw CppRuntimeException When serialization fails.
 */
template <typename T>
void serializeToFile(T& object, const std::string& fileName)
{
    const BitBuffer bitBuffer = serialize(object);
    writeBufferToFile(bitBuffer, fileName);
}

/**
 * Deserializes given file contents to instance of generated object.
 *
 * \param fileName File to use.
 * \param arguments Object's arguments (optional).
 *
 * \return Generated object created from the given file contents.
 *
 * \throw CppRuntimeException When deserialization fails.
 */
template <typename T, typename ...ARGS>
T deserializeFromFile(const std::string& fileName, ARGS&&... arguments)
{
    const BitBuffer bitBuffer = readBufferFromFile(fileName);
    return deserialize<T>(bitBuffer, std::forward<ARGS>(arguments)...);
}

} // namespace zserio

#endif // ZSERIO_SERIALIZE_UTIL_H_INC
