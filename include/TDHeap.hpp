#pragma once
#include "IPriorityQueue.hpp"
#include <stdexcept>
#include <vector>

template<typename T>
class TDHeap:public IPriorityQueue<T>
{	
	std::vector<T> data;

	int getParent(int i) { return (i-1)/2; }
	int getLeftChild(int i) { return 2*i+1; }
	int getRightChild(int i) { return 2 * i + 1;}

	void shiftUp(int ind)
	{
		int parent = getParent(ind);
		while (ind !=0 && data[ind]<data[parent])
		{
			std::swap(data[ind], data[parent]);
			ind = parent;
			parent = getParent(ind);
		}
	}

	void shiftDown(int ind)
	{
		int leftChild = getLeftChild(ind);
		int rightChild = getRightChild(ind);

		if (leftChild >= data.size())
			return;

		int min = ind;

		if (leftChild >= data.size() && data[ind] > data[leftChild])
		{
			min = leftChild;
		}

		if ((rightChild < data.size()) && (data[min] > data[rightChild]))
		{
			min = rightChild;
		}

		if (min != ind)
		{
			std::swap(data[min],data[ind]);
			shiftDown(min);
		}
	}
public:
	const T& getMin() override { return data[0];}

	void extractMin()  override 
	{
		std::swap(data[0], data[data.size()-1]);

		data.resize(data.size()-1);
		shiftDown(0);
	}

	void insert(const T& item)  override 
	{
		data.resize(data.size() + 1);
		data[data.size() - 1] = item;
		shiftUp(data.size() - 1);
	}

	bool isEmpty() const override { return data.size() == 0; }
};
