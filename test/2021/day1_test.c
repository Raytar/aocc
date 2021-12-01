#include <2021/solutions.h>
#include <unity.h>

void setUp()
{
}

void tearDown()
{
}

const char *PART1_INPUT = "199\n"
						  "200\n"
						  "208\n"
						  "210\n"
						  "200\n"
						  "207\n"
						  "240\n"
						  "269\n"
						  "260\n"
						  "263";

void test_part1()
{
	input_t input = input_new_from_str(PART1_INPUT);
	TEST_ASSERT_EQUAL_INT64(7, day1_part1(input));
}

void test_part2()
{
	input_t input = input_new_from_str(PART1_INPUT);
	TEST_ASSERT_EQUAL_INT64(5, day1_part2(input));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_part1);
	RUN_TEST(test_part2);
	return UNITY_END();
}
