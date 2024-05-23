#include <gtest.h>
#include "fheap.h"

TEST(FHeap, can_create)
{
	ASSERT_NO_THROW(FHeap<int> h);
}

TEST(FHeap, can_copy)
{
	FHeap<int> h;
	ASSERT_NO_THROW(FHeap<int> h1(h));
}

TEST(FHeap, can_assign)
{
	FHeap<int> h;
	FHeap<int> h1;
	ASSERT_NO_THROW(h1 = h);
}

TEST(FHeap, copied_heaps_have_own_memory)
{
	FHeap<int> h;
	h.push(42);
	FHeap<int> h1(h);
	h.push(12);
	EXPECT_EQ(42, h1.top());
}

TEST(FHeap, assigned_heaps_have_own_memory)
{
	FHeap<int> h;
	FHeap<int> h1;
	h.push(42);
	h1 = h;
	h.push(12);
	EXPECT_EQ(42, h1.top());
}

TEST(FHeap, can_insert)
{
	FHeap<int> h;
	ASSERT_NO_THROW(h.push(42));
}

TEST(FHeap, can_pop)
{
	FHeap<int> h;
	h.push(42);
	ASSERT_NO_THROW(h.pop());
}

TEST(FHeap, can_pop_from_empty)
{
	FHeap<int> h;
	ASSERT_NO_THROW(h.pop());
}

TEST(FHeap, can_get_size)
{
	FHeap<int> h;
	ASSERT_EQ(0, h.size());
	h.push(42);
	ASSERT_EQ(1, h.size());
	h.pop();
	ASSERT_EQ(0, h.size());
	h.pop();
	ASSERT_EQ(0, h.size());
}

TEST(FHeap, can_check_empty)
{
	FHeap<int> h;
	ASSERT_TRUE(h.empty());
	h.push(42);
	ASSERT_FALSE(h.empty());
	h.pop();
	ASSERT_TRUE(h.empty());
	h.pop();
	ASSERT_TRUE(h.empty());
}