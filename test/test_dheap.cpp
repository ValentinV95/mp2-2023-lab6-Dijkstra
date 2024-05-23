#include <gtest.h>
#include "dheap.h"

TEST(DHeap, can_create)
{
	ASSERT_NO_THROW(DHeap<int> h);
}

TEST(DHeap, can_copy)
{
	DHeap<int> h;
	ASSERT_NO_THROW(DHeap<int> h1(h));
}

TEST(DHeap, can_assign)
{
	DHeap<int> h;
	DHeap<int> h1;
	ASSERT_NO_THROW(h1 = h);
}

TEST(DHeap, copied_heaps_have_own_memory)
{
	DHeap<int> h;
	h.push(42);
	DHeap<int> h1(h);
	h.push(12);
	EXPECT_EQ(42, h1.top());
}

TEST(DHeap, assigned_heaps_have_own_memory)
{
	DHeap<int> h;
	DHeap<int> h1;
	h.push(42);
	h1 = h;
	h.push(12);
	EXPECT_EQ(42, h1.top());
}

TEST(DHeap, can_insert)
{
	DHeap<int> h;
	ASSERT_NO_THROW(h.push(42));
}

TEST(DHeap, can_pop)
{
	DHeap<int> h;
	h.push(42);
	ASSERT_NO_THROW(h.pop());
}

TEST(DHeap, can_pop_from_empty)
{
	DHeap<int> h;
	ASSERT_NO_THROW(h.pop());
}

TEST(DHeap, can_get_size)
{
	DHeap<int> h;
	ASSERT_EQ(0, h.size());
	h.push(42);
	ASSERT_EQ(1, h.size());
	h.pop();
	ASSERT_EQ(0, h.size());
	h.pop();
	ASSERT_EQ(0, h.size());
}

TEST(DHeap, can_check_empty)
{
	DHeap<int> h;
	ASSERT_TRUE(h.empty());
	h.push(42);
	ASSERT_FALSE(h.empty());
	h.pop();
	ASSERT_TRUE(h.empty());
	h.pop();
	ASSERT_TRUE(h.empty());
}