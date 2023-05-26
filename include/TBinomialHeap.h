#pragma once

#include"PriorityQueue.h"

#include<vector>

template<class T>
class TBinomialHeap: public PriorityQueue<T>
{
	struct Node
	{
		T data;
		Node* parent;
		Node* child;
		Node* sibling;
		size_t childCount;
	};
	Node* fictHead;
	size_t sz;

	void merge(TBinomialHeap<T>& other)
	{
		if (other.fictHead->sibling == nullptr)
		{
			return;
		}
		if(this->fictHead->sibling == nullptr)
		{
			fictHead = other.fictHead;
			other.fictHead = nullptr;
			return;
		}
		Node* thisPrev = this->fictHead;
		Node* thisCur = this->fictHead->sibling;
		Node* otherCur = other.fictHead->sibling;
		while(thisCur != nullptr && otherCur != nullptr)
		{
			Node* otherNext = otherCur->sibling;
			if(thisCur->childCount <= otherCur->childCount)
			{
				Node* next = thisCur->sibling;
				thisCur->sibling = otherCur;
				otherCur->sibling = next;
			}
			else
			{
				thisPrev->sibling = otherCur;
				otherCur->sibling = thisCur;
			}
			thisPrev = thisPrev->sibling;
			thisCur = thisCur->sibling;
			otherCur = otherNext;
		}
		thisPrev = this->fictHead;
		thisCur = thisPrev->sibling;
		Node* thisNext = thisCur->sibling;
		while (thisNext != nullptr)
		{
			if(thisNext->sibling != nullptr)
			{
				if (thisNext->childCount == thisNext->sibling->childCount)
				{
					thisPrev = thisCur;
					thisCur = thisNext;
					thisNext = thisCur->sibling;
					continue;
				}
			}
			if (thisCur->childCount == thisNext->childCount)
			{
				if (thisCur->data < thisNext->data)
				{
					Node* next = thisNext->sibling;
					if(thisCur->child == nullptr)
					{
						thisCur->child = thisNext;
					}
					else 
					{
						Node* child = thisCur->child;
						while (child->sibling != nullptr)
						{
							child = child->sibling;
						}
						child->sibling = thisNext;
					}
					thisNext->parent = thisCur;
					thisNext->sibling = nullptr;
					thisCur->childCount += thisNext->childCount + 1;
					thisCur->sibling = next;
					thisNext = next;
				}
				else
				{
					if(thisNext->child == nullptr)
					{
						thisNext->child = thisCur;
					}
					else
					{
						Node* child = thisNext->child;
						while (child->sibling != nullptr)
						{
							child = child->sibling;
						}
						child->sibling = thisCur;
					}
					thisCur->parent = thisNext;
					thisCur->sibling = nullptr;
					thisNext->childCount += thisCur->childCount + 1;
					thisPrev->sibling = thisNext;
					thisCur = thisNext;
					thisNext = thisNext->sibling;
				}
			}
			else
			{
				thisPrev = thisCur;
				thisCur = thisNext;
				thisNext = thisCur->sibling;
			}
		}
	}

public:
	TBinomialHeap()
	{
		sz = 0;
		fictHead = new Node{ T(),nullptr,nullptr,nullptr, 0 };
	}

	~TBinomialHeap()
	{
		while(sz != 0)
		{
			extractMin();
		}
	}

	void insert(const T& data) override
	{
		TBinomialHeap<T> other;
		other.fictHead->sibling = new Node{ data, nullptr, nullptr, nullptr, 0 };
		merge(other);
		sz++;
	}

	const T& getMin() const override
	{
		Node* cur = fictHead->sibling;
		T min = cur->data;
		while(cur->sibling != nullptr)
		{
			cur = cur->sibling;
			if (cur->data < min)
			{
				min = cur->data;
			}
		}
		return min;
	}

	void extractMin() override
	{
		Node* prev = fictHead;
		Node* cur = fictHead->sibling;
		Node* minPrev = fictHead;
		Node* min = cur;
		while (cur->sibling != nullptr)
		{
			prev = cur;
			cur = cur->sibling;
			if (cur->data < min->data)
			{
				minPrev = prev;
				min = cur;
			}
		}
		std::vector<Node*> minChilds;
		Node* child = min->child;
		while(child != nullptr)
		{
			child->parent = nullptr;
			Node* tmp = child->sibling;
			child->sibling = nullptr;
			minChilds.push_back(child);
			child = tmp;
		}
		minPrev->sibling = min->sibling;
		delete min;
		while(!minChilds.empty())
		{
			TBinomialHeap<T> tmp;
			tmp.fictHead->sibling = minChilds[minChilds.size() - 1];
			this->merge(tmp);
			minChilds.pop_back();
		}
		sz--;
	}
};