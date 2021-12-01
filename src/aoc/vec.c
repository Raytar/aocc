#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "vec.h"

const int INITIAL_CAPACITY = 100;

static void bounds_check(int size, int index)
{
	if (index < 0 || index >= size)
	{
		panicf("vec: index %d out of bounds for size %d", index, size);
	}
}

static void grow_capacity(vec_unsafe_t *v, int needed_capacity)
{
	if (v->capacity < needed_capacity)
	{
		vec_unsafe_ensure_capacity(v, needed_capacity + v->capacity / 2);
	}
}

vec_unsafe_t *vec_unsafe_new(size_t item_size)
{
	return vec_unsafe_new_with_capacity(item_size, INITIAL_CAPACITY);
}

vec_unsafe_t *vec_unsafe_new_with_capacity(size_t item_size, int capacity)
{
	vec_unsafe_t *v = malloc(sizeof(vec_unsafe_t));
	v->capacity = capacity;
	v->size = 0;
	v->item_size = item_size;
	v->data = malloc(capacity * item_size);
	return v;
}

void vec_unsafe_free(vec_unsafe_t *v)
{
	free(v->data);
	free(v);
}

int vec_unsafe_size(vec_unsafe_t *v)
{
	return v->size;
}

int vec_unsafe_index(vec_unsafe_t *v, int index)
{
	bounds_check(v->size, index);
	return index;
}

int vec_unsafe_insert(vec_unsafe_t *v, int index)
{
	// permit the vec to grow by one item
	bounds_check(v->size + 1, index);
	vec_unsafe_ensure_capacity(v, v->size + 1);

	if (index < v->size)
	{
		memmove(v->data + (index + 1) * v->item_size, v->data + index * v->item_size, (v->size - index) * v->item_size);
	}

	v->size++;
	return index;
}

void vec_unsafe_remove(vec_unsafe_t *v, int index)
{
	bounds_check(v->size, index);

	if (index < v->size - 1)
	{
		memmove(v->data + index * v->item_size, v->data + (index + 1) * v->item_size, (v->size - (index + 1)) * v->item_size);
	}
	v->size--;
}

void vec_unsafe_clear(vec_unsafe_t *v)
{
	v->size = 0;
}

int vec_unsafe_push_back(vec_unsafe_t *v)
{
	grow_capacity(v, v->size + 1);
	int index = v->size;
	v->size++;
	return index;
}

void vec_unsafe_pop_back(vec_unsafe_t *v)
{
	if (v->size < 1)
	{
		return;
	}
	v->size--;
}

void vec_unsafe_ensure_capacity(vec_unsafe_t *v, int capacity)
{
	if (v->capacity < capacity)
	{
		v->data = realloc(v->data, capacity * v->item_size);
		v->capacity = capacity;
	}
}
