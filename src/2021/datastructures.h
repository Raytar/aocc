#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <stdint.h>
#include <aoc/queue.h>
#include <aoc/vec.h>

QUEUE_DECLARE_TYPE_NAME(int64_t, int64)

VEC_DECLARE_TYPE_NAME(uint8_t, uint8)

int cmp_uint8(const uint8_t *a, const uint8_t *b);

#endif // DATASTRUCTURES_H
