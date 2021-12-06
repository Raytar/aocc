#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h> // calloc, size_t
#include <stdbool.h>

#include "common.h"

#define HASHMAP_INITIAL_CAPACITY 101

enum entry_state
{
	HASHMAP_ENTRY_UNUSED,
	HASHMAP_ENTRY_AVAILABLE,
	HASHMAP_ENTRY_ASSIGNED,
};

size_t hash_str(const char *str);

#define HASHMAP_DECLARE_TYPE(KEY, VALUE) HASHMAP_DECLARE_TYPE_NAME(KEY, VALUE, KEY##_##VALUE)

#define HASHMAP_DECLARE_TYPE_NAME(KEY, VALUE, NAME)                               \
	typedef struct hashmap_##NAME##_entry_t                                       \
	{                                                                             \
		KEY key;                                                                  \
		VALUE value;                                                              \
		enum entry_state state;                                                   \
	} hashmap_##NAME##_entry_t;                                                   \
	typedef struct hashmap_##NAME##_t                                             \
	{                                                                             \
		int capacity;                                                             \
		int size;                                                                 \
		hashmap_##NAME##_entry_t *entries;                                        \
	} hashmap_##NAME##_t;                                                         \
	hashmap_##NAME##_t hashmap_##NAME##_new();                                    \
	hashmap_##NAME##_t hashmap_##NAME##_new_with_capacity(int capacity);          \
	void hashmap_##NAME##_free(hashmap_##NAME##_t *map);                          \
	void hashmap_##NAME##_insert(hashmap_##NAME##_t *map, KEY key, VALUE value);  \
	bool hashmap_##NAME##_get(hashmap_##NAME##_t *map, KEY key, VALUE *value);    \
	bool hashmap_##NAME##_remove(hashmap_##NAME##_t *map, KEY key, VALUE *value); \
	size_t hashmap_##NAME##_size(hashmap_##NAME##_t *map);                        \
	bool hashmap_##NAME##_iter(hashmap_##NAME##_t *map, size_t *pos, KEY *key, VALUE *value);

#define HASHMAP_IMPL_TYPE(KEY, VALUE, HASH, CMP) HASHMAP_IMPL_TYPE_NAME(KEY, VALUE, KEY##_##VALUE, HASH, CMP)

