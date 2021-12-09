#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "solutions.h"
#include "datastructures.h"

static const uint8_t VISITED_MASK = 0x80;

static void read_input(FILE *input, vec_uint8_t *heightmap, int *rows, int *cols)
{
	char *line = NULL;
	size_t buf_len = 0;

	while (getline(&line, &buf_len, input) != -1)
	{
		line[strcspn(line, "\r\n")] = '\0';

		size_t len = strlen(line);
		if (*cols == 0)
			*cols = len;

		for (size_t i = 0; i < len; i++)
			vec_uint8_push_back(heightmap, line[i] - '0');

		(*rows)++;
	}

	if (line)
		free(line);
}

static void find_low_points(vec_uint8_t *heightmap, vec_int_t *low_points, int rows, int cols)
{
	for (int pos = 0; pos < (int)vec_uint8_size(heightmap); pos++)
	{
		uint8_t height = vec_uint8_get(heightmap, pos);

		// check top
		if (pos / cols > 0 && height >= vec_uint8_get(heightmap, pos - cols))
			goto not_low_point;
		// check bottom
		if (pos / cols < rows - 1 && height >= vec_uint8_get(heightmap, pos + cols))
			goto not_low_point;
		// check left
		if (pos % cols > 0 && height >= vec_uint8_get(heightmap, pos - 1))
			goto not_low_point;
		// check right
		if (pos % cols < cols - 1 && height >= vec_uint8_get(heightmap, pos + 1))
			goto not_low_point;

		vec_int_push_back(low_points, pos);

	not_low_point:;
		// jump here if the point is not a low point
	}
}

int64_t day9_part1(FILE *input)
{
	vec_uint8_t *heightmap = vec_uint8_new();
	vec_int_t *low_points = vec_int_new();
	int rows = 0, cols = 0;

	read_input(input, heightmap, &rows, &cols);

	find_low_points(heightmap, low_points, rows, cols);

	int64_t answer = 0;
	for (size_t i = 0; i < vec_int_size(low_points); i++)
		answer += vec_uint8_get(heightmap, vec_int_get(low_points, i)) + 1;

	vec_uint8_free(heightmap);
	vec_int_free(low_points);

	return answer;
}

static int basin_size(vec_uint8_t *heightmap, int rows, int cols, int pos)
{
	int size = 1;

	uint8_t height = vec_uint8_get(heightmap, pos);

	if (height & VISITED_MASK)
		return 0; // already counted

	vec_uint8_set(heightmap, pos, height | VISITED_MASK);

	if (height == 9)
		return 0;

	// check top
	if (pos / cols > 0 && height <= vec_uint8_get(heightmap, pos - cols))
		size += basin_size(heightmap, rows, cols, pos - cols);
	// check bottom
	if (pos / cols < rows - 1 && height <= vec_uint8_get(heightmap, pos + cols))
		size += basin_size(heightmap, rows, cols, pos + cols);
	// check left
	if (pos % cols > 0 && height <= vec_uint8_get(heightmap, pos - 1))
		size += basin_size(heightmap, rows, cols, pos - 1);
	// check right
	if (pos % cols < cols - 1 && height <= vec_uint8_get(heightmap, pos + 1))
		size += basin_size(heightmap, rows, cols, pos + 1);

	return size;
}

int64_t day9_part2(FILE *input)
{
	vec_uint8_t *heightmap = vec_uint8_new();
	vec_int_t *low_points = vec_int_new();
	vec_int_t *basin_sizes = vec_int_new();
	int rows = 0, cols = 0;

	read_input(input, heightmap, &rows, &cols);
	find_low_points(heightmap, low_points, rows, cols);

	for (size_t i = 0; i < vec_int_size(low_points); i++)
	{
		int pos = vec_int_get(low_points, i);
		int size = basin_size(heightmap, rows, cols, pos);
		printf("pos: %d, size: %d\n", pos, size);
		vec_int_push_back(basin_sizes, size);
	}

	vec_int_sort(basin_sizes, cmp_int);

	int64_t answer = 1;
	for (int i = 0; i < 3; i++)
		answer *= vec_int_pop_back(basin_sizes);

	vec_uint8_free(heightmap);
	vec_int_free(low_points);
	vec_int_free(basin_sizes);

	return answer;
}
