#include "AvlTree.h"
#include "gtest.h"

TEST(avlTree, can_insert)
{
	avlTree<int, int> avl;
	ASSERT_NO_THROW(avl.insert(1,1));
}

TEST(avlTree, can_delete)
{
	avlTree<int, int> avl;
	avl.insert(1, 1);
	ASSERT_NO_THROW(avl.delElem(1));
}

TEST(avlTree, throw_when_delete_non_existent_element)
{
	avlTree<int, int> avl;
	ASSERT_ANY_THROW(avl.delElem(1));
}

TEST(avlTree, can_find)
{
	avlTree<int, int> avl;
	avl.insert(1, 1);
	ASSERT_NO_THROW(avl.getElement(1));
}

TEST(avlTree, can_chagne_value_find)
{
	avlTree<int, int> avl;
	int val = 1;
	avl.insert(1, val);
	avl.getElement(1) = val+1;
	EXPECT_NE(avl.getElement(1), val);
}

TEST(avlTree, throw_when_find_non_existent_element)
{
	avlTree<int, int> avl;
	ASSERT_ANY_THROW(avl.getElement(1));
}