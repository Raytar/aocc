#include "datastructures.h"

RING_IMPL_TYPE_NAME(int64_t, int64)

VEC_IMPL_TYPE_NAME(uint8_t, uint8)
VEC_IMPL_TYPE_NAME(uint16_t, uint16)
VEC_IMPL_TYPE(int)
VEC_IMPL_TYPE_NAME(const char *, str)

IMPL_INT_CMP(uint8_t, uint8)
IMPL_INT_CMP(uint16_t, uint16)
IMPL_INT_CMP(int, int)
IMPL_INT_CMP(char, char)
