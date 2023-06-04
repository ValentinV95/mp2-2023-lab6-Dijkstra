#include "priorityQueue.h"
#include "gtest.h"


TEST(priorityQueue, can_create)
{
	ASSERT_NO_THROW(dHeapQueue<int> d);
	ASSERT_NO_THROW(avlQueue<int> a);
	ASSERT_NO_THROW(fibonacciQueue<int> f);
}

TEST(priorityQueue, can_insert)
{
	dHeapQueue<int> d;
	avlQueue<int> a;
	fibonacciQueue<int> f;
	ASSERT_NO_THROW(d.insert(1));
	ASSERT_NO_THROW(a.insert(1));
	ASSERT_NO_THROW(f.insert(1));
}

TEST(priorityQueue, can_get_min)
{
	dHeapQueue<int> d;
	avlQueue<int> a;
	fibonacciQueue<int> f;
	int min = 1;
	d.insert(min);
	a.insert(min);
	f.insert(min);
	int get;
	ASSERT_NO_THROW(get = d.getMin());
	ASSERT_EQ(get, min);
	ASSERT_NO_THROW(get = a.getMin());
	ASSERT_EQ(get, min);
	ASSERT_NO_THROW(get = f.getMin());
	ASSERT_EQ(get, min);
}

TEST(priorityQueue, throw_when_empty)
{
	dHeapQueue<int> d;
	avlQueue<int> a;
	fibonacciQueue<int> f;
	ASSERT_ANY_THROW(d.getMin());
	ASSERT_ANY_THROW(a.getMin());
	ASSERT_ANY_THROW(f.getMin());
}

TEST(priorityQueue, can_check_empty)
{
	dHeapQueue<int> d;
	avlQueue<int> a;
	fibonacciQueue<int> f;
	ASSERT_EQ(d.isEmpty(), true);
	ASSERT_EQ(a.isEmpty(), true);
	ASSERT_EQ(f.isEmpty(), true);
	d.insert(1);
	a.insert(1);
	f.insert(1);
	ASSERT_EQ(d.isEmpty(), false);
	ASSERT_EQ(a.isEmpty(), false);
	ASSERT_EQ(f.isEmpty(), false);
}
