#ifndef ZSERIO_PMR_BIT_BUFFER_H_INC
#define ZSERIO_PMR_BIT_BUFFER_H_INC

#include "zserio/BitBuffer.h"
#include "zserio/pmr/PolymorphicAllocator.h"

namespace zserio
{
namespace pmr
{

using BitBuffer = zserio::BasicBitBuffer<PropagatingPolymorphicAllocator<uint8_t>>;

} // namespace pmr
} // namespace zserio

#endif // ZSERIO_PMR_BIT_BUFFER_H_INC
