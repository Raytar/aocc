#include <inttypes.h>

#include "2022.h"
#include "solutions.h"

static solution_t solutions[] = {
	aoc2022_1_1,
};

void aoc_2022_run_solution(int day, int part, FILE *input)
{
	int index = (day - 1) * 2 + (part - 1);
	if (index >= (int)(sizeof(solutions) / sizeof(solution_t)))
		panicf("solution for day %d part %d not implemented!", day, part);

	int64_t result = solutions[index](input);
	printf("day %d part %d: solution is %" PRIi64 "\n", day, part, result);
}
