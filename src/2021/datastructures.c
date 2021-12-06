#include "datastructures.h"

QUEUE_IMPL_TYPE_NAME(int64_t, int64)

VEC_IMPL_TYPE_NAME(uint8_t, uint8)

int cmp_uint8(const uint8_t *a, const uint8_t *b)
{
	return *a - *b;
}
