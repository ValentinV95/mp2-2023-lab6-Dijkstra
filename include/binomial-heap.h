//binomial heap
//

#pragma once
#include "queue.h"

template<typename N, typename T>
class BinomHeap : public priority_queue<N, T>{
private:
	class Node {
	public:
		N key;
		T data;
		Node* child;
		Node* brother;

		Node()
		{
			this->child = nullptr;
			this->data = 0;
			this->brother = nullptr;
			this->degree = 0;
		}

		Node(N key, T data, Node* child = nullptr, Node* brother = nullptr)
		{
			this->key = key;
			this->child = child;
			this->data = data;
			this->brother = brother;
		}
	};

	int degree;
	Node* Head;
	Node* prev;

	void merge(BinomHeap<N, T>& secondHeap)
	{
		if (secondHeap.Head != nullptr)
		{
			if (this->Head != nullptr)
			{
				Node* curr_firstHeap = this->Head;
				Node* curr_secondHeap = secondHeap.Head;
				if (this->degree <= secondHeap.degree)
				{
					prev = curr_firstHeap;
					curr_firstHeap = curr_firstHeap->brother;
				}
				else
				{
					prev = curr_secondHeap;
					curr_secondHeap = curr_secondHeap->brother;
				}

				while (curr_firstHeap != nullptr && curr_secondHeap != nullptr)
				{
					if (this->degree <= secondHeap.degree)
					{
						prev->brother = curr_firstHeap;
						curr_firstHeap = curr_firstHeap->brother;
					}
					else
					{
						prev->brother = curr_secondHeap;
						curr_secondHeap = curr_secondHeap->brother;
					}
					prev = prev->brother;
				}

				if (curr_firstHeap == nullptr)
					prev->brother = curr_secondHeap;
				else
					prev->brother = curr_firstHeap;
			}
			else
			{
				this->Head = secondHeap.Head;
			}
		}
		else {}
	}
public:
	BinomHeap()
	{
		Head = nullptr;
		prev = nullptr;
	}

	BinomHeap(N key, T data, Node* child = nullptr, Node* brother = nullptr)
	{
		Head = new Node(key, data, child, brother);
		prev = nullptr;
		degree = 0;
	}

	BinomHeap(Node* newHead)
	{
		Head = new Node(newHead->key, newHead->data, newHead->child, newHead->brother);
		prev = nullptr;
		degree = 0;
	}

	void insert(N key, T width)
	{
		BinomHeap<N, T> new_Heap(key, width);
		merge(new_Heap);
		degree++;
	}

	T getMinimum()
	{
		Node* root_tmp = Head;
		Node* curr = Head;
		Node* min = Head;

		if (Head != nullptr)
			curr = Head->brother;

		while (curr != nullptr)
		{
			if (curr->data < min->data)
			{
				min = curr;
				prev = Head;
			}
			curr = curr->brother;
			Head = Head->brother;
		}

		return min->data;
	}

	void extractMin()
	{
		Node* curr = Head->brother;		
		prev = nullptr;

		Node* min_del = Head;

		while (curr != nullptr)
		{
			if (curr->data < min_del->data)
			{
				min_del = curr;
				prev = Head;
			}
			curr = curr->brother;
			Head = Head->brother;
		}

		if (prev == nullptr)
			Head = min_del->brother;
		else
			prev->brother = min_del->brother;

		Node* curr_child = min_del->child;
		BinomHeap<N, T> newHeap;
		while (curr_child != nullptr)
		{
			BinomHeap<N, T> tmp(curr_child);
			curr_child = curr_child->brother;
			newHeap.merge(tmp);
		}
		this->merge(newHeap);

		delete min_del;
	}
};