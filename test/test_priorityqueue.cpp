#include <gtest.h>
#include "priorityqueue.hpp"

TEST(PriorityQueue, wrong_type_number_in_method)
{
	PriorityQueue<int> queue;
	ASSERT_ANY_THROW(queue.getMin(0));
}

TEST(PriorityQueue, can_use_method_getMin)
{
	PriorityQueue<int> queue;
	ASSERT_NO_THROW(queue.getMin(1));
	ASSERT_NO_THROW(queue.getMin(2));
	ASSERT_NO_THROW(queue.getMin(3));
}

TEST(PriorityQueue, can_use_method_insert)
{
	PriorityQueue<int> queue;
	ASSERT_NO_THROW(queue.insert(2));
}

TEST(PriorityQueue, can_use_method_extract_min)
{
	PriorityQueue<int> queue;
	ASSERT_NO_THROW(queue.extractMin());
}

TEST(PriorityQueue, can_use_method_size)
{
	PriorityQueue<int> queue;
	ASSERT_NO_THROW(queue.size(1));
	ASSERT_NO_THROW(queue.size(2));
	ASSERT_NO_THROW(queue.size(3));
}

TEST(PriorityQueue, can_use_method_is_empty)
{
	PriorityQueue<int> queue;
	ASSERT_NO_THROW(queue.isEmpty(1));
	ASSERT_NO_THROW(queue.isEmpty(2));
	ASSERT_NO_THROW(queue.isEmpty(3));
}