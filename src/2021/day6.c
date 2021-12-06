#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <aoc/queue.h>

#include "solutions.h"
#include "datastructures.h"

int64_t day6(FILE *input, int days)
{
	char *line = NULL;
	size_t buf_len = 0;

	if (getline(&line, &buf_len, input) == -1)
		panic("expected input");

	vec_uint8_t *starting_fishes = vec_uint8_new();

	uint8_t num;
	char *token = strtok(line, ",");
	while (token != NULL)
	{
		if (sscanf(token, "%" SCNu8, &num) != 1)
			panic("expected a number");
		vec_uint8_push_back(starting_fishes, num);
		token = strtok(NULL, ",");
	}

	vec_uint8_sort(starting_fishes, &cmp_uint8);
	queue_int64_t *queue = queue_int64_new(9);

	uint8_t days_until_spawn = 0;
	uint64_t num_fishes = 0;
	for (size_t i = 0; i < vec_uint8_size(starting_fishes); i++)
	{
		num = vec_uint8_get(starting_fishes, i);

		while (num > days_until_spawn)
		{
			days_until_spawn++;
			queue_int64_enqueue(queue, num_fishes);
			num_fishes = 0;
		}

		if (num < days_until_spawn)
			panic("expected the vector to be sorted");

		num_fishes++;
	}
	queue_int64_enqueue(queue, num_fishes);

	while (queue_int64_len(queue) < 9)
		queue_int64_enqueue(queue, 0);

	for (int i = 0; i < days; i++)
	{
		num_fishes = queue_int64_dequeue(queue);
		uint64_t n = queue_int64_get(queue, 6);
		queue_int64_set(queue, 6, n + num_fishes); // increase the number of fishes with 7 days left
		queue_int64_enqueue(queue, num_fishes);	   // the new fishes with 8 days left

		int64_t total = 0;
		for (size_t i = 0; i < queue_int64_len(queue); i++)
		{
			uint64_t m = queue_int64_get(queue, i);
			total += m;
		}

		printf("day %d: %" PRIu64 "\n", i + 1, total);
	}

	int64_t total = 0;
	for (size_t i = 0; i < queue_int64_len(queue); i++)
	{
		total += queue_int64_get(queue, i);
	}

	if (line)
		free(line);

	vec_uint8_free(starting_fishes);
	queue_int64_free(queue);

	return total;
}

int64_t day6_part1(FILE *input)
{
	return day6(input, 80);
}

int64_t day6_part2(FILE *input)
{
	return day6(input, 256);
}
