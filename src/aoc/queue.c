#include <stdlib.h> // malloc and free

#include "common.h"
#include "queue.h"

queue_unsafe_t *queue_unsafe_new(size_t item_size, int capacity)
{
	if (capacity < 1)
		panic("queue length must be 1 or greater");

	queue_unsafe_t *queue = malloc(sizeof(queue_unsafe_t));
	queue->head = -1;
	queue->tail = -1;
	queue->capacity = capacity;
	queue->item_size = item_size;
	queue->data = malloc(capacity * item_size);
	return queue;
}

void queue_unsafe_free(queue_unsafe_t *queue)
{
	free(queue->data);
	free(queue);
}

bool queue_unsafe_enqueue(queue_unsafe_t *queue, int *index)
{
	int pos = queue->tail + 1;
	if (pos == queue->capacity)
		pos = 0; // wrap around
	if (pos == queue->head)
		return false;
	queue->tail = pos;
	if (queue->head == -1)
		queue->head = pos;
	*index = pos;
	return true;
}

int queue_unsafe_dequeue(queue_unsafe_t *queue)
{
	int index = queue->head;
	if (index == -1)
		return -1;
	if (queue->head == queue->tail)
	{
		queue->head = -1;
		queue->tail = -1;
	}
	else
	{
		queue->head++;
		if (queue->head == queue->capacity)
			queue->head = 0;
	}
	return index;
}

int queue_unsafe_get(queue_unsafe_t *queue, int pos)
{
	size_t len = queue_unsafe_len(queue);
	if (pos < 0 || pos >= (int)len)
		panicf("cannot access queue item at position %d for queue length %zu", pos, len);
	return (queue->head + pos) % queue->capacity;
}

size_t queue_unsafe_len(queue_unsafe_t *queue)
{
	if (queue->head == -1)
		return 0;
	else if (queue->head <= queue->tail)
		return queue->tail - queue->head + 1;
	else
		return queue->capacity - queue->head + queue->tail + 1;
}
