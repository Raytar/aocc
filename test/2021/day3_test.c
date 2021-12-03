#include <2021/solutions.h>
#include <unity.h>

void setUp()
{
}

void tearDown()
{
}

const char *PART1_INPUT = "00100\n"
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

void test_part1()
{
	input_t input = input_new_from_str(PART1_INPUT);
	TEST_ASSERT_EQUAL_INT64(198, day3_part1(input));
}

void test_part2()
{
	input_t input = input_new_from_str(PART1_INPUT);
	TEST_ASSERT_EQUAL_INT64(230, day3_part2(input));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_part1);
	RUN_TEST(test_part2);
	return UNITY_END();
}