#define HASHMAP_IMPL_TYPE_NAME(KEY, VALUE, NAME, HASH, CMP)                                     \
	hashmap_##NAME##_t hashmap_##NAME##_new()                                                   \
	{                                                                                           \
		return hashmap_##NAME##_new_with_capacity(HASHMAP_INITIAL_CAPACITY);                    \
	}                                                                                           \
	hashmap_##NAME##_t hashmap_##NAME##_new_with_capacity(int capacity)                         \
	{                                                                                           \
		hashmap_##NAME##_t map = {                                                              \
			.capacity = capacity,                                                               \
			.size = 0,                                                                          \
			.entries = calloc(capacity, sizeof(hashmap_##NAME##_entry_t)),                      \
		};                                                                                      \
		return map;                                                                             \
	}                                                                                           \
	void hashmap_##NAME##_free(hashmap_##NAME##_t *map)                                         \
	{                                                                                           \
		free(map->entries);                                                                     \
	}                                                                                           \
	void hashmap_##NAME##_rehash(hashmap_##NAME##_t *map)                                       \
	{                                                                                           \
		hashmap_##NAME##_t new_map = hashmap_##NAME##_new_with_capacity(map->capacity * 2 + 1); \
		for (int i = 0; i < map->capacity; i++)                                                 \
		{                                                                                       \
			hashmap_##NAME##_entry_t *entry = &map->entries[i];                                 \
			if (entry->state != HASHMAP_ENTRY_ASSIGNED)                                         \
			{                                                                                   \
				continue;                                                                       \
			}                                                                                   \
			hashmap_##NAME##_insert(&new_map, entry->key, entry->value);                        \
		}                                                                                       \
		free(map->entries);                                                                     \
		*map = new_map;                                                                         \
	}                                                                                           \
	int hashmap_##NAME##_index_for(hashmap_##NAME##_t *map, KEY key)                            \
	{                                                                                           \
		/* Need to find an entry that has a matching key and is ASSIGNED */                     \
		int index = HASH(key) % map->capacity;                                                  \
		hashmap_##NAME##_entry_t *entry;                                                        \
		for (int i = 0; i < map->capacity; i++)                                                 \
		{                                                                                       \
			entry = &map->entries[index];                                                       \
			switch (entry->state)                                                               \
			{                                                                                   \
			case HASHMAP_ENTRY_ASSIGNED:                                                        \
				if (CMP(key, entry->key) == 0)                                                  \
					return index;                                                               \
				break;                                                                          \
			case HASHMAP_ENTRY_AVAILABLE:                                                       \
				break;                                                                          \
			case HASHMAP_ENTRY_UNUSED:                                                          \
				return -1;                                                                      \
			}                                                                                   \
			index += 2 * i + 1;                                                                 \
			index %= map->capacity;                                                             \
		}                                                                                       \
		return -1;                                                                              \
	}                                                                                           \
	void hashmap_##NAME##_insert(hashmap_##NAME##_t *map, KEY key, VALUE value)                 \
	{                                                                                           \
		if (((float)map->size) / map->capacity >= 0.75f)                                        \
			hashmap_##NAME##_rehash(map);                                                       \
		/* Need to find an entry that is either AVAILABLE or UNUSED */                          \
		/* or we could replace an ASSIGNED entry with a matching key. */                        \
		/* In the latter case, the old key and old value will be written */                     \
		/* to the respective pointer arguments if they are not NULL. */                         \
		/* This is done so that the old key and old value may be freed. */                      \
		int index = HASH(key) % map->capacity;                                                  \
		hashmap_##NAME##_entry_t *entry;                                                        \
		for (int i = 0; i < map->capacity; i++)                                                 \
		{                                                                                       \
			entry = &map->entries[index];                                                       \
			switch (entry->state)                                                               \
			{                                                                                   \
			case HASHMAP_ENTRY_ASSIGNED:                                                        \
				if (CMP(key, entry->key) != 0)                                                  \
					break;                                                                      \
			case HASHMAP_ENTRY_AVAILABLE:                                                       \
			case HASHMAP_ENTRY_UNUSED:                                                          \
				goto found;                                                                     \
			}                                                                                   \
			index += 2 * i + 1;                                                                 \
			index %= map->capacity;                                                             \
		}                                                                                       \
	found:;                                                                                     \
		if (entry->state != HASHMAP_ENTRY_ASSIGNED)                                             \
		{                                                                                       \
			map->size++;                                                                        \
			entry->state = HASHMAP_ENTRY_ASSIGNED;                                              \
		}                                                                                       \
		entry->key = key;                                                                       \
		entry->value = value;                                                                   \
	}                                                                                           \
	bool hashmap_##NAME##_get(hashmap_##NAME##_t *map, KEY key, VALUE *value)                   \
	{                                                                                           \
		int index = hashmap_##NAME##_index_for(map, key);                                       \
		if (index == -1)                                                                        \
			return false;                                                                       \
		*value = map->entries[index].value;                                                     \
		return true;                                                                            \
	}                                                                                           \
	bool hashmap_##NAME##_remove(hashmap_##NAME##_t *map, KEY key, VALUE *value)                \
	{                                                                                           \
		int index = hashmap_##NAME##_index_for(map, key);                                       \
		if (index == -1)                                                                        \
			return false;                                                                       \
		hashmap_##NAME##_entry_t *entry = &map->entries[index];                                 \
		*value = entry->value;                                                                  \
		entry->state = HASHMAP_ENTRY_AVAILABLE;                                                 \
		map->size--;                                                                            \
		return true;                                                                            \
	}                                                                                           \
	size_t hashmap_##NAME##_size(hashmap_##NAME##_t *map)                                       \
	{                                                                                           \
		return map->size;                                                                       \
	}                                                                                           \
	bool hashmap_##NAME##_iter(hashmap_##NAME##_t *map, size_t *pos, KEY *key, VALUE *value)    \
	{                                                                                           \
		if (!pos)                                                                               \
			panic("pos parameter cannot be NULL");                                              \
		for (; *pos < (size_t)map->capacity; (*pos)++)                                          \
		{                                                                                       \
			hashmap_##NAME##_entry_t *entry = &map->entries[*pos];                              \
			if (entry->state == HASHMAP_ENTRY_ASSIGNED)                                         \
			{                                                                                   \
				if (key)                                                                        \
					*key = entry->key;                                                          \
				if (value)                                                                      \
					*value = entry->value;                                                      \
				(*pos)++;                                                                       \
				return true;                                                                    \
			}                                                                                   \
		}                                                                                       \
		return false;                                                                           \
	}

#endif // HASHMAP_H
