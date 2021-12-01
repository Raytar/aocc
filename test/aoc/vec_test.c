#include <aoc/vec.h>
#include <unity.h>

VEC_DECLARE_TYPE(int)

VEC_IMPL_TYPE(int)

vec_int_t *v;

void setUp()
{
	v = vec_int_new();
}

void tearDown()
{
	vec_int_free(v);
}

void test_vec_push_and_pop()
{
	int val = 1;
	vec_int_push_back(v, val);
	TEST_ASSERT_EQUAL_INT(val, vec_int_pop_back(v));
}

void test_vec_insert_front()
{
	int val = 1;
	vec_int_push_back(v, 2);
	vec_int_insert(v, 0, val);
	TEST_ASSERT_EQUAL_INT(val, vec_int_get(v, 0));
}

void test_vec_insert_back()
{
	int val = 1;
	vec_int_push_back(v, 2);
	vec_int_insert(v, 1, val);
	TEST_ASSERT_EQUAL_INT(val, vec_int_get(v, 1));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_vec_push_and_pop);
	RUN_TEST(test_vec_insert_front);
	RUN_TEST(test_vec_insert_back);
	return UNITY_END();
}
