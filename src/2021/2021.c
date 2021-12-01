#include "2021.h"
#include "solutions.h"

void _2021_run_solution(int day, int part, FILE *fp)
{
	int index = (day - 1) * 2 + (part - 1);
	if (index >= sizeof(solutions) / sizeof(solution_t))
		panicf("solution for day %d part %d not implemented!\n", day, part);

	input_t input = input_new_from_file(fp);
	int64_t result = solutions[index](input);
	printf("day %d part %d: solution is %ld\n", day, part, result);
}
