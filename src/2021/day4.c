#include <stdio.h>	// sscanf
#include <string.h> // strtok
#include <stdbool.h>
#include <inttypes.h>

#include <aoc/vec.h>
#include <aoc/hashmap.h>
#include "solutions.h"

#define BINGO_LEN 5

size_t hash_int8(int8_t key)
{
	return key;
}

int cmp_int8(int8_t a, int8_t b)
{
	return a - b;
}

HASHMAP_DECLARE_TYPE_NAME(int8_t, uint8_t, bingo_lookup)
HASHMAP_IMPL_TYPE_NAME(int8_t, uint8_t, bingo_lookup, hash_int8, cmp_int8)

typedef struct bingo_t
{
	int8_t board[BINGO_LEN * BINGO_LEN];
	hashmap_bingo_lookup_t lookup; // for fast index lookups
} bingo_t;

VEC_DECLARE_TYPE_NAME(int8_t, int8)
VEC_IMPL_TYPE_NAME(int8_t, int8)

VEC_DECLARE_TYPE_NAME(bingo_t, bingo)
VEC_IMPL_TYPE_NAME(bingo_t, bingo)

// mark a number in the bingo board
static bool bingo_mark(bingo_t *bingo, int8_t number)
{
	uint8_t index;
	if (!hashmap_bingo_lookup_get(&bingo->lookup, number, &index))
	{
		return false;
	}

	// we'll represent a marked value by adding 1 and making it negative
	// adding 1 is necessary so that 0 will work
	int8_t value = bingo->board[index];
	bingo->board[index] = -(value + 1);

	// now check the row and column of the number
	int col_start = index % BINGO_LEN;
	int row_start = index - col_start;

	uint8_t num_marked = 0;
	for (int i = row_start; i < row_start + BINGO_LEN; i++)
	{
		if (bingo->board[i] < 0)
			num_marked++;
	}

	if (num_marked == BINGO_LEN)
		return true;

	num_marked = 0;
	for (int i = col_start; i < BINGO_LEN * BINGO_LEN; i += BINGO_LEN)
	{
		if (bingo->board[i] < 0)
			num_marked++;
	}

	if (num_marked == BINGO_LEN)
		return true;

	return false;
}

static void read_input(FILE *input, vec_int8_t *numbers, vec_bingo_t *bingos)
{
	char *line = NULL;
	size_t buf_len = 0;

	// read the first line containing numbers
	if (getline(&line, &buf_len, input) == -1)
		panic("expected numbers");

	char *token = strtok(line, ",");

	int8_t number;
	while (token != NULL)
	{
		if (sscanf(token, "%" SCNi8, &number) != 1)
			panic("expected a u8");
		vec_int8_push_back(numbers, number);
		token = strtok(NULL, ",");
	}

	uint8_t row_number = 0;
	bingo_t bingo;
	while (getline(&line, &buf_len, input) != -1)
	{
		line[strcspn(line, "\r\n")] = '\0'; // remove newline

		if (strlen(line) == 0)
		{
			if (row_number == BINGO_LEN)
			{
				vec_bingo_push_back(bingos, bingo);
			}
			memset(bingo.board, 0, sizeof(bingo.board));
			bingo.lookup = hashmap_bingo_lookup_new();
			row_number = 0;
			continue;
		}

		token = strtok(line, " ");
		uint8_t col_number = 0;
		while (token != NULL)
		{
			if (sscanf(token, "%" SCNi8, &number) != 1)
				panic("expected a u8");
			uint8_t index = row_number * BINGO_LEN + col_number;
			bingo.board[index] = number;
			hashmap_bingo_lookup_insert(&bingo.lookup, number, index);
			col_number++;
			token = strtok(NULL, " ");
		}

		row_number++;
	}

	if (row_number != BINGO_LEN)
		panic("incomplete bingo board");

	vec_bingo_push_back(bingos, bingo);

	if (line != NULL)
		free(line);
}

static void free_bingos(vec_bingo_t *bingos)
{
	for (size_t i = 0; i < vec_bingo_size(bingos); i++)
	{
		bingo_t bingo = vec_bingo_pop_front(bingos);
		hashmap_bingo_lookup_free(&bingo.lookup);
	}
	vec_bingo_free(bingos);
}

static uint64_t score(bingo_t *bingo, int8_t number)
{
	int64_t unmarked_sum = 0;
	for (int i = 0; i < BINGO_LEN * BINGO_LEN; i++)
	{
		int8_t n = bingo->board[i];
		if (n > 0)
			unmarked_sum += n;
	}
	printf("number: %" PRIi8 ", unmarked_sum: %" PRIi64 "\n", number, unmarked_sum);
	return unmarked_sum * number;
}

int64_t day4_part1(FILE *input)
{
	vec_int8_t *numbers = vec_int8_new();
	vec_bingo_t *bingos = vec_bingo_new();

	read_input(input, numbers, bingos);

	bingo_t *bingo = NULL;
	int8_t number = 0;

	for (size_t i = 0; i < vec_int8_size(numbers); i++)
	{
		number = vec_int8_get(numbers, i);
		for (size_t j = 0; j < vec_bingo_size(bingos); j++)
		{
			bingo = vec_bingo_get_ptr(bingos, j);
			if (bingo_mark(bingo, number))
				goto found_winner;
		}
	}

found_winner:;
	int64_t result = score(bingo, number);

	vec_int8_free(numbers);
	free_bingos(bingos);

	return result;
}

int64_t day4_part2(FILE *input)
{
	vec_int8_t *numbers = vec_int8_new();
	vec_bingo_t *bingos = vec_bingo_new();

	read_input(input, numbers, bingos);

	bingo_t *bingo = NULL;
	int8_t number = 0;

	for (size_t i = 0; i < vec_int8_size(numbers); i++)
	{
		number = vec_int8_get(numbers, i);
		for (ssize_t j = vec_bingo_size(bingos) - 1; j >= 0; j--)
		{
			bingo = vec_bingo_get_ptr(bingos, j);
			if (bingo_mark(bingo, number))
			{
				if (vec_bingo_size(bingos) == 1)
					goto found_loser;

				bingo_t winner = vec_bingo_remove(bingos, j);
				hashmap_bingo_lookup_free(&winner.lookup);
				bingo = NULL;
			}
		}
	}

found_loser:;
	int64_t result = score(bingo, number);

	vec_int8_free(numbers);
	free_bingos(bingos);

	return result;
}
