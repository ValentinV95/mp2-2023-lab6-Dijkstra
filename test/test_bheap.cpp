#include <gtest.h>
#include "bheap.h"

TEST(BHeap, can_create)
{
	ASSERT_NO_THROW(BHeap<int> h);
}

TEST(BHeap, can_copy)
{
	BHeap<int> h;
	ASSERT_NO_THROW(BHeap<int> h1(h));
}

TEST(BHeap, can_assign)
{
	BHeap<int> h;
	BHeap<int> h1;
	ASSERT_NO_THROW(h1 = h);
}

TEST(BHeap, copied_heaps_have_own_memory)
{
	BHeap<int> h;
	h.push(42);
	BHeap<int> h1(h);
	h.push(12);
	EXPECT_EQ(42, h1.top());
}

TEST(BHeap, assigned_heaps_have_own_memory)
{
	BHeap<int> h;
	BHeap<int> h1;
	h.push(42);
	h1 = h;
	h.push(12);
	EXPECT_EQ(42, h1.top());
}

TEST(BHeap, can_insert)
{
	BHeap<int> h;
	ASSERT_NO_THROW(h.push(42));
}

TEST(BHeap, can_pop)
{
	BHeap<int> h;
	h.push(42);
	ASSERT_NO_THROW(h.pop());
}

TEST(BHeap, can_pop_from_empty)
{
	BHeap<int> h;
	ASSERT_NO_THROW(h.pop());
}

TEST(BHeap, can_get_size)
{
	BHeap<int> h;
	ASSERT_EQ(0, h.size());
	h.push(42);
	ASSERT_EQ(1, h.size());
	h.pop();
	ASSERT_EQ(0, h.size());
	h.pop();
	ASSERT_EQ(0, h.size());
}

TEST(BHeap, can_check_empty)
{
	BHeap<int> h;
	ASSERT_TRUE(h.empty());
	h.push(42);
	ASSERT_FALSE(h.empty());
	h.pop();
	ASSERT_TRUE(h.empty());
	h.pop();
	ASSERT_TRUE(h.empty());
}