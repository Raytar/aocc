#ifndef VEC_H
#define VEC_H

typedef struct vec_t
{
	void **data;
	int capacity;
	int size;
} vec_t;

// Allocates a new vector with the default capacity.
vec_t *vec_new();

// Allocates a new vector with the specified capacity.
vec_t *vec_new_with_capacity(int capacity);

// Frees the memory allocated to the vector.
void vec_free(vec_t *v);

void vec_size(vec_t *v);

void *vec_get(vec_t *v, int index);

void *vec_set(vec_t *v, int index, void *item);

void vec_insert(vec_t *v, int index, void *item);

void *vec_remove(vec_t *v, int index);

void vec_clear(vec_t *v);

void vec_push_back(vec_t *v, void *item);

void *vec_pop_back(vec_t *v);

void vec_ensure_capacity(vec_t *v, int capacity);

#endif // VEC_H
