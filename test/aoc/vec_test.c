#include <aoc/vec.h>
#include <unity.h>

VEC_DECLARE_TYPE(int)

VEC_IMPL_TYPE(int)

vec_int_t *v;

void setUp()
{
	v = vec_int_new_with_capacity(1);
}

void tearDown()
{
	vec_int_free(v);
}

void test_vec_push_and_pop()
{
	int val = 1;
	vec_int_push_back(v, val);
	TEST_ASSERT_EQUAL_INT(val, vec_int_pop_front(v));
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

void test_vec_remove()
{
	vec_int_push_back(v, 1);
	vec_int_push_back(v, 2);
	vec_int_push_back(v, 3);

	vec_int_remove(v, 1);

	TEST_ASSERT_EQUAL_INT(3, vec_int_pop_front(v));
	TEST_ASSERT_EQUAL_INT(1, vec_int_pop_front(v));
	TEST_ASSERT_EQUAL_INT(0, vec_int_size(v));
}

void test_vec_clear()
{
	vec_int_push_back(v, 1);
	vec_int_push_back(v, 2);
	vec_int_push_back(v, 3);

	vec_int_clear(v);

	TEST_ASSERT_EQUAL_INT(0, vec_int_size(v));
}

void test_vec_grow()
{
	vec_int_push_back(v, 1);
	vec_int_push_back(v, 2);
	vec_int_push_back(v, 3);

	vec_int_ensure_capacity(v, 100);

	TEST_ASSERT_EQUAL_INT(3, vec_int_pop_front(v));
	TEST_ASSERT_EQUAL_INT(2, vec_int_pop_front(v));
	TEST_ASSERT_EQUAL_INT(1, vec_int_pop_front(v));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_vec_push_and_pop);
	RUN_TEST(test_vec_insert_front);
	RUN_TEST(test_vec_insert_back);
	RUN_TEST(test_vec_remove);
	RUN_TEST(test_vec_clear);
	return UNITY_END();
}
