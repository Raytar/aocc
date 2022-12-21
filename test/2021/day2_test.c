#include <stdio.h>
#include <stdlib.h>

#include <2021/solutions.h>
#include <aoc/common.h>
#include <unity.h>

const char *INPUT = "forward 5\n"
					"down 5\n"
					"forward 8\n"
					"up 3\n"
					"down 8\n"
					"forward 2";

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
	TEST_ASSERT_EQUAL_INT64(150, aoc2021_2_1(input));
}

void test_part2()
{
	TEST_ASSERT_EQUAL_INT64(900, aoc2021_2_2(input));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_part1);
	RUN_TEST(test_part2);
	return UNITY_END();
}
