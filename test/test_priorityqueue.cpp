#include <gtest.h>
#include "priorityqueue.hpp"

TEST(PriorityQueue, wrong_type_number_in_method)
{
	ASSERT_ANY_THROW(PriorityQueue<int> queue(0));
	ASSERT_ANY_THROW(PriorityQueue<int> queue(4));
}

TEST(PriorityQueue, cannot_use_method_front_in_empty_queue)
{
	PriorityQueue<int> q1(1);
	ASSERT_ANY_THROW(q1.front());
	PriorityQueue<int> q2(2);
	ASSERT_ANY_THROW(q2.front());
	PriorityQueue<int> q3(3);
	ASSERT_ANY_THROW(q3.front());
}

TEST(PriorityQueue, can_use_method_front_in_queue)
{
	PriorityQueue<int> q1(1);
	q1.push(3);
	ASSERT_NO_THROW(q1.front());
	PriorityQueue<int> q2(2);
	q2.push(3);
	ASSERT_NO_THROW(q2.front());
	PriorityQueue<int> q3(3);
	q3.push(3);
	ASSERT_NO_THROW(q3.front());
}

TEST(PriorityQueue, can_use_method_push)
{
	PriorityQueue<int> q1(1);
	ASSERT_NO_THROW(q1.push(1));
	PriorityQueue<int> q2(2);
	ASSERT_NO_THROW(q2.push(2));
	PriorityQueue<int> q3(3);
	ASSERT_NO_THROW(q3.push(3));
}

TEST(PriorityQueue, can_use_method_pop)
{
	PriorityQueue<int> q1(1);
	ASSERT_NO_THROW(q1.pop());
	PriorityQueue<int> q2(2);
	ASSERT_NO_THROW(q2.pop());
	PriorityQueue<int> q3(3);
	ASSERT_NO_THROW(q3.pop());
}

TEST(PriorityQueue, can_use_method_size)
{
	PriorityQueue<int> q1(1);
	ASSERT_NO_THROW(q1.size());
	PriorityQueue<int> q2(2);
	ASSERT_NO_THROW(q2.size());
	PriorityQueue<int> q3(3);
	ASSERT_NO_THROW(q3.size());
}

TEST(PriorityQueue, can_use_method_is_empty)
{
	PriorityQueue<int> q1(1);
	ASSERT_NO_THROW(q1.isEmpty());
	PriorityQueue<int> q2(2);
	ASSERT_NO_THROW(q2.isEmpty());
	PriorityQueue<int> q3(3);
	ASSERT_NO_THROW(q3.isEmpty());
}