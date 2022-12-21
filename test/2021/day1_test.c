#include <stdio.h>
#include <stdlib.h>

#include <2021/solutions.h>
#include <aoc/common.h>
#include <unity.h>

const char *INPUT = "199\n"
					"200\n"
					"208\n"
					"210\n"
					"200\n"
					"207\n"
					"240\n"
					"269\n"
					"260\n"
					"263";

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
	TEST_ASSERT_EQUAL_INT64(7, aoc2021_1_1(input));
}

void test_part2()
{
	TEST_ASSERT_EQUAL_INT64(5, aoc2021_1_2(input));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_part1);
	RUN_TEST(test_part2);
	return UNITY_END();
}
