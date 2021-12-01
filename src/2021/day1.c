#include <stdlib.h>

#include "solutions.h"
#include "datastructures.h"

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
	vec_int64_t *history = vec_int64_new();
	int window_start = 0;
	int64_t num_increased = 0;
	int64_t prev_value = -1;

	while (input_getline(&line, &buf_len, &input) != -1)
	{
		int64_t num;
		if (!sscanf(line, "%ld", &num))
			panic("expected a number");

		vec_int64_push_back(history, num);

		int64_t sum = 0;
		if (vec_int64_size(history) >= 3)
		{
			sum += vec_int64_get(history, window_start);
			sum += vec_int64_get(history, window_start + 1);
			sum += vec_int64_get(history, window_start + 2);
			window_start++;
		}

		if (prev_value > 0 && sum > prev_value)
			num_increased++;

		prev_value = sum;
	}

	vec_int64_free(history);

	if (line != NULL)
		free(line);

	return num_increased;
}
