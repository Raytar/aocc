#include <stdio.h>
#include <stdlib.h>

#include <2022/solutions.h>
#include <aoc/common.h>
#include <unity.h>

const char *INPUT = "1000\n"
					"2000\n"
					"3000\n"
					"\n"
					"4000\n"
					"\n"
					"5000\n"
					"6000\n"
					"\n"
					"7000\n"
					"8000\n"
					"9000\n"
					"\n"
					"10000";

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
	TEST_ASSERT_EQUAL_INT64(24000, aoc2022_1_1(input));
}

void test_part2()
{
	// TEST_ASSERT_EQUAL_INT64(5, aoc2021_1_2(input));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_part1);
	RUN_TEST(test_part2);
	return UNITY_END();
}
