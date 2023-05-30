#include "red_black_tree.h"
#include "d_heap.h"
#include "binomial_heap.h"
#include <gtest.h>

TEST(RedBlackTreeQueue, can_insert_item)
{
	RedBlackTreeQueue<int, size_t> Q;
	ASSERT_NO_THROW(Q.insert(1, 5));
}

TEST(DHeapQueue, can_insert_item)
{
	DHeapQueue<2, int, size_t> Q(5);
	ASSERT_NO_THROW(Q.insert(1, 5));
}

TEST(BinomialHeapQueue, can_insert_item)
{
	BinomialHeapQueue<int, size_t> Q;
	ASSERT_NO_THROW(Q.insert(1, 5));
}

TEST(RedBlackTreeQueue, can_extract_minimum)
{
	RedBlackTreeQueue<int, size_t> Q;
	Q.insert(1, 5);
	Q.insert(2, 6);
	EXPECT_EQ(5, Q.extract_min());
}

TEST(DHeapQueue, can_extract_minimum)
{
	DHeapQueue<3, int, size_t> Q(5);
	Q.insert(1, 5);
	Q.insert(2, 6);
	EXPECT_EQ(5, Q.extract_min());
}

TEST(BinomialHeapQueue, can_extract_minimum)
{
	BinomialHeapQueue<int, size_t> Q;
	Q.insert(1, 5);
	Q.insert(2, 6);
	EXPECT_EQ(5, Q.extract_min());
}