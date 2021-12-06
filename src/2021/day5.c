#include <inttypes.h>
#include <aoc/hashmap.h>
#include "solutions.h"

struct point
{
	uint16_t x;
	uint16_t y;
};

size_t hash_point(struct point point)
{
	return (size_t)point.x | ((size_t)point.y << 16);
}

int cmp_point(struct point a, struct point b)
{
	if (a.x == b.x && a.y == b.y)
		return 0;
	return 1;
}

HASHMAP_DECLARE_TYPE_NAME(struct point, uint16_t, points)
HASHMAP_IMPL_TYPE_NAME(struct point, uint16_t, points, hash_point, cmp_point)

void inc_point(hashmap_points_t *points, uint16_t x, uint16_t y)
{
	struct point point = {
		.x = x,
		.y = y,
	};

	// printf("%" PRIu16 ", %" PRIu16 "\n", x, y);

	uint16_t num = 0;
	hashmap_points_get(points, point, &num);
	num++;
	hashmap_points_insert(points, point, num);
}

int64_t day5(FILE *input, bool diagonal)
{
	hashmap_points_t points = hashmap_points_new();
	char *line = NULL;
	size_t buf_len = 0;

	while (getline(&line, &buf_len, input) != -1)
	{
		uint16_t x, y, x1, y1, x2, y2;
		if (sscanf(line, "%" SCNu16 ",%" SCNu16 " -> %" SCNu16 ",%" SCNu16, &x1, &y1, &x2, &y2) != 4)
			panic("could not parse input");

		if (!diagonal && x1 != x2 && y1 != y2)
			continue; // skip diagonal lines

		x = x1;
		y = y1;

		while (x != x2 || y != y2)
		{
			inc_point(&points, x, y);

			if (x1 < x2)
				x++;
			else if (x1 > x2)
				x--;
			if (y1 < y2)
				y++;
			else if (y1 > y2)
				y--;
		}

		inc_point(&points, x2, y2);
	}

	int64_t at_least_two_overlap = 0;
	size_t pos = 0;
	struct point point;
	uint16_t overlap;

	while (hashmap_points_iter(&points, &pos, &point, &overlap))
	{
		if (overlap > 1)
		{
			// printf("(%" PRIu16 ", %" PRIu16 "): %" PRIu16 "\n", point.x, point.y, overlap);
			at_least_two_overlap++;
		}
	}

	hashmap_points_free(&points);

	if (line)
		free(line);

	return at_least_two_overlap;
}

int64_t day5_part1(FILE *input)
{
	return day5(input, false);
}

int64_t day5_part2(FILE *input)
{
	return day5(input, true);
}
