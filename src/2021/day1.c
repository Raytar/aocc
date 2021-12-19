#include <stdio.h>	// sscanf
#include <stdlib.h> // free
#include <inttypes.h>

#include "solutions.h"
#include "datastructures.h"

int64_t day1_part1(FILE *input)
{
	char *line = NULL;
	size_t buf_len = 0;

	int64_t num_increased = 0;
	int64_t prev_value = -1;

	while (getline(&line, &buf_len, input) != -1)
	{
		int64_t num;
		if (!sscanf(line, "%" SCNi64, &num))
			panic("expected a number");

		if (prev_value > 0 && num > prev_value)
			num_increased++;

		prev_value = num;
	}

	if (line != NULL)
		free(line);

	return num_increased;
}

int64_t day1_part2(FILE *input)
{
	char *line = NULL;
	size_t buf_len = 0;

	ring_int64_t *history = ring_int64_new(3);
	int64_t num_increased = 0;
	int64_t prev_value = -1;

	while (getline(&line, &buf_len, input) != -1)
	{
		int64_t num;
		if (!sscanf(line, "%" SCNi64, &num))
			panic("expected a number");

		// enring the new item
		ring_int64_push_back(history, num);

		int64_t sum = 0;
		if (ring_int64_len(history) == 3)
		{
			sum += ring_int64_get(history, 0);
			sum += ring_int64_get(history, 1);
			sum += ring_int64_get(history, 2);

			// remove oldest item
			ring_int64_pop_front(history);
		}

		if (prev_value > 0 && sum > prev_value)
			num_increased++;

		prev_value = sum;
	}

	ring_int64_free(history);

	if (line != NULL)
		free(line);

	return num_increased;
}
