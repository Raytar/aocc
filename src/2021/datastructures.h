#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <stdint.h>
#include <aoc/queue.h>
#include <aoc/vec.h>

QUEUE_DECLARE_TYPE_NAME(int64_t, int64)

VEC_DECLARE_TYPE_NAME(uint8_t, uint8)
VEC_DECLARE_TYPE_NAME(uint16_t, uint16)

DECLARE_INT_CMP(uint8_t, uint8)
DECLARE_INT_CMP(uint16_t, uint16)

#endif // DATASTRUCTURES_H
