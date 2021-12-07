#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "solutions.h"
#include "datastructures.h"

typedef uint64_t (*cost_fn)(vec_uint16_t *, uint16_t);

uint64_t compute_cost_part1(vec_uint16_t *sub_positions, uint16_t target_position)
{
	uint64_t cost = 0;
	for (size_t i = 0; i < vec_uint16_size(sub_positions); i++)
	{
		cost += abs(target_position - vec_uint16_get(sub_positions, i));
	}
	return cost;
}

uint64_t compute_cost_part2(vec_uint16_t *sub_positions, uint16_t target_position)
{
	uint64_t cost = 0;
	for (size_t i = 0; i < vec_uint16_size(sub_positions); i++)
	{
		uint16_t distance = abs(target_position - vec_uint16_get(sub_positions, i));
		// sum of positive integers from 1 to n: n(n+1)/2
		cost += (distance * (distance + 1)) / 2;
	}
	return cost;
}

int64_t day7(FILE *input, cost_fn compute_cost)
{
	char *line = NULL;
	size_t buf_len = 0;

	if (getline(&line, &buf_len, input) == -1)
		panic("expected input");

	vec_uint16_t *subs = vec_uint16_new();

	uint16_t num;

	char *token = strtok(line, ",");
	while (token != NULL)
	{
		if (sscanf(token, "%" SCNu16, &num) != 1)
			panic("expected a number");

		vec_uint16_push_back(subs, num);

		token = strtok(NULL, ",");
	}

	uint64_t sum = 0;
	for (size_t i = 0; i < vec_uint16_size(subs); i++)
	{
		sum += vec_uint16_get(subs, i);
	}

	// we'll assume that the average of all sub positions is close to the correct answer
	uint16_t avg = sum / vec_uint16_size(subs);
	uint16_t pos = avg;
	uint64_t lowest_cost = compute_cost(subs, pos);

	// then we'll look in either direction for a better position
	// until we find one that is worse than the current best
	int direction = 1;
	while (1)
	{
		uint16_t next_pos = pos + direction;
		uint64_t cost = compute_cost(subs, pos);
		if (cost <= lowest_cost)
		{
			lowest_cost = cost;
			pos = next_pos;
		}
		else if (direction == 1) // switch direction and return to average position
		{
			pos = avg;
			direction = -1;
		}
		else
			break; // done
	}

	vec_uint16_free(subs);

	if (line)
		free(line);

	return lowest_cost;
}

int64_t day7_part1(FILE *input)
{
	return day7(input, &compute_cost_part1);
}

int64_t day7_part2(FILE *input)
{
	return day7(input, &compute_cost_part2);
}
