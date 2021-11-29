#include <aoc/vec.h>
#include <unity.h>

vec_t *v;

void setUp()
{
	v = vec_new();
}

void tearDown()
{
	vec_free(v);
}

void test_vec_push_and_pop()
{
	int val = 1;
	vec_push_back(v, val);
	TEST_ASSERT_EQUAL_INT(val, (int)vec_pop_back(v));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_vec_push_and_pop);
	return UNITY_END();
}
