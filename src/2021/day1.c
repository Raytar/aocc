#include <stdlib.h>
#include <aoc/vec.h>

#include "solutions.h"

int64_t day1_part1(input_t input)
{
	char *line = NULL;
	size_t buf_len = 0;

	int64_t num_increased = 0;
	int64_t prev_value = -1;

	while (input_getline(&line, &buf_len, &input) != -1)
	{
		int64_t num;
		if (!sscanf(line, "%ld", &num))
			panic("expected a number");

		if (prev_value > 0 && num > prev_value)
			num_increased++;

		prev_value = num;
	}

	if (line != NULL)
		free(line);

	return num_increased;
}

int64_t day1_part2(input_t input)
{
	char *line = NULL;
	size_t buf_len = 0;

	// FIXME: a queue can be used instead, but I don't want to implement one right now
	vec_t *history = vec_new();
	int window_start = 0;
	int64_t num_increased = 0;
	int64_t prev_value = -1;

	while (input_getline(&line, &buf_len, &input) != -1)
	{
		int64_t num;
		if (!sscanf(line, "%ld", &num))
			panic("expected a number");

		// FIXME: this only works on machines where the pointer size is 64 bits
		vec_push_back(history, (void *)num);

		int64_t sum = 0;
		if (vec_size(history) >= 3)
		{
			sum += (int64_t)vec_get(history, window_start);
			sum += (int64_t)vec_get(history, window_start + 1);
			sum += (int64_t)vec_get(history, window_start + 2);
			window_start++;
		}

		if (prev_value > 0 && sum > prev_value)
			num_increased++;

		prev_value = sum;
	}

	vec_free(history);

	if (line != NULL)
		free(line);

	return num_increased;
}
