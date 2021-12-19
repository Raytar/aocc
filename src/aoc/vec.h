#ifndef VEC_H
#define VEC_H

#include <stdlib.h>
#include <stddef.h>

#include "common.h"

typedef struct vec_unsafe_t
{
	int capacity;
	int size;
	size_t item_size;
	char *data;
} vec_unsafe_t;

// Allocates a new vector with the default capacity.
vec_unsafe_t *vec_unsafe_new(size_t item_size);

// Allocates a new vector with the specified capacity.
vec_unsafe_t *vec_unsafe_new_with_capacity(size_t item_size, int capacity);

// Frees the memory allocated to the vector.
void vec_unsafe_free(vec_unsafe_t *v);

int vec_unsafe_size(vec_unsafe_t *v);

int vec_unsafe_index(vec_unsafe_t *v, int index);

int vec_unsafe_insert(vec_unsafe_t *v, int index);

void vec_unsafe_remove(vec_unsafe_t *v, int index);

void vec_unsafe_clear(vec_unsafe_t *v);

int vec_unsafe_push_back(vec_unsafe_t *v);

void vec_unsafe_pop_front(vec_unsafe_t *v);

void vec_unsafe_ensure_capacity(vec_unsafe_t *v, int capacity);

void vec_unsafe_set_size(vec_unsafe_t *v, int size);

vec_unsafe_t *vec_unsafe_clone(vec_unsafe_t *v);

#define VEC_DECLARE_TYPE(TYPE) VEC_DECLARE_TYPE_NAME(TYPE, TYPE)

#define VEC_DECLARE_TYPE_NAME(TYPE, NAME)                                 \
	typedef struct vec_##NAME##_t                                         \
	{                                                                     \
		int capacity;                                                     \
		int size;                                                         \
		size_t item_size;                                                 \
		TYPE *data;                                                       \
	} vec_##NAME##_t;                                                     \
	vec_##NAME##_t *vec_##NAME##_new();                                   \
	vec_##NAME##_t *vec_##NAME##_new_with_capacity(int capacity);         \
	void vec_##NAME##_free(vec_##NAME##_t *vec);                          \
	void vec_##NAME##_clear(vec_##NAME##_t *vec);                         \
	size_t vec_##NAME##_size(vec_##NAME##_t *vec);                        \
	TYPE vec_##NAME##_get(vec_##NAME##_t *vec, int index);                \
	TYPE *vec_##NAME##_get_ptr(vec_##NAME##_t *vec, int index);           \
	TYPE vec_##NAME##_set(vec_##NAME##_t *vec, int index, TYPE item);     \
	void vec_##NAME##_insert(vec_##NAME##_t *vec, int index, TYPE item);  \
	TYPE vec_##NAME##_remove(vec_##NAME##_t *vec, int index);             \
	void vec_##NAME##_push_back(vec_##NAME##_t *vec, TYPE item);          \
	TYPE vec_##NAME##_pop_front(vec_##NAME##_t *vec);                     \
	void vec_##NAME##_ensure_capacity(vec_##NAME##_t *vec, int capacity); \
	void vec_##NAME##_set_size(vec_##NAME##_t *vec, int size);            \
	vec_##NAME##_t *vec_##NAME##_clone(vec_##NAME##_t *vec);              \
	void vec_##NAME##_sort(vec_##NAME##_t *vec, int (*cmp)(const TYPE *a, const TYPE *b));

#define VEC_IMPL_TYPE(TYPE) VEC_IMPL_TYPE_NAME(TYPE, TYPE)

