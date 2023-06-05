#pragma once

#include "queue.h"

template <class P, class T>
class BinomialHeapQueue : public PriorityQueue<P, T>
{
private:
	struct Node
	{
		P priority;
		T data;
		size_t degree;
		Node* parent;
		Node* child;
		Node* sibling;
	};
	Node* head;
	Node* prev_minimum;
	Node* minimum;

	void update_minimum()
	{
		Node* cur_previous = nullptr;
		Node* current_min = head;
		if (minimum == nullptr) minimum = head;
		while (current_min != nullptr)
		{
			if (current_min->priority <= minimum->priority)
			{
				prev_minimum = cur_previous;
				minimum = current_min;
			}
			cur_previous = current_min;
			current_min = current_min->sibling;
		}
	}
	void merge(BinomialHeapQueue<P, T>& other)
	{
		// merge root lists
		if (other.head == nullptr)
		{
			return;
		}
		if (head == nullptr)
		{
			head = other.head;
			return;
		}
		Node* final_head = nullptr;
		Node* current = final_head;
		Node* this_current = head;
		Node* other_current = other.head;
		while (this_current != nullptr && other_current != nullptr)
		{
			if (this_current->degree <= other_current->degree)
			{
				if (final_head == nullptr)
				{
					final_head = this_current;
					current = final_head;
				}
				else
				{
					current->sibling = this_current;
					current = current->sibling;
				}
				this_current = this_current->sibling;
			}
			else
			{
				if (final_head == nullptr)
				{
					final_head = other_current;
					current = final_head;
				}
				else
				{
					current->sibling = other_current;
					current = current->sibling;
				}
				other_current = other_current->sibling;
			}
		}
		while (this_current != nullptr)
		{
			current->sibling = this_current;
			current = current->sibling;
			this_current = this_current->sibling;
		}
		while (other_current != nullptr)
		{
			current->sibling = other_current;
			current = current->sibling;
			other_current = other_current->sibling;
		}
		head = final_head;

		// restore binomial heap properties
		Node* previous = nullptr;
		current = head;
		Node* next = current->sibling;
		while (next != nullptr)
		{
			if (current->degree != next->degree || (next->sibling != nullptr && next->sibling->degree == current->degree))
			{
				previous = current;
				current = next;
				next = current->sibling;
			}
			else if (current->priority <= next->priority)
			{
				current->sibling = next->sibling;
				next->parent = current;
				next->sibling = current->child;
				current->child = next;
				current->degree++;
			}
			else
			{
				if (previous == nullptr)
				{
					head = next;
				}
				else
				{
					previous->sibling = next;
				}
				current->parent = next;
				current->sibling = next->child;
				next->child = current;
				next->degree++;
				current = next;
			}
			next = current->sibling;
		}
	}
public:
	BinomialHeapQueue() : head(nullptr), minimum(nullptr), prev_minimum(nullptr) {}

	void insert(const P& _priority, const T& _data) override
	{
		BinomialHeapQueue<P, T> inserted;
		Node* inserted_node = new Node{ _priority, _data, 0, nullptr, nullptr, nullptr };
		inserted.head = inserted_node;
		merge(inserted);
		update_minimum();
	}
	const T& get_min() const override
	{
		if (minimum == nullptr)
		{
			throw std::exception("Queue is empty");
		}
		return minimum->data;
	}
	void extract_min() override
	{
		if (minimum == nullptr)
		{
			throw std::exception("Queue is empty");
		}

		// break the connection with the minimum
		if (prev_minimum != nullptr)
		{
			prev_minimum->sibling = minimum->sibling;
		}
		else head = minimum->sibling;

		// reverse the list of minimum children
		Node* child = minimum->child;
		Node* previous = nullptr;
		while (child != nullptr)
		{
			Node* sibling = child->sibling;
			child->sibling = previous;
			previous = child;
			child = sibling;
		}
		BinomialHeapQueue<P, T> reunited;
		reunited.head = previous;

		delete minimum;
		minimum = nullptr;
		merge(reunited);
		update_minimum();
	}

	~BinomialHeapQueue()
	{
		while (minimum != nullptr)
		{
			extract_min();
		}
	}
};