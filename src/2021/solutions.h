#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdint.h>
#include <aoc/common.h>

int64_t day1_part1(input_t input);
int64_t day1_part2(input_t input);

static solution_t solutions[] = {
	day1_part1,
	day1_part2,
};

#endif // SOLUTIONS_H
