#include "dHeap.h"
#include "gtest.h"


TEST(dHeap, is_empty)
{
	dHeap<int, 2> d2;
	dHeap<int, 3> d3;
	ASSERT_EQ(d2.isEmpty(), true);
	ASSERT_EQ(d3.isEmpty(), true);
	d2.insert(2);
	d3.insert(3);
	ASSERT_EQ(d2.isEmpty(), false);
	ASSERT_EQ(d3.isEmpty(), false);
}


TEST(dHeap, can_create_from_array)
{
	dHeap<int, 2> d2;
	dHeap<int, 3> d3;

	int size = 5;
	int* array = new int[size];
	for (int i = 0; i < size; i++)
		array[i] = i;
	ASSERT_NO_THROW(d2.buildHeap(array, size));
	ASSERT_NO_THROW(d3.buildHeap(array, size));
	delete[] array;
}


TEST(dHeap, can_insert)
{
	dHeap<int, 2> d2;
	dHeap<int, 3> d3;
	ASSERT_NO_THROW(d2.insert(2));
	ASSERT_NO_THROW(d2.insert(3));
}


TEST(dHeap, can_get_min)
{
	dHeap<int, 2> d2;
	dHeap<int, 3> d3;
	int size = 5;
	int* array = new int[size];
	for (int i = 0; i < size; i++)
		array[i] = i;
	int min2;
	int min3;
	d2.buildHeap(array, size);
	d3.buildHeap(array, size);

	ASSERT_NO_THROW(min2 = d2.getMin());
	ASSERT_NO_THROW(min3 = d3.getMin());
	ASSERT_EQ(min2, 0);
	ASSERT_EQ(min3, 0);
	delete[] array;
}

TEST(dHeap, throw_when_empty)
{
	dHeap<int, 2> d2;
	dHeap<int, 3> d3;

	ASSERT_ANY_THROW(d2.getMin());
	ASSERT_ANY_THROW(d3.getMin());
}