#define VEC_IMPL_TYPE_NAME(TYPE, NAME)                                                    \
	vec_##NAME##_t *vec_##NAME##_new()                                                    \
	{                                                                                     \
		return (vec_##NAME##_t *)vec_unsafe_new(sizeof(TYPE));                            \
	}                                                                                     \
	vec_##NAME##_t *vec_##NAME##_new_with_capacity(int capacity)                          \
	{                                                                                     \
		return (vec_##NAME##_t *)vec_unsafe_new_with_capacity(sizeof(TYPE), capacity);    \
	}                                                                                     \
	void vec_##NAME##_free(vec_##NAME##_t *vec)                                           \
	{                                                                                     \
		vec_unsafe_free((vec_unsafe_t *)vec);                                             \
	}                                                                                     \
	void vec_##NAME##_clear(vec_##NAME##_t *vec)                                          \
	{                                                                                     \
		vec_unsafe_clear((vec_unsafe_t *)vec);                                            \
	}                                                                                     \
	size_t vec_##NAME##_size(vec_##NAME##_t *vec)                                         \
	{                                                                                     \
		return vec_unsafe_size((vec_unsafe_t *)vec);                                      \
	}                                                                                     \
	TYPE vec_##NAME##_get(vec_##NAME##_t *vec, int index)                                 \
	{                                                                                     \
		return vec->data[vec_unsafe_index((vec_unsafe_t *)vec, index)];                   \
	}                                                                                     \
	TYPE *vec_##NAME##_get_ptr(vec_##NAME##_t *vec, int index)                            \
	{                                                                                     \
		return &vec->data[vec_unsafe_index((vec_unsafe_t *)vec, index)];                  \
	}                                                                                     \
	TYPE vec_##NAME##_set(vec_##NAME##_t *vec, int index, TYPE item)                      \
	{                                                                                     \
		int i = vec_unsafe_index((vec_unsafe_t *)vec, index);                             \
		TYPE tmp = vec->data[i];                                                          \
		vec->data[i] = item;                                                              \
		return tmp;                                                                       \
	}                                                                                     \
	void vec_##NAME##_insert(vec_##NAME##_t *vec, int index, TYPE item)                   \
	{                                                                                     \
		int i = vec_unsafe_insert((vec_unsafe_t *)vec, index);                            \
		vec->data[i] = item;                                                              \
	}                                                                                     \
	TYPE vec_##NAME##_remove(vec_##NAME##_t *vec, int index)                              \
	{                                                                                     \
		TYPE tmp = vec->data[index];                                                      \
		vec_unsafe_remove((vec_unsafe_t *)vec, index);                                    \
		return tmp;                                                                       \
	}                                                                                     \
	void vec_##NAME##_push_back(vec_##NAME##_t *vec, TYPE item)                           \
	{                                                                                     \
		int index = vec_unsafe_push_back((vec_unsafe_t *)vec);                            \
		vec->data[index] = item;                                                          \
	}                                                                                     \
	TYPE vec_##NAME##_pop_front(vec_##NAME##_t *vec)                                      \
	{                                                                                     \
		int size = vec_unsafe_size((vec_unsafe_t *)vec);                                  \
		if (size == 0)                                                                    \
			panic("empty vector");                                                        \
		TYPE tmp = vec->data[size - 1];                                                   \
		vec_unsafe_pop_front((vec_unsafe_t *)vec);                                        \
		return tmp;                                                                       \
	}                                                                                     \
	void vec_##NAME##_ensure_capacity(vec_##NAME##_t *vec, int capacity)                  \
	{                                                                                     \
		vec_unsafe_ensure_capacity((vec_unsafe_t *)vec, capacity);                        \
	}                                                                                     \
	void vec_##NAME##_set_size(vec_##NAME##_t *vec, int size)                             \
	{                                                                                     \
		vec_unsafe_set_size((vec_unsafe_t *)vec, size);                                   \
	}                                                                                     \
	vec_##NAME##_t *vec_##NAME##_clone(vec_##NAME##_t *vec)                               \
	{                                                                                     \
		return (vec_##NAME##_t *)vec_unsafe_clone((vec_unsafe_t *)vec);                   \
	}                                                                                     \
	void vec_##NAME##_sort(vec_##NAME##_t *vec, int (*cmp)(const TYPE *a, const TYPE *b)) \
	{                                                                                     \
		qsort(vec->data, vec->size, vec->item_size, (cmp_fn)cmp);                         \
	}

#endif // VEC_H
