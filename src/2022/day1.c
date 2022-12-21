#include <stdlib.h>
#include <inttypes.h>

#include <aoc/common.h>

#include "solutions.h"

int64_t aoc2022_1_1(FILE *input)
{
	char *line = NULL;
	size_t buf_len = 0;

	int64_t max_calories = 0;
	int64_t curr_calories = 0;

	while (getline(&line, &buf_len, input) != -1)
	{
		if (strlen(line) == 0)
		{
			if (curr_calories > max_calories)
			{
				max_calories = curr_calories;
			}
			continue;
		}

		int64_t num;
		if (!sscanf(line, "%" SCNi64, &num))
			panic("expected a number");

		curr_calories += num;
	}

	return max_calories;
}
