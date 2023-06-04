#include <gtest.h>
#include "IPriorityQueue.hpp"
#include "TRbTree.hpp"

//TREE TESTS
//create
//���� ������� �������
TEST(TRbTree, can_create_tree)
{
	ASSERT_NO_THROW(TRbTree<int> rbTree);
}

//insert
//���� �������� �������
TEST(TRbTree, can_append_data)
{
	TRbTree<int> rbTree;

	ASSERT_NO_THROW(rbTree.insert(1));
	ASSERT_NO_THROW(rbTree.insert(7));
	ASSERT_NO_THROW(rbTree.insert(11));
	ASSERT_NO_THROW(rbTree.insert(42));
	ASSERT_NO_THROW(rbTree.insert(9));
	ASSERT_NO_THROW(rbTree.insert(0));
	ASSERT_NO_THROW(rbTree.insert(18));
	ASSERT_NO_THROW(rbTree.insert(21));
	ASSERT_NO_THROW(rbTree.insert(3));
	ASSERT_NO_THROW(rbTree.insert(14));
}

//finde
//���� ����� ������� �� ������������� �����
TEST(TRbTree, can_finde_data_by_existing_key)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(5);

	ASSERT_NO_THROW(rbTree.find(1));
}

//��������� ������� ������ ������ ������
TEST(TRbTree, found_element_contains_correct_data)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(2);
	rbTree.insert(3);
	rbTree.insert(10);

	ASSERT_EQ(rbTree.find(3), 3);
}

//����� �� �� ������������� ����� �������� � ������
TEST(TRbTree, finde_by_non_exist_key_throw_exception)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(3);
	rbTree.insert(10);

	ASSERT_ANY_THROW(rbTree.find(5));
}

//remove
//���� ������� ������� �� ������������� �����
TEST(TRbTree, can_delete_data_by_key)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(3);
	rbTree.insert(10);

	ASSERT_NO_THROW(rbTree.remove(5));
}

//��������� ������� ���������
TEST(TRbTree, data_really_deliting)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(3);
	rbTree.insert(10);

	rbTree.remove(5);
	ASSERT_ANY_THROW(rbTree.find(5));
}

//�������� �� �� ������������� ����� �� �������� � ������
TEST(TRbTree, delete_by_non_exist_key_not_throw_exception)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(3);
	rbTree.insert(10);

	ASSERT_NO_THROW(rbTree.remove(6));
}

//���� �������� ���������� �������
TEST(TRbTree, can_get_min_data)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(3);
	rbTree.insert(10);

	ASSERT_NO_THROW(rbTree.getMin());
}

//����������� ������� ��������� ���������
TEST(TRbTree, min_data_finds_correctly)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(3);
	rbTree.insert(3);
	rbTree.insert(10);

	ASSERT_EQ(rbTree.getMin(),1);
}

//����������� ������� �����������
TEST(TRbTree, min_data_extracts)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(3);
	rbTree.insert(10);

	ASSERT_NO_THROW(rbTree.extractMin());
	ASSERT_NE(rbTree.getMin(), 1);
}

TEST(TRbTree, insert_and_extract_works_correctly)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(3);
	rbTree.insert(3);
	rbTree.insert(10);

	ASSERT_EQ(rbTree.getMin(), 1);
	rbTree.extractMin();

	ASSERT_EQ(rbTree.getMin(), 3);
	rbTree.extractMin();

	ASSERT_EQ(rbTree.getMin(), 3);
	rbTree.extractMin();

	ASSERT_EQ(rbTree.getMin(), 10);
	rbTree.extractMin();
}

//isEmpty �������� ���������
TEST(TRbTree, isEmpty_works_correctly)
{
	TRbTree<int> rbTree;

	ASSERT_EQ(rbTree.isEmpty(), true);
	rbTree.insert(0);
	ASSERT_EQ(rbTree.isEmpty(), false);
}