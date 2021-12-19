#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <stdint.h>
#include <aoc/ring.h>
#include <aoc/vec.h>

RING_DECLARE_TYPE_NAME(int64_t, int64)

VEC_DECLARE_TYPE_NAME(uint8_t, uint8)
VEC_DECLARE_TYPE_NAME(uint16_t, uint16)
VEC_DECLARE_TYPE(int)

VEC_DECLARE_TYPE_NAME(const char *, str)

DECLARE_INT_CMP(uint8_t, uint8)
DECLARE_INT_CMP(uint16_t, uint16)
DECLARE_INT_CMP(int, int)
DECLARE_INT_CMP(char, char)

#endif // DATASTRUCTURES_H
