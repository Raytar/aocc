#include <aoc/queue.h>
#include <unity.h>

QUEUE_DECLARE_TYPE(int)
QUEUE_IMPL_TYPE(int)

queue_int_t *q;

void setUp()
{
	q = queue_int_new(3);
}

void tearDown()
{
	queue_int_free(q);
}

void test_queue_push_and_pop()
{
	TEST_ASSERT(queue_int_enqueue(q, 1));
	TEST_ASSERT(queue_int_enqueue(q, 2));
	TEST_ASSERT(queue_int_enqueue(q, 3));
	TEST_ASSERT_FALSE(queue_int_enqueue(q, 4));

	TEST_ASSERT_EQUAL_INT(1, queue_int_dequeue(q));
	TEST_ASSERT_EQUAL_INT(2, queue_int_dequeue(q));
	TEST_ASSERT_EQUAL_INT(3, queue_int_dequeue(q));
}

void test_queue_get()
{
	TEST_ASSERT(queue_int_enqueue(q, 1));
	TEST_ASSERT(queue_int_enqueue(q, 2));
	TEST_ASSERT(queue_int_enqueue(q, 3));

	TEST_ASSERT_EQUAL_INT(1, queue_int_get(q, 0));
	TEST_ASSERT_EQUAL_INT(2, queue_int_get(q, 1));
	TEST_ASSERT_EQUAL_INT(3, queue_int_get(q, 2));
}

void test_queue_wrap()
{
	TEST_ASSERT(queue_int_enqueue(q, 1));
	TEST_ASSERT(queue_int_enqueue(q, 2));

	TEST_ASSERT_EQUAL_size_t(1, queue_int_len(q));

	TEST_ASSERT_EQUAL_INT(1, queue_int_dequeue(q));
	TEST_ASSERT(queue_int_enqueue(q, 3));
	TEST_ASSERT(queue_int_enqueue(q, 4));

	TEST_ASSERT_EQUAL_size_t(3, queue_int_len(q));

	TEST_ASSERT_EQUAL_INT(2, queue_int_get(q, 0));
	TEST_ASSERT_EQUAL_INT(2, queue_int_dequeue(q));
	TEST_ASSERT_EQUAL_INT(3, queue_int_dequeue(q));
	TEST_ASSERT_EQUAL_INT(4, queue_int_dequeue(q));

	TEST_ASSERT_EQUAL_size_t(0, queue_int_len(q));
}

int main()
{
	UNITY_BEGIN();

	RUN_TEST(test_queue_push_and_pop);
	RUN_TEST(test_queue_get);

	return UNITY_END();
}
