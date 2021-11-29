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

void test_vec_insert_front()
{
	int val = 1;
	vec_push_back(v, 2);
	vec_insert(v, 0, val);
	TEST_ASSERT_EQUAL_INT(val, (int)vec_get(v, 0));
}

void test_vec_insert_back()
{
	int val = 1;
	vec_push_back(v, 2);
	vec_insert(v, 1, val);
	TEST_ASSERT_EQUAL_INT(val, (int)vec_get(v, 1));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_vec_push_and_pop);
	RUN_TEST(test_vec_insert_front);
	RUN_TEST(test_vec_insert_back);
	return UNITY_END();
}
