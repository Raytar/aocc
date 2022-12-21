#include <stdio.h>
#include <stdlib.h>

#include <2021/solutions.h>
#include <aoc/common.h>
#include <unity.h>

const char *INPUT = "2199943210\n"
					"3987894921\n"
					"9856789892\n"
					"8767896789\n"
					"9899965678";

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
	TEST_ASSERT_EQUAL_INT64(15, aoc2021_9_1(input));
}

void test_part2()
{
	TEST_ASSERT_EQUAL_INT64(1134, aoc2021_9_2(input));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_part1);
	RUN_TEST(test_part2);
	return UNITY_END();
}
