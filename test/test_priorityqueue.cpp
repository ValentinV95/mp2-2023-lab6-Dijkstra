#include <gtest.h>
#include "priorityqueue.hpp"

TEST(PriorityQueue, wrong_type_number_in_method)
{
	PriorityQueue<int> queue;
	ASSERT_ANY_THROW(queue.front(0));
}

TEST(PriorityQueue, can_use_method_front)
{
	PriorityQueue<int> queue;
	ASSERT_NO_THROW(queue.front(1));
	ASSERT_NO_THROW(queue.front(2));
	ASSERT_NO_THROW(queue.front(3));
}

TEST(PriorityQueue, can_use_method_push)
{
	PriorityQueue<int> queue;
	ASSERT_NO_THROW(queue.push(2));
}

TEST(PriorityQueue, can_use_method_pop)
{
	PriorityQueue<int> queue;
	ASSERT_NO_THROW(queue.pop());
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