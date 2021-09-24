#ifndef ZSERIO_PMR_ANY_HOLDER_H_INC
#define ZSERIO_PMR_ANY_HOLDER_H_INC

#include "zserio/AnyHolder.h"
#include "zserio/pmr/PolymorphicAllocator.h"

namespace zserio
{
namespace pmr
{

using AnyHolder = zserio::AnyHolder<PropagatingPolymorphicAllocator<uint8_t>>;

} // namespace pmr
} // namespace zserio

#endif // ZSERIO_PMR_ANY_HOLDER_H_INC
