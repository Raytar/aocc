#include <inttypes.h>

#include "2021.h"
#include "solutions.h"

solution_t solutions[] = {
	day1_part1,
	day1_part2,
	day2_part1,
	day2_part2,
	day3_part1,
	day3_part2,
	day4_part1,
	day4_part2,
};

void aoc_2021_run_solution(int day, int part, FILE *input)
{
	int index = (day - 1) * 2 + (part - 1);
	if (index >= (int)(sizeof(solutions) / sizeof(solution_t)))
		panicf("solution for day %d part %d not implemented!", day, part);

	int64_t result = solutions[index](input);
	printf("day %d part %d: solution is %" PRIi64 "\n", day, part, result);
}
