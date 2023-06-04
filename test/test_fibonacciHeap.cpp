#include "fibonacciHeap.h"
#include "gtest.h"


TEST(FibonacciHeap, is_empty)
{
	FibonacciHeap<int, int> f;
	ASSERT_EQ(f.isEmpty(), true);
	f.insert(2, 2);
	ASSERT_EQ(f.isEmpty(), false);
}



TEST(FibonacciHeap, can_insert)
{
	FibonacciHeap<int, int> f;
	ASSERT_NO_THROW(f.insert(2, 3));
}


TEST(FibonacciHeap, can_get_min)
{
	FibonacciHeap<int, int> f;
	int min;
	f.insert(4, 2);
	f.insert(1, 1);
	f.insert(8, 9);
	ASSERT_NO_THROW(min = f.getMin());
	ASSERT_EQ(min, 1);
}

TEST(FibonacciHeap, throw_when_empty)
{
	FibonacciHeap<int, int> f;
	ASSERT_ANY_THROW(f.getMin());
}