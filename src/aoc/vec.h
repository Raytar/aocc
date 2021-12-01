#ifndef VEC_H
#define VEC_H

#include <stddef.h>

#include "common.h"

typedef struct vec_t
{
	int capacity;
	int size;
	size_t item_size;
	char *data;
} vec_t;

// Allocates a new vector with the default capacity.
vec_t *_vec_new(size_t item_size);

// Allocates a new vector with the specified capacity.
vec_t *_vec_new_with_capacity(size_t item_size, int capacity);

// Frees the memory allocated to the vector.
void _vec_free(vec_t *v);

int _vec_size(vec_t *v);

int _vec_index(vec_t *v, int index);

int _vec_insert(vec_t *v, int index);

void _vec_remove(vec_t *v, int index);

void _vec_clear(vec_t *v);

int _vec_push_back(vec_t *v);

void _vec_pop_back(vec_t *v);

void _vec_ensure_capacity(vec_t *v, int capacity);

#define VEC_DECLARE_TYPE(TYPE) VEC_DECLARE_TYPE_NAME(TYPE, TYPE)

#define VEC_DECLARE_TYPE_NAME(TYPE, NAME)                                                                \
	typedef struct vec_##NAME##_t                                                                        \
	{                                                                                                    \
		int capacity;                                                                                    \
		int size;                                                                                        \
		size_t item_size;                                                                                \
		TYPE *data;                                                                                      \
	} vec_##NAME##_t;                                                                                    \
                                                                                                         \
	/* Creates a new vector of TYPE. */                                                                  \
	vec_##NAME##_t *vec_##NAME##_new();                                                                  \
	/* Creates a new vector of TYPE with the specified capacity. */                                      \
	vec_##NAME##_t *vec_##NAME##_new_with_capacity(int capacity);                                        \
	/* Frees the vector */                                                                               \
	void vec_##NAME##_free(vec_##NAME##_t *vec);                                                         \
	/* Clears the vector. This simply sets the size to zero. */                                          \
	void vec_##NAME##_clear(vec_##NAME##_t *vec);                                                        \
	/* Returns the number of items in the vector. */                                                     \
	size_t vec_##NAME##_size(vec_##NAME##_t *vec);                                                       \
	/* Returns the TYPE */                                                                               \
	TYPE vec_##NAME##_get(vec_##NAME##_t *vec, int index);                                               \
	/* Replaces the old value at the specified index with the new value, returns the old value.  */      \
	TYPE vec_##NAME##_set(vec_##NAME##_t *vec, int index, TYPE item);                                    \
	/* Inserts the item at the specified index, making space by moving other items as necessary. */      \
	void vec_##NAME##_insert(vec_##NAME##_t *vec, int index, TYPE item);                                 \
	/* Removes the item at the specified index. */                                                       \
	TYPE vec_##NAME##_remove(vec_##NAME##_t *vec, int index);                                            \
	/* Appends an item to the vector. */                                                                 \
	void vec_##NAME##_push_back(vec_##NAME##_t *vec, TYPE item);                                         \
	/* Pops an item from the end of the vector. */                                                       \
	TYPE vec_##NAME##_pop_back(vec_##NAME##_t *vec);                                                     \
	/* Ensures that the vector has the specified capacity, allocating additional memory if necessary. */ \
	void vec_##NAME##_ensure_capacity(vec_##NAME##_t *vec, int capacity);

#define VEC_IMPL_TYPE(TYPE) VEC_IMPL_TYPE_NAME(TYPE, TYPE)

#define VEC_IMPL_TYPE_NAME(TYPE, NAME)                                           \
	vec_##NAME##_t *vec_##NAME##_new()                                           \
	{                                                                            \
		return (vec_##NAME##_t *)_vec_new(sizeof(TYPE));                         \
	}                                                                            \
	vec_##NAME##_t *vec_##NAME##_new_with_capacity(int capacity)                 \
	{                                                                            \
		return (vec_##NAME##_t *)_vec_new_with_capacity(sizeof(TYPE), capacity); \
	}                                                                            \
	void vec_##NAME##_free(vec_##NAME##_t *vec)                                  \
	{                                                                            \
		_vec_free((vec_t *)vec);                                                 \
	}                                                                            \
	void vec_##NAME##_clear(vec_##NAME##_t *vec)                                 \
	{                                                                            \
		_vec_clear((vec_t *)vec);                                                \
	}                                                                            \
	size_t vec_##NAME##_size(vec_##NAME##_t *vec)                                \
	{                                                                            \
		return _vec_size((vec_t *)vec);                                          \
	}                                                                            \
	TYPE vec_##NAME##_get(vec_##NAME##_t *vec, int index)                        \
	{                                                                            \
		return vec->data[_vec_index((vec_t *)vec, index)];                       \
	}                                                                            \
	TYPE vec_##NAME##_set(vec_##NAME##_t *vec, int index, TYPE item)             \
	{                                                                            \
		int i = _vec_index((vec_t *)vec, index);                                 \
		TYPE tmp = vec->data[i];                                                 \
		vec->data[i] = item;                                                     \
		return tmp;                                                              \
	}                                                                            \
	void vec_##NAME##_insert(vec_##NAME##_t *vec, int index, TYPE item)          \
	{                                                                            \
		int i = _vec_insert((vec_t *)vec, index);                                \
		vec->data[i] = item;                                                     \
	}                                                                            \
	TYPE vec_##NAME##_remove(vec_##NAME##_t *vec, int index)                     \
	{                                                                            \
		TYPE tmp = vec->data[index];                                             \
		_vec_remove((vec_t *)vec, index);                                        \
		return tmp;                                                              \
	}                                                                            \
	void vec_##NAME##_push_back(vec_##NAME##_t *vec, TYPE item)                  \
	{                                                                            \
		int index = _vec_push_back((vec_t *)vec);                                \
		vec->data[index] = item;                                                 \
	}                                                                            \
	TYPE vec_##NAME##_pop_back(vec_##NAME##_t *vec)                              \
	{                                                                            \
		int size = _vec_size((vec_t *)vec);                                      \
		if (size == 0)                                                           \
			panic("empty vector");                                               \
		TYPE tmp = vec->data[size - 1];                                          \
		_vec_pop_back((vec_t *)vec);                                             \
		return tmp;                                                              \
	}                                                                            \
	void vec_##NAME##_ensure_capacity(vec_##NAME##_t *vec, int capacity)         \
	{                                                                            \
		_vec_ensure_capacity((vec_t *)vec, capacity);                            \
	}

#endif // VEC_H
