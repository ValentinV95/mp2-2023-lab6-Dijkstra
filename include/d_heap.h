#pragma once

#include "priority_queue.h"

template <int D, class P, class T>
class DHeapQueue : public PriorityQueue<P, T>
{
private:
	struct Node
	{
		P priority;
		T data;
	};
	Node* pMem;
	size_t capacity;
	size_t size;

	void sift_up(size_t index)
	{
		size_t parent = (index - 1) / D;
		while (index != 0 && pMem[index].priority < pMem[parent].priority)
		{
			Node tmp = pMem[index];
			pMem[index] = pMem[parent];
			pMem[parent] = tmp;
			index = parent;
			parent = (index - 1) / D;
		}
	}
	size_t get_min_child(size_t index)
	{
		size_t min_child = index * D + 1;
		for (int i = 2; i < D + 1 && min_child < size; i++)
		{
			if (pMem[index * D + i].priority < pMem[min_child].priority)
			{
				if (index * D + i < size)
				{
					min_child = index * D + i;
				}
				else break;
			}
		}
		return min_child;
	}
	void sift_down(size_t index)
	{
		size_t child = get_min_child(index);
		
		while (index * D + 1 < size && pMem[index].priority > pMem[child].priority)
		{
			Node tmp = pMem[index];
			pMem[index] = pMem[child];
			pMem[child] = tmp;
			
			index = child;
			child = get_min_child(index);
		}
	}
public:
	DHeapQueue(size_t sz) : capacity(sz), size(0)
	{
		if (sz <= 0)
		{
			throw std::exception("Heap size should be greater than zero");
		}
		else pMem = new Node[capacity];
	}

	void insert(const P& _priority, const T& _data) override
	{
		pMem[size] = Node{ _priority, _data };
		sift_up(size++);
	}
	T extract_min() override
	{
		T ret_data = pMem[0].data;
		pMem[0] = pMem[--size];
		
		sift_down(0);
		return ret_data;
	}

	bool empty() const override
	{
		return size == 0;
	}

	~DHeapQueue()
	{
		delete[] pMem;
	}
};
