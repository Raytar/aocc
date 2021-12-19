#include <aoc/ring.h>
#include <unity.h>

RING_DECLARE_TYPE(int)
RING_IMPL_TYPE(int)

ring_int_t *q;

void setUp()
{
	q = ring_int_new(3);
}

void tearDown()
{
	ring_int_free(q);
}

void test_ring_push_and_pop()
{
	TEST_ASSERT(ring_int_push_back(q, 1));
	TEST_ASSERT(ring_int_push_back(q, 2));
	TEST_ASSERT(ring_int_push_back(q, 3));
	TEST_ASSERT_FALSE(ring_int_push_back(q, 4));

	TEST_ASSERT_EQUAL_INT(1, ring_int_pop_front(q));
	TEST_ASSERT_EQUAL_INT(2, ring_int_pop_front(q));
	TEST_ASSERT_EQUAL_INT(3, ring_int_pop_front(q));
}

void test_ring_get()
{
	TEST_ASSERT(ring_int_push_back(q, 1));
	TEST_ASSERT(ring_int_push_back(q, 2));
	TEST_ASSERT(ring_int_push_back(q, 3));

	TEST_ASSERT_EQUAL_INT(1, ring_int_get(q, 0));
	TEST_ASSERT_EQUAL_INT(2, ring_int_get(q, 1));
	TEST_ASSERT_EQUAL_INT(3, ring_int_get(q, 2));
}

void test_ring_wrap()
{
	TEST_ASSERT(ring_int_push_back(q, 1));
	TEST_ASSERT(ring_int_push_back(q, 2));

	TEST_ASSERT_EQUAL_size_t(1, ring_int_len(q));

	TEST_ASSERT_EQUAL_INT(1, ring_int_pop_front(q));
	TEST_ASSERT(ring_int_push_back(q, 3));
	TEST_ASSERT(ring_int_push_back(q, 4));

	TEST_ASSERT_EQUAL_size_t(3, ring_int_len(q));

	TEST_ASSERT_EQUAL_INT(2, ring_int_get(q, 0));
	TEST_ASSERT_EQUAL_INT(2, ring_int_pop_front(q));
	TEST_ASSERT_EQUAL_INT(3, ring_int_pop_front(q));
	TEST_ASSERT_EQUAL_INT(4, ring_int_pop_front(q));

	TEST_ASSERT_EQUAL_size_t(0, ring_int_len(q));
}

int main()
{
	UNITY_BEGIN();

	RUN_TEST(test_ring_push_and_pop);
	RUN_TEST(test_ring_get);

	return UNITY_END();
}
