#include <stdlib.h> // malloc and free

#include "common.h"
#include "ring.h"

ring_unsafe_t *ring_unsafe_new(size_t item_size, int capacity)
{
	if (capacity < 1)
		panic("ring length must be 1 or greater");

	ring_unsafe_t *ring = malloc(sizeof(ring_unsafe_t));
	ring->head = -1;
	ring->tail = -1;
	ring->capacity = capacity;
	ring->item_size = item_size;
	ring->data = malloc(capacity * item_size);
	return ring;
}

void ring_unsafe_free(ring_unsafe_t *ring)
{
	free(ring->data);
	free(ring);
}

bool ring_unsafe_push_back(ring_unsafe_t *ring, int *index)
{
	int pos = ring->tail + 1;
	if (pos == ring->capacity)
		pos = 0; // wrap around
	if (pos == ring->head)
		return false;
	ring->tail = pos;
	if (ring->head == -1)
		ring->head = pos;
	*index = pos;
	return true;
}

int ring_unsafe_pop_front(ring_unsafe_t *ring)
{
	int index = ring->head;
	if (index == -1)
		return -1;
	if (ring->head == ring->tail)
	{
		ring->head = -1;
		ring->tail = -1;
	}
	else
	{
		ring->head++;
		if (ring->head == ring->capacity)
			ring->head = 0;
	}
	return index;
}

int ring_unsafe_pop(ring_unsafe_t *ring)
{
	int index = ring->head;
	if (index == -1)
		return -1;
	if (ring->head == ring->tail)
	{
		ring->head = -1;
		ring->tail = -1;
	}
	else
	{
		ring->head++;
		if (ring->head == ring->capacity)
			ring->head = 0;
	}
	return index;
}

int ring_unsafe_get(ring_unsafe_t *ring, int pos)
{
	size_t len = ring_unsafe_len(ring);
	if (pos < 0 || pos >= (int)len)
		panicf("cannot access ring item at position %d for ring length %zu", pos, len);
	return (ring->head + pos) % ring->capacity;
}

size_t ring_unsafe_len(ring_unsafe_t *ring)
{
	if (ring->head == -1)
		return 0;
	else if (ring->head <= ring->tail)
		return ring->tail - ring->head + 1;
	else
		return ring->capacity - ring->head + ring->tail + 1;
}
