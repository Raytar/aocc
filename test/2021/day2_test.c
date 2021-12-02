#include <2021/solutions.h>
#include <unity.h>

void setUp()
{
}

void tearDown()
{
}

const char *PART1_INPUT = "forward 5\n"
						  "down 5\n"
						  "forward 8\n"
						  "up 3\n"
						  "down 8\n"
						  "forward 2";

void test_part1()
{
	input_t input = input_new_from_str(PART1_INPUT);
	TEST_ASSERT_EQUAL_INT64(150, day2_part1(input));
}

void test_part2()
{
	input_t input = input_new_from_str(PART1_INPUT);
	TEST_ASSERT_EQUAL_INT64(900, day2_part2(input));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_part1);
	RUN_TEST(test_part2);
	return UNITY_END();
}
