#include <stdio.h>
#include <stdlib.h>

#include <2021/solutions.h>
#include <aoc/common.h>
#include <unity.h>

const char *INPUT = "00100\n"
					"11110\n"
					"10110\n"
					"10111\n"
					"10101\n"
					"01111\n"
					"00111\n"
					"11100\n"
					"10000\n"
					"11001\n"
					"00010\n"
					"01010";

FILE *input;

void setUp()
{
	input = fmemopen_str(INPUT, "r");
	if (!input)
	{
		perror("setUp");
		exit(1);
	}
}

void tearDown()
{
	fclose(input);
}

void test_part1()
{
	TEST_ASSERT_EQUAL_INT64(198, day3_part1(input));
}

void test_part2()
{
	TEST_ASSERT_EQUAL_INT64(230, day3_part2(input));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_part1);
	RUN_TEST(test_part2);
	return UNITY_END();
}
