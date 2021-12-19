#include <stdio.h>
#include <string.h>
#include <inttypes.h>

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

	// create ring filled with zeros
	ring_int64_t *ring = ring_int64_new(9);
	while (ring_int64_len(ring) < 9)
		ring_int64_push_back(ring, 0);

	// increment the ring entries based on the input numbers
	for (size_t i = 0; i < vec_uint8_size(starting_fishes); i++)
	{
		uint8_t days = vec_uint8_get(starting_fishes, i);
		int64_t num_fishes = ring_int64_get(ring, days);
		ring_int64_set(ring, days, ++num_fishes);
	}

	for (int i = 0; i < days; i++)
	{
		int64_t num_fishes = ring_int64_pop_front(ring); // get the number of fishes with counter 0
		int64_t n = ring_int64_get(ring, 6);
		ring_int64_set(ring, 6, n + num_fishes); // increase the number of fishes with counter 6
		ring_int64_push_back(ring, num_fishes);	 // add the new fishes with counter 8
	}

	int64_t total = 0;
	for (size_t i = 0; i < ring_int64_len(ring); i++)
	{
		total += ring_int64_get(ring, i);
	}

	if (line)
		free(line);

	vec_uint8_free(starting_fishes);
	ring_int64_free(ring);

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
