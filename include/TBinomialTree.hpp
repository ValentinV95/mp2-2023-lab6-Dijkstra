#pragma once
#include <exception>
#include <stack>
#include "IPriorityQueue.hpp"

template<typename T>
class TBinomialTree :public IPriorityQueue<T>
{
	struct Node
	{
		Node* parent;
		Node* child;
		Node* sibling;
		size_t pow;

		T data;

		Node() {};
	};

	Node* head = nullptr;

	void treeLink(Node* child,Node* parent)
	{
		child->parent = parent;
		child->sibling = parent->child;

		parent->child = child;
		parent->pow++;
	}

	Node* treeMerge(Node* h1, Node* h2)
	{
		Node* res;

		if (h1 == nullptr && h2 != nullptr)
		{
			res = h2;
			h2 = h2->sibling;
		}
		else if (h1 != nullptr && h2 == nullptr)
		{
			res = h1;
			h1 = h1->sibling;
		}
		else
		{
			if (h1->pow <= h2->pow)
			{
				res = h1;
				h1 = h1->sibling;
			}
			else
			{
				res = h2;
				h2 = h2->sibling;
			}
		}

		Node* tail = res;

		while (h1 != nullptr && h2 != nullptr)
		{
			if (h1->pow <= h2->pow)
			{
				tail->sibling = h1;
				h1 = h1->sibling;
			}
			else
			{
				tail->sibling = h2;
				h2 = h2->sibling;
			}

			tail = tail->sibling;
		}

		while (h1 != nullptr)
		{
			tail->sibling = h1;
			h1 = h1->sibling;
			tail = tail->sibling;
		}

		while (h2 != nullptr)
		{
			tail->sibling = h2;
			h2 = h2->sibling;
			tail = tail->sibling;
		}

		return res;
	}

	Node* treeUnion(Node* h1, Node* h2)
	{
		Node* h = treeMerge(h1, h2);

		Node* prev = nullptr;
		Node* current = h;
		Node* next = current->sibling;

		while (next!=nullptr)
		{
			if ((current->pow != next->pow) || (next->sibling != nullptr && next->sibling->pow == current->pow))
			{
				prev = current;
				current = next;
			}
			else if(current->data <= next->data)
			{
				current->sibling = next->sibling;
				treeLink(next,current);
			}
			else
			{
				if (prev == nullptr)
					h = next;
				else
					prev->sibling = next;

				treeLink(current,next);
				current = next;
			}
			next = current->sibling;
		}

		return h;
	}

public:

	const T& getMin() override 
	{ 
		if (isEmpty())
			throw std::exception("BinomialHeap was empty and have not min element");

		Node* current = head->sibling;
		Node* min = head;

		while (current != nullptr)
		{
			if (current->data < min->data)
				min = current;

			current = current->sibling;
		}

		return min->data;
	}

	void extractMin()  override 
	{
		Node* current = head, *prev = nullptr, *prevmin = nullptr;
		Node* min = head;
		Node* h = head;

		while (current != nullptr)
		{
			if (current->data < min->data)
			{
				min = current;
				prevmin = prev;
			}
			prev = current;
			current = current->sibling;
		}

		if (prevmin != nullptr)
		{
			prevmin->sibling = min->sibling;
		}
		else
		{
			h = min->sibling;
		}

		Node* minChild = min->child;
		prev = nullptr;

		while (minChild != nullptr)
		{
			Node* sibling = minChild->sibling;

			minChild->parent = nullptr;

			minChild->sibling = prev;
			prev = minChild;
			minChild = sibling;
		}

		delete min;
		min = nullptr;

		if (h != nullptr || prev != nullptr)
			head = treeUnion(h, prev);
		else
			head = nullptr;
	}

	void insert(const T& data) override 
	{
		Node* newNode = new Node();

		newNode->data = data;
		newNode->pow = 0;

		newNode->parent = nullptr;
		newNode->child = nullptr;
		newNode->sibling = nullptr;

		if (head == nullptr)
			head = newNode;
		else
			head = treeUnion(head,newNode);
	}

	bool isEmpty() const override { return head == nullptr; }

	~TBinomialTree()
	{
		if (head != nullptr)
		{
			std::stack<Node*> nodePtrs;
			Node* current = head;

			while (current != nullptr)
			{
				nodePtrs.push(current);
				current = current->sibling;
			}

			Node* child;
			while (!nodePtrs.empty())
			{
				child = nodePtrs.top()->child;
				delete nodePtrs.top();
				nodePtrs.pop();

				while (child != nullptr)
				{
					nodePtrs.push(child);
					child = child->sibling;
				}
			}
		}
	}
};