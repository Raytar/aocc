#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h> // size_t

// an unsafe evicting queue.
typedef struct queue_unsafe_t
{
	int head;
	int tail;
	int capacity;
	size_t item_size;
	char *data;
} queue_unsafe_t;

// creates a new queue with the specified item size and fixed capacity.
queue_unsafe_t *queue_unsafe_new(size_t item_size, int capacity);

// frees the memory allocated to the queue.
void queue_unsafe_free(queue_unsafe_t *queue);

// writes into index the index where a new item would be inserted. returns false if the queue is full.
bool queue_unsafe_enqueue(queue_unsafe_t *queue, int *index);

// returns the index where an item should be read from.
int queue_unsafe_dequeue(queue_unsafe_t *queue);

// returns the index where the item at the specified position in the queue is stored.
int queue_unsafe_get(queue_unsafe_t *queue, int pos);

// returns the lenght of the queue.
size_t queue_unsafe_len(queue_unsafe_t *queue);

#define QUEUE_DECLARE_TYPE(TYPE) QUEUE_DECLARE_TYPE_NAME(TYPE, TYPE)

#define QUEUE_DECLARE_TYPE_NAME(TYPE, NAME)                          \
	typedef struct queue_##NAME##_t                                  \
	{                                                                \
		int head;                                                    \
		int tail;                                                    \
		int capacity;                                                \
		size_t item_size;                                            \
		TYPE *data;                                                  \
	} queue_##NAME##_t;                                              \
	queue_##NAME##_t *queue_##NAME##_new(int capacity);              \
	bool queue_##NAME##_enqueue(queue_##NAME##_t *queue, TYPE item); \
	TYPE queue_##NAME##_dequeue(queue_##NAME##_t *queue);            \
	TYPE queue_##NAME##_get(queue_##NAME##_t *queue, int pos);       \
	size_t queue_##NAME##_len(queue_##NAME##_t *queue);              \
	void queue_##NAME##_free(queue_##NAME##_t *queue);

#define QUEUE_IMPL_TYPE(TYPE) QUEUE_IMPL_TYPE_NAME(TYPE, TYPE)

#define QUEUE_IMPL_TYPE_NAME(TYPE, NAME)                                     \
	queue_##NAME##_t *queue_##NAME##_new(int capacity)                       \
	{                                                                        \
		return (queue_##NAME##_t *)queue_unsafe_new(sizeof(TYPE), capacity); \
	}                                                                        \
	bool queue_##NAME##_enqueue(queue_##NAME##_t *queue, TYPE item)          \
	{                                                                        \
		int index;                                                           \
		if (!queue_unsafe_enqueue((queue_unsafe_t *)queue, &index))          \
			return false;                                                    \
		queue->data[index] = item;                                           \
		return true;                                                         \
	}                                                                        \
	TYPE queue_##NAME##_dequeue(queue_##NAME##_t *queue)                     \
	{                                                                        \
		int index = queue_unsafe_dequeue((queue_unsafe_t *)queue);           \
		return queue->data[index];                                           \
	}                                                                        \
	TYPE queue_##NAME##_get(queue_##NAME##_t *queue, int pos)                \
	{                                                                        \
		int index = queue_unsafe_get((queue_unsafe_t *)queue, pos);          \
		return queue->data[index];                                           \
	}                                                                        \
	size_t queue_##NAME##_len(queue_##NAME##_t *queue)                       \
	{                                                                        \
		return queue_unsafe_len((queue_unsafe_t *)queue);                    \
	}                                                                        \
	void queue_##NAME##_free(queue_##NAME##_t *queue)                        \
	{                                                                        \
		queue_unsafe_free((queue_unsafe_t *)queue);                          \
	}

#endif // QUEUE_H
