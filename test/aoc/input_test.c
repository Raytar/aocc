#include <stdlib.h>
#include <aoc/input.h>
#include <unity.h>

void setUp()
{
}

void tearDown()
{
}

const char *INPUT = "hello\nworld";

void test_input_str_getline()
{
	input_t input = input_new_from_str(INPUT);

	char *line = NULL;
	size_t len = 0;

	TEST_ASSERT_EQUAL_INT(6, input_getline(&line, &len, &input));
	TEST_ASSERT_EQUAL_STRING("hello\n", line);

	TEST_ASSERT_EQUAL_INT(5, input_getline(&line, &len, &input));
	TEST_ASSERT_EQUAL_STRING("world", line);

	TEST_ASSERT_EQUAL_INT(-1, input_getline(&line, &len, &input));

	if (line != NULL)
		free(line);
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_input_str_getline);
	return UNITY_END();
}
