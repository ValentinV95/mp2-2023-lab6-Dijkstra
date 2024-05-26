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

TEST(BHeap, can_insert_into_emptied_heap)
{
	BHeap<int> h;
	h.push(42);
	h.push(43);
	h.push(44);
	h.push(45);
	h.pop();
	h.pop();
	h.pop();
	h.pop();
	h.push(111);
	EXPECT_EQ(111, h.top());
	EXPECT_EQ(1, h.size());
}

// A rather bad heapsort implementation for testing out the heap functions
TEST(BHeap, heapsort_test)
{
	std::vector<int> v(100);
	std::generate(v.begin(), v.end(), std::rand);
	std::vector<int> res;
	BHeap<int> h;

	for (auto& i : v)
		h.push(i);

	for (int i = 0; i < v.size(); i++)
	{
		res.push_back(h.top());
		h.pop();
	}

	for (int i = 0; i < res.size() - 1; i++)
		ASSERT_TRUE(res[i] <= res[i + 1]);
}