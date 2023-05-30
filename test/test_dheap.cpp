#include <gtest.h>
#include "dheap.hpp"

TEST(DHeap, can_use_method_get_min)
{
	DHeap<2, int> dheap(4);
	ASSERT_NO_THROW(dheap.getMin());
}

TEST(DHeap, using_method_get_min_true)
{
	DHeap<2, int> dheap(4);
	EXPECT_EQ(*dheap.getMin(), 4);
}

TEST(DHeap, can_use_method_is_empty)
{
	DHeap<2, int> dheap(4);
	ASSERT_NO_THROW(dheap.isEmpty());
}

TEST(DHeap, using_method_is_empty_true)
{
	DHeap<2, int> dheap;
	EXPECT_EQ(true, dheap.isEmpty());
}

TEST(DHeap, using_method_is_empty_false)
{
	DHeap<2, int> dheap(4);
	EXPECT_EQ(false, dheap.isEmpty());
}

TEST(DHeap, can_use_method_size)
{
	DHeap<2, int> dheap(4);
	ASSERT_NO_THROW(dheap.size());
}

TEST(DHeap, using_method_size_true)
{
	DHeap<2, int> dheap(3);
	EXPECT_EQ(1, dheap.size());
}

TEST(DHeap, can_insert_smth_in_dheap)
{
	DHeap<2, int> dheap(4);
	ASSERT_NO_THROW(dheap.insert(2));
}

TEST(DHeap, inserting_smth_in_dheap_true)
{
	DHeap<2, int> dheap(4);
	dheap.insert(2);
	EXPECT_EQ(*dheap.getMin(), 2);
}

TEST(DHeap, inserting_smth_in_dheap_increase_size)
{
	DHeap<2, int> dheap(4);
	dheap.insert(2);
	EXPECT_EQ(2, dheap.size());
}

TEST(DHeap, can_insert_smth_in_empty_dheap)
{
	DHeap<2, int> dheap;
	ASSERT_NO_THROW(dheap.insert(2));
}

TEST(DHeap, inserting_smth_in_empty_dheap_true)
{
	DHeap<2, int> dheap;
	dheap.insert(2);
	EXPECT_EQ(*dheap.getMin(), 2);
}

TEST(DHeap, can_extract_min_in_dheap)
{
	DHeap<2, int> dheap(4);
	ASSERT_NO_THROW(dheap.extractMin());
}

TEST(DHeap, extracting_min_in_dheap_decrease_size)
{
	DHeap<2, int> dheap(4);
	dheap.extractMin();
	EXPECT_EQ(0, dheap.size());
}

TEST(DHeap, can_extract_min_in_empty_dheap)
{
	DHeap<2, int> dheap;
	ASSERT_NO_THROW(dheap.extractMin());
}
