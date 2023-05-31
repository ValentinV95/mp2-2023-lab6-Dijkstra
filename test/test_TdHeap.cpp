#include <gtest.h>
#include "IPriorityQueue.hpp"
#include "TDHeap.hpp"

//Могу создать биномиальную кучу
TEST(TDHeap, can_create_heap)
{
	ASSERT_NO_THROW(TDHeap<int> tree;);
}

//Могу добавить элемент
TEST(TDHeap, can_insert_element)
{
	TDHeap<int> tree;
	ASSERT_NO_THROW(tree.insert(1););
}

//Могу получить минимальый элемент
TEST(TDHeap, can_get_min)
{
	TDHeap<int> tree;

	tree.insert(1);
	tree.insert(3);

	ASSERT_NO_THROW(tree.getMin(), 1);
}

//Минимальный элемент находится правильно
TEST(TDHeap, min_gets_correctly)
{
	TDHeap<int> tree;

	tree.insert(1);
	tree.insert(3);

	ASSERT_EQ(tree.getMin(), 1);
}

//Могу извлеч минимальный элемент
TEST(TDHeap, can_extract_min)
{
	TDHeap<int> tree;

	tree.insert(1);
	tree.insert(3);

	ASSERT_NO_THROW(tree.extractMin());
}

//Минимальный элемент извлекается правильно
TEST(TDHeap, min_extracts_correctly)
{
	TDHeap<int> tree;

	tree.insert(1);
	tree.insert(3);
	tree.insert(2);

	tree.extractMin();
	ASSERT_EQ(tree.getMin(), 2);
}

//isEmpty работает правильно
TEST(TDHeap, isEmpty_works_correctly)
{
	TDHeap<int> tree;

	ASSERT_EQ(tree.isEmpty(), true);

	tree.insert(1);
	tree.insert(3);
	tree.insert(2);

	ASSERT_EQ(tree.isEmpty(), false);
}

TEST(TDHeap, insert_and_extract_works_correctly)
{
	TDHeap<int> tree;

	tree.insert(1);
	tree.insert(3);
	tree.insert(3);
	tree.insert(10);

	ASSERT_EQ(tree.getMin(), 1);
	tree.extractMin();

	ASSERT_EQ(tree.getMin(), 3);
	tree.extractMin();

	ASSERT_EQ(tree.getMin(), 3);
	tree.extractMin();

	ASSERT_EQ(tree.getMin(), 10);
	tree.extractMin();
}