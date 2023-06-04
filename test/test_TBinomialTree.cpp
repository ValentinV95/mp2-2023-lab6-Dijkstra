#include <gtest.h>
#include "IPriorityQueue.hpp"
#include "TBinomialTree.hpp"

//���� ������� ������������ ����
TEST(TBinomialTree, can_create_binomial_tree)
{
	ASSERT_NO_THROW(TBinomialTree<int> tree);
}

//���� �������� �������
TEST(TBinomialTree, can_insert_element)
{
	TBinomialTree<int> tree;
	ASSERT_NO_THROW(tree.insert(1));
}

//���� �������� ���������� �������
TEST(TBinomialTree, can_get_min)
{
	TBinomialTree<int> tree;

	tree.insert(1);
	tree.insert(3);

	ASSERT_NO_THROW(tree.getMin());
}

//����������� ������� ��������� ���������
TEST(TBinomialTree, min_gets_correctly)
{
	TBinomialTree<int> tree;

	tree.insert(1);
	tree.insert(3);

	ASSERT_EQ(tree.getMin(), 1);
}

//���� ������ ����������� �������
TEST(TBinomialTree, can_extract_min)
{
	TBinomialTree<int> tree;

	tree.insert(1);
	tree.insert(3);

	ASSERT_NO_THROW(tree.extractMin());
}

//����������� ������� ����������� ���������
TEST(TBinomialTree, min_extracts_correctly)
{
	TBinomialTree<int> tree;

	tree.insert(1);
	tree.insert(3);
	tree.insert(2);
	
	tree.extractMin();
	ASSERT_EQ(tree.getMin(),2);
}

//isEmpty �������� ���������
TEST(TBinomialTree, isEmpty_works_correctly)
{
	TBinomialTree<int> tree;

	ASSERT_EQ(tree.isEmpty(), true);

	tree.insert(1);
	tree.insert(3);
	tree.insert(2);

	ASSERT_EQ(tree.isEmpty(), false);
}