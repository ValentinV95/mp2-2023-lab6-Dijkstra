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

TEST(DHeap, can_insert_into_emptied_heap)
{
	DHeap<int> h;
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
TEST(DHeap, heapsort_test)
{
	std::vector<int> v(100);
	std::generate(v.begin(), v.end(), std::rand);
	std::vector<int> res;
	DHeap<int> h;

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