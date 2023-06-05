//class D-heap
//
#pragma once
#include <iostream>
#include <vector>
#include "../include/queue.h"

template <typename N, typename T, int D> // D > 1
class DHeap : public priority_queue<N,T>{
private:
	std::vector<std::pair<N, T>> heap;
	int size;

	void swap(int id_left, int id_right)
	{
		std::pair<N, T> tmp = heap[id_left];
		heap[id_left] = heap[id_right];
		heap[id_right] = tmp;
	}

	int id_child(int sequence_number_child, int id_parent)
	{
		return (D * id_parent) + sequence_number_child;
	}

	int id_parent(int id_child)
	{
		return (id_child - 1) / D;
	}

	void shift_up(int id_element)
	{
		while (heap[id_element].second < heap[id_parent(id_element)].second)
		{
			this->swap(id_parent(id_element), id_element);
			id_element = id_parent(id_element);
		}
	}

	int id_min_child(int id_parent)
	{
		int min_child = id_child(1, id_parent);
		for (int i = 2; i < D + 1 && id_child(i, id_parent) < heap.size(); i++)
		{
			if (heap[id_child(i, id_parent)].second < heap[min_child].second)
			{
				min_child = id_child(i, id_parent);
			}
		}
		return min_child;
	}

	void shift_down(int id_element)
	{
		for (int min_child = id_min_child(id_element); min_child < heap.size() && heap[id_element].second > heap[min_child].second; min_child = id_min_child(id_element))
		{
				swap(id_element, min_child);
				id_element = min_child;
		}
	}

public:
	DHeap()
	{
		heap = std::vector<std::pair<N, T>>(0);
		size = 0;
	}

	T getMinimum()
	{
		return heap[0].second;
	}

	void insert(N key, T width)
	{
		heap.push_back(std::pair<N, T>(key, width));
		shift_up(heap.size() - 1);
		size++;
	}

	void extractMin()
	{
		swap(0, heap.size() - 1);
		heap.pop_back();
		shift_down(0);
		size--;
	}
};