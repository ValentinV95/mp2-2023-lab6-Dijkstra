#pragma once

#include"gtest.h"
#include"TDHeap.h"

TEST(DHEAP_QUEUE, can_create_empty_heap)
{
	ASSERT_NO_THROW(TDHeap<size_t> heap);
}

TEST(DHEAP_QUEUE, can_insert_element)
{
	TDHeap<size_t, 3> heap;
	ASSERT_NO_THROW(heap.insert(7));
}

TEST(DHEAP_QUEUE, can_insert_many_elements)
{
	TDHeap<size_t, 3> heap;
	ASSERT_NO_THROW(heap.insert(7));
	ASSERT_NO_THROW(heap.insert(6));
	ASSERT_NO_THROW(heap.insert(3));
	ASSERT_NO_THROW(heap.insert(2));
	ASSERT_NO_THROW(heap.insert(22));
	ASSERT_NO_THROW(heap.insert(45));
}

TEST(DHEAP_QUEUE, can_get_min)
{
	TDHeap<size_t, 3> heap;
	heap.insert(7);
	heap.insert(6);
	heap.insert(22);
	heap.insert(1);
	EXPECT_EQ(1, heap.getMin());
}

TEST(DHEAP_QUEUE, can_extract_min)
{
	TDHeap<size_t, 3> heap;
	heap.insert(7);
	heap.insert(6);
	heap.insert(22);
	heap.insert(1);
	ASSERT_NO_THROW(heap.extractMin());
}

TEST(DHEAP_QUEUE, extract_min_works_correctly)
{
	TDHeap<size_t, 3> heap;
	heap.insert(7);
	heap.insert(6);
	heap.insert(22);
	heap.insert(1);
	heap.extractMin();
	EXPECT_EQ(6, heap.getMin());
}

TEST(DHEAP_QUEUE, can_sort_array_with_bh)
{
	TDHeap<size_t, 3> heap;
	size_t arr[] = { 75,152,634,1535,643,1,256,547,342,124 };
	for (size_t i = 0; i < 10; i++)
	{
		heap.insert(arr[i]);
	}
	size_t arrSorted[10];
	for (size_t i = 0; i < 10; i++)
	{
		arrSorted[i] = heap.getMin();
		heap.extractMin();
	}
	for (size_t i = 0; i < 9; i++)
	{
		EXPECT_EQ(true, arrSorted[i] < arrSorted[i + 1]);
	}
}