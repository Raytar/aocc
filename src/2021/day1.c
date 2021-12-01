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

	queue_int64_t *history = queue_int64_new(3);
	int64_t num_increased = 0;
	int64_t prev_value = -1;

	while (input_getline(&line, &buf_len, &input) != -1)
	{
		int64_t num;
		if (!sscanf(line, "%ld", &num))
			panic("expected a number");

		// enqueue the new item
		queue_int64_enqueue(history, num);

		int64_t sum = 0;
		if (queue_int64_len(history) == 3)
		{
			sum += queue_int64_get(history, 0);
			sum += queue_int64_get(history, 1);
			sum += queue_int64_get(history, 2);

			// remove oldest item
			queue_int64_dequeue(history);
		}

		if (prev_value > 0 && sum > prev_value)
			num_increased++;

		prev_value = sum;
	}

	queue_int64_free(history);

	if (line != NULL)
		free(line);

	return num_increased;
}
