#include "red_black_tree.h"
#include "d_heap.h"
#include "binomial_heap.h"

#include <gtest.h>

TEST(RedBlackTreeQueue, can_create_queue)
{
	ASSERT_NO_THROW((RedBlackTreeQueue<int, size_t>()), GTEST_FATAL_FAILURE_);
}

TEST(DHeapQueue, can_create_queue)
{
	ASSERT_NO_THROW((DHeapQueue<3, int, size_t>(5)), GTEST_FATAL_FAILURE_);
}

TEST(DHeapQueue, throws_when_create_queue_with_negative_size)
{
	EXPECT_THROW((DHeapQueue<3, int, size_t>(-1)), std::exception);
}

TEST(DHeapQueue, throws_when_create_queue_with_zero_size)
{
	EXPECT_THROW((DHeapQueue<3, int, size_t>(0)), std::exception);
}

TEST(BinomialHeapQueue, can_create_queue)
{
	ASSERT_NO_THROW((BinomialHeapQueue<int, size_t>()), GTEST_FATAL_FAILURE_);
}

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

TEST(DHeapQueue, cant_insert_too_many_items)
{
	DHeapQueue<2, int, size_t> Q(1);
	Q.insert(1, 5);
	EXPECT_ANY_THROW(Q.insert(2, 6));
}

TEST(BinomialHeapQueue, can_insert_item)
{
	BinomialHeapQueue<int, size_t> Q;
	ASSERT_NO_THROW(Q.insert(1, 5));
}

TEST(RedBlackTreeQueue, can_get_minimum)
{
	RedBlackTreeQueue<int, size_t> Q;
	Q.insert(1, 5);
	Q.insert(2, 6);
	EXPECT_EQ(5, Q.get_min());
}

TEST(DHeapQueue, can_get_minimum)
{
	DHeapQueue<3, int, size_t> Q(5);
	Q.insert(1, 5);
	Q.insert(2, 6);
	EXPECT_EQ(5, Q.get_min());
}

TEST(BinomialHeapQueue, can_get_minimum)
{
	BinomialHeapQueue<int, size_t> Q;
	Q.insert(1, 5);
	Q.insert(2, 6);
	EXPECT_EQ(5, Q.get_min());
}

TEST(RedBlackTreeQueue, cant_get_minimum_from_empty_queue)
{
	RedBlackTreeQueue<int, size_t> Q;
	EXPECT_ANY_THROW(Q.get_min());
	Q.insert(1, 5);
	Q.extract_min();
	EXPECT_ANY_THROW(Q.get_min());
}

TEST(DHeapQueue, cant_get_minimum_from_empty_queue)
{
	DHeapQueue<3, int, size_t> Q(5);
	EXPECT_ANY_THROW(Q.get_min());
	Q.insert(1, 5);
	Q.extract_min();
	EXPECT_ANY_THROW(Q.get_min());
}

TEST(BinomialHeapQueue, cant_get_minimum_from_empty_queue)
{
	BinomialHeapQueue<int, size_t> Q;
	EXPECT_ANY_THROW(Q.get_min());
	Q.insert(1, 5);
	Q.extract_min();
	EXPECT_ANY_THROW(Q.get_min());
}

TEST(RedBlackTreeQueue, can_extract_min)
{
	RedBlackTreeQueue<int, size_t> Q;
	Q.insert(1, 5);
	ASSERT_NO_THROW(Q.extract_min());
}

TEST(DHeapQueue, can_extract_min)
{
	DHeapQueue<3, int, size_t> Q(5);
	Q.insert(1, 5);
	ASSERT_NO_THROW(Q.extract_min());
}

TEST(BinomialHeapQueue, can_extract_min)
{
	BinomialHeapQueue<int, size_t> Q;
	Q.insert(1, 5);
	ASSERT_NO_THROW(Q.extract_min());
}

TEST(RedBlackTreeQueue, cant_extract_minimum_from_empty_queue)
{
	RedBlackTreeQueue<int, size_t> Q;
	EXPECT_ANY_THROW(Q.extract_min());
	Q.insert(1, 5);
	Q.extract_min();
	EXPECT_ANY_THROW(Q.extract_min());
}

TEST(DHeapQueue, cant_extract_minimum_from_empty_queue)
{
	DHeapQueue<3, int, size_t> Q(5);
	EXPECT_ANY_THROW(Q.extract_min());
	Q.insert(1, 5);
	Q.extract_min();
	EXPECT_ANY_THROW(Q.extract_min());
}

TEST(BinomialHeapQueue, cant_extract_minimum_from_empty_queue)
{
	BinomialHeapQueue<int, size_t> Q;
	EXPECT_ANY_THROW(Q.extract_min());
	Q.insert(1, 5);
	Q.extract_min();
	EXPECT_ANY_THROW(Q.extract_min());
}
