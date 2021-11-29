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

static void grow_capacity(vec_t *v, int needed_capacity)
{
	if (v->capacity < needed_capacity)
	{
		vec_ensure_capacity(v, needed_capacity + v->capacity / 2);
	}
}

vec_t *vec_new()
{
	return vec_new_with_capacity(INITIAL_CAPACITY);
}

vec_t *vec_new_with_capacity(int capacity)
{
	vec_t *v = malloc(sizeof(vec_t));
	v->capacity = capacity;
	v->size = 0;
	v->data = malloc(capacity * sizeof(void *));
	return v;
}

void vec_free(vec_t *v)
{
	free(v->data);
	free(v);
}

int vec_size(vec_t *v)
{
	return v->size;
}

void *vec_get(vec_t *v, int index)
{
	bounds_check(v->size, index);
	return v->data[index];
}

void *vec_set(vec_t *v, int index, void *item)
{
	bounds_check(v->size, index);
	void *old = v->data[index];
	v->data[index] = item;
	return old;
}

void vec_insert(vec_t *v, int index, void *item)
{
	// permit the vec to grow by one item
	bounds_check(v->size + 1, index);
	vec_ensure_capacity(v, v->size + 1);

	if (index < v->size)
	{
		memmove(v->data + index + 1, v->data + index, (v->size - index) * sizeof(void *));
	}

	v->data[index] = item;
	v->size++;
}

void *vec_remove(vec_t *v, int index)
{
	bounds_check(v->size, index);

	void *item = v->data[index];
	if (index < v->size - 1)
	{
		memmove(v->data + index, v->data + index + 1, (v->size - (index + 1)) * sizeof(void *));
	}
	v->size--;
	return item;
}

void vec_clear(vec_t *v)
{
	v->size = 0;
}

void vec_push_back(vec_t *v, void *item)
{
	grow_capacity(v, v->size + 1);
	v->data[v->size] = item;
	v->size++;
}

void *vec_pop_back(vec_t *v)
{
	if (v->size < 1)
	{
		return NULL;
	}
	void *item = v->data[v->size - 1];
	v->size--;
	return item;
}

void vec_ensure_capacity(vec_t *v, int capacity)
{
	if (v->capacity < capacity)
	{
		v->data = realloc(v->data, capacity * sizeof(void *));
		v->capacity = capacity;
	}
}
