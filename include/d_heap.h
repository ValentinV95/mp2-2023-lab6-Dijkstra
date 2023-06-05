#pragma once

#include <vector>

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
	std::vector<Node> pMem;

	void swap(size_t first, size_t second)
	{
		Node tmp = pMem[first];
		pMem[first] = pMem[second];
		pMem[second] = tmp;
	}
	void sift_up(size_t index)
	{
		size_t parent = (index - 1) / D;
		while (index != 0 && pMem[index].priority < pMem[parent].priority)
		{
			swap(index, parent);
			index = parent;
			parent = (index - 1) / D;
		}
	}
	size_t get_min_child(size_t index)
	{
		size_t min_child = index * D + 1;
		for (int i = 2; i < D + 1 && index * D + i < pMem.size(); i++)
		{
			if (pMem[index * D + i].priority < pMem[min_child].priority)
			{
				min_child = index * D + i;
			}
		}
		return min_child;
	}
	void sift_down(size_t index)
	{
		size_t child = get_min_child(index);
		while (child < pMem.size() && pMem[index].priority > pMem[child].priority)
		{
			swap(index, child);
			index = child;
			child = get_min_child(index);
		}
	}
public:
	bool empty() const override
	{
		return pMem.empty();
	}
	void insert(const P& _priority, const T& _data) override
	{
		pMem.push_back(Node{ _priority, _data });
		sift_up(pMem.size() - 1);
	}
	const T& get_min() const override
	{
		if (pMem.empty())
		{
			throw std::exception("Queue is empty");
		}
		return pMem[0].data;
	}
	void extract_min() override
	{
		if (pMem.empty())
		{
			throw std::exception("Queue is empty");
		}
		swap(0, pMem.size() - 1);
		pMem.pop_back();
		sift_down(0);
	}
};
