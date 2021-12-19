#ifndef RING_H
#define RING_H

#include <stdbool.h>
#include <stddef.h> // size_t

// an unsafe evicting ring.
typedef struct ring_unsafe_t
{
	int head;
	int tail;
	int capacity;
	size_t item_size;
	char *data;
} ring_unsafe_t;

// creates a new ring with the specified item size and fixed capacity.
ring_unsafe_t *ring_unsafe_new(size_t item_size, int capacity);

// frees the memory allocated to the ring.
void ring_unsafe_free(ring_unsafe_t *ring);

// writes into index the index where a new item would be inserted. returns false if the ring is full.
bool ring_unsafe_push_back(ring_unsafe_t *ring, int *index);

// returns the index where an item should be read from.
int ring_unsafe_pop_front(ring_unsafe_t *ring);

int ring_unsafe_pop(ring_unsafe_t *ring);

// returns the index where the item at the specified position in the ring is stored.
int ring_unsafe_get(ring_unsafe_t *ring, int pos);

// returns the lenght of the ring.
size_t ring_unsafe_len(ring_unsafe_t *ring);

#define RING_DECLARE_TYPE(TYPE) RING_DECLARE_TYPE_NAME(TYPE, TYPE)

#define RING_DECLARE_TYPE_NAME(TYPE, NAME)                              \
	typedef struct ring_##NAME##_t                                      \
	{                                                                   \
		int head;                                                       \
		int tail;                                                       \
		int capacity;                                                   \
		size_t item_size;                                               \
		TYPE *data;                                                     \
	} ring_##NAME##_t;                                                  \
	ring_##NAME##_t *ring_##NAME##_new(int capacity);                   \
	bool ring_##NAME##_push_back(ring_##NAME##_t *ring, TYPE item);     \
	TYPE ring_##NAME##_pop_front(ring_##NAME##_t *ring);                \
	TYPE ring_##NAME##_get(ring_##NAME##_t *ring, int pos);             \
	TYPE ring_##NAME##_set(ring_##NAME##_t *ring, int pos, TYPE value); \
	size_t ring_##NAME##_len(ring_##NAME##_t *ring);                    \
	void ring_##NAME##_free(ring_##NAME##_t *ring);

#define RING_IMPL_TYPE(TYPE) RING_IMPL_TYPE_NAME(TYPE, TYPE)

#define RING_IMPL_TYPE_NAME(TYPE, NAME)                                    \
	ring_##NAME##_t *ring_##NAME##_new(int capacity)                       \
	{                                                                      \
		return (ring_##NAME##_t *)ring_unsafe_new(sizeof(TYPE), capacity); \
	}                                                                      \
	bool ring_##NAME##_push_back(ring_##NAME##_t *ring, TYPE item)         \
	{                                                                      \
		int index;                                                         \
		if (!ring_unsafe_push_back((ring_unsafe_t *)ring, &index))         \
			return false;                                                  \
		ring->data[index] = item;                                          \
		return true;                                                       \
	}                                                                      \
	TYPE ring_##NAME##_pop_front(ring_##NAME##_t *ring)                    \
	{                                                                      \
		int index = ring_unsafe_pop_front((ring_unsafe_t *)ring);          \
		return ring->data[index];                                          \
	}                                                                      \
	TYPE ring_##NAME##_pop(ring_##NAME##_t *ring)                          \
	{                                                                      \
		int index = ring_unsafe_pop((ring_unsafe_t *)ring);                \
		return ring->data[index];                                          \
	}                                                                      \
	TYPE ring_##NAME##_get(ring_##NAME##_t *ring, int pos)                 \
	{                                                                      \
		int index = ring_unsafe_get((ring_unsafe_t *)ring, pos);           \
		return ring->data[index];                                          \
	}                                                                      \
	TYPE ring_##NAME##_set(ring_##NAME##_t *ring, int pos, TYPE value)     \
	{                                                                      \
		int index = ring_unsafe_get((ring_unsafe_t *)ring, pos);           \
		TYPE old = ring->data[index];                                      \
		ring->data[index] = value;                                         \
		return old;                                                        \
	}                                                                      \
	size_t ring_##NAME##_len(ring_##NAME##_t *ring)                        \
	{                                                                      \
		return ring_unsafe_len((ring_unsafe_t *)ring);                     \
	}                                                                      \
	void ring_##NAME##_free(ring_##NAME##_t *ring)                         \
	{                                                                      \
		ring_unsafe_free((ring_unsafe_t *)ring);                           \
	}

#endif // RING_H
