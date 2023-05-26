#pragma once

#include"gtest.h"
#include"TRBtree.h"

TEST(RBT_QUEUE, can_create_empty_tree)
{
	ASSERT_NO_THROW(TRBTree<size_t> tree);
}

TEST(RBT_QUEUE, can_insert_element)
{
	TRBTree<size_t> tree;
	ASSERT_NO_THROW(tree.insert(1));
}

TEST(RBT_QUEUE, can_insert_many_elements)
{
	TRBTree<size_t> tree;
	ASSERT_NO_THROW(tree.insert(1));
	ASSERT_NO_THROW(tree.insert(6));
	ASSERT_NO_THROW(tree.insert(7));
	ASSERT_NO_THROW(tree.insert(5));
	ASSERT_NO_THROW(tree.insert(3));
	ASSERT_NO_THROW(tree.insert(2));
}

TEST(RBT_QUEUE, can_delete_root)
{
	TRBTree<size_t> tree;
	tree.insert(1);
	ASSERT_NO_THROW(tree.erase(1));
}

TEST(RBT_QUEUE, can_delete_leaf)
{
	TRBTree<size_t> tree;
	tree.insert(1);
	tree.insert(2);
	ASSERT_NO_THROW(tree.erase(2));
}

TEST(RBT_QUEUE, can_delete_leaf_correctly)
{
	TRBTree<size_t> tree;

	tree.insert(0);
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);

	tree.erase(3);
	tree.erase(6);
	ASSERT_NO_THROW(tree.search(7));
}

TEST(RBT_QUEUE, can_insert_element_after_delete_root)
{
	TRBTree<size_t> tree;
	
	tree.insert(2);
	tree.insert(1);
	tree.insert(3);
	tree.erase(1);
	ASSERT_NO_THROW(tree.insert(4));
}

TEST(RBT_QUEUE, can_find_element)
{
	TRBTree<size_t> tree;
	tree.insert(1);
	EXPECT_EQ(1, tree.search(1));
}

TEST(RBT_QUEUE, cant_find_element_with_wrong_key)
{
	TRBTree<size_t> tree;
	tree.insert(1);
	ASSERT_ANY_THROW(tree.search(0));
}

TEST(RBT_QUEUE, cant_find_deleted_element)
{
	TRBTree<size_t> tree;
	tree.insert(1);
	tree.insert(2);
	tree.erase(2);
	ASSERT_ANY_THROW(tree.search(2));
}