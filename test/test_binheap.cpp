#include <gtest.h>
#include "binomialheap.hpp"

TEST(BinHeap, can_create_binheap)
{
	ASSERT_NO_THROW(BinHeap<int> bheap);
}

TEST(BinHeap, can_use_method_size_in_empty_binheap)
{
	BinHeap<int> binheap;
	ASSERT_NO_THROW(binheap.size());
}

TEST(BinHeap, using_method_size_in_empty_binheap_true)
{
	BinHeap<int> binheap;
	EXPECT_EQ(0, binheap.size());
}

TEST(BinHeap, can_use_method_is_empty_in_empty_binheap)
{
	BinHeap<int> binheap;
	ASSERT_NO_THROW(binheap.isEmpty());
}

TEST(BinHeap, using_method_is_empty_in_empty_binheap_true)
{
	BinHeap<int> binheap;
	EXPECT_EQ(true, binheap.isEmpty());
}

TEST(BinHeap, can_use_method_get_min_in_empty_binheap)
{
	BinHeap<int> binheap;
	ASSERT_NO_THROW(binheap.getMin());
}

TEST(BinHeap, using_method_get_min_in_empty_binheap_true)
{
	BinHeap<int> binheap;
	EXPECT_EQ(nullptr, binheap.getMin());
}

TEST(BinHeap, can_use_method_get_min_in_binheap)
{
	BinHeap<int> binheap(2);
	ASSERT_NO_THROW(binheap.getMin());
}

TEST(BinHeap, using_method_get_min_in_binheap_true)
{
	BinHeap<int> binheap(2);
	EXPECT_EQ(2, binheap.getMin()->data);
}

TEST(BinHeap, can_insert_to_empty_binheap)
{
	BinHeap<int> binheap;
	ASSERT_NO_THROW(binheap.insert(1));
}

TEST(BinHeap, inserting_to_empty_binheap_true)
{
	BinHeap<int> binheap;
	binheap.insert(1);
	EXPECT_EQ(1, binheap.getMin()->data);
}

TEST(BinHeap, can_insert_to_binheap)
{
	BinHeap<int> binheap(3);
	ASSERT_NO_THROW(binheap.insert(1));
}

TEST(BinHeap, inserting_to_binheap_true)
{
	BinHeap<int> binheap(3);
	binheap.insert(1);
	EXPECT_EQ(1, binheap.getMin()->data);
}

TEST(BinHeap, can_extract_min_in_empty_binheap)
{
	BinHeap<int> binheap;
	ASSERT_NO_THROW(binheap.extractMin());
}

TEST(BinHeap, can_extract_min_in_binheap)
{
	BinHeap<int> binheap(3);
	ASSERT_NO_THROW(binheap.extractMin());
}

TEST(BinHeap, extracting_min_in_binheap_true)
{
	BinHeap<int> binheap(3);
	binheap.insert(1);
	binheap.extractMin();
	EXPECT_EQ(3, binheap.getMin()->data);
}

TEST(BinHeap, can_use_method_clear_in_binheap)
{
	BinHeap<int> binheap(3);
	ASSERT_NO_THROW(binheap.clear());
}