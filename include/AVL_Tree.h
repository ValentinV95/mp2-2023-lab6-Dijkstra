#pragma once
#include <iostream>
#include <stack>
#include <iomanip>
#define uchar unsigned char
#include "queue.h"

template <typename N, typename T>
class AVL_Tree :  public priority_queue<N, T> {
private:
	struct Node
	{
		N key;
		T value;
		Node* parent;
		Node* left;
		Node* right;
		uchar height;

		Node(N key, T data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr, uchar dsb = '0')
		{
			this->key = key;
			this->value = data;
			this->parent = parent;
			this->left = left;
			this->right = right;
			this->height = dsb;
			if (parent != nullptr)
				if (key > parent->key)
					parent->right = this;
				else
					parent->left = this;
		}
	};

	Node *root;
	int size;

	/*-------------------------балансировка дерева---------------------------------*/
	int balanceFactor(Node* ptr)
	{
		int hl;
		int hr;
		if (ptr->left == nullptr)
			hl = 0;
		else
			hl = ptr->left->height;

		if (ptr->right == nullptr)
			hr = 0;
		else
			hr = ptr->right->height;

		return (hl - hr);
	}

	void balance(Node* ptr)
	{
		if (balanceFactor(ptr) == 2)
		{
			if (balanceFactor(ptr->left) > 0)
			{
				rotateLeft(ptr->left);
			}
			return rotateRight(ptr);
		}
		else if (balanceFactor(ptr) == -2)
		{
			if (balanceFactor(ptr->right) < 0)
			{
				rotateRight(ptr->right);
			}
			return rotateLeft(ptr);
		}
		else {}
	}

	void fixHeight(Node* ptr)
	{
		uchar h_left;
		uchar h_right;
		h_left = ptr->left ? ptr->left->height : 0;
		h_right = ptr->right ? ptr->right->height : 0;
		if (h_left > h_right)
			ptr->height = h_left + 1;
		else
			ptr->height = h_right + 1;
	}

	void rotateRight(Node* ptr)
	{
		Node* new_root = ptr->left;
		if (ptr->parent == nullptr)
			root = new_root;
		ptr->parent = new_root;
		ptr->left = new_root->right;
		new_root->right = ptr;
		fixHeight(ptr);
		fixHeight(new_root);
	}

	void rotateLeft(Node* ptr)
	{
		Node* new_root = ptr->right;
		if (ptr->parent == nullptr)
			root = new_root;
		ptr->parent = new_root;
		ptr->right = new_root->left;
		new_root->left = ptr;
		fixHeight(ptr);
		fixHeight(new_root);
	}

	void bigRotateRight(Node* ptr)
	{
		rotateRight(ptr->right);
		rotateLeft(ptr);
	}

	void bigRotateLeft(Node* ptr)
	{
		rotateLeft(ptr->left);
		rotateRight(ptr);
	}
	/*--------------------------------------------------------------------------------*/
public:
	/*--------------------обход в глубину-----------------------*/
	class iterator {
	private:
		Node* ptr;
	public:
		iterator() {}

		iterator(Node* p)
		{
			ptr = p;
		}

		iterator& operator++(int) {
			if (ptr->right != nullptr) {
				ptr = ptr->right;
				while (ptr != nullptr && ptr->left != nullptr)
				{
					ptr = ptr->left;
				}
			}
			else {
				Node* tmp = ptr->parent;
				while (tmp != nullptr && ptr == tmp->right) {
					ptr = tmp;
					tmp = tmp->parent;
				}
				ptr = tmp;
			}
			return *this;
		}

		Node* operator*()
		{
			return ptr;
		}

		bool operator==(const Node* second) const
		{
			return ((ptr->key == second->key) && (ptr->value == second->value));
		}

		bool operator!=(const Node* second) const
		{
			return !(ptr == second);
		}

		~iterator() { }
	};

	Node* begin() const
	{
		if (root == nullptr)
			return nullptr;
		Node* a = root;
		if (root == nullptr)
			return a;
		while (a->left != nullptr)
			a = a->left;
		return a;
	}

	Node* end() const
	{
		return nullptr;
	}
	/*----------------------------------------------------------*/

	AVL_Tree()
	{
		root = nullptr;
		size = 0;
	}

	Node* getRoot()
	{
		return root;
	}

	void insert(N key, T data)  //right - max, left - min
	{
		Node* prev = root;
		bool flag_right = true;
		Node *tmp = root;
		if (root == nullptr)
		{
			root = new Node(key, data);
		}
		else
		{
			while (tmp != nullptr)
			{
				if (tmp->left != nullptr || tmp->right != nullptr)
				{
					tmp->height = tmp->height + 1;
				}
				if (key > tmp->key)
				{
					prev = tmp;
					tmp = tmp->right;
				}
				else if (key < tmp->key)
				{
					prev = tmp;
					tmp = tmp->left;
					flag_right = false;
				}
				else
				{
					throw std::exception("ERROR: this name already used");
				}
			}

			tmp = new Node(key, data, prev);

			balance(root);

			if (flag_right)
			{
				prev->right = tmp;
			}
			else
			{
				prev->left = tmp;
			}
		}
		size++;
	}

	Node* AVLSearch(N current_key) //вспомогающая функция
	{
		Node* tmp = root;
		while (tmp != nullptr)
		{
			if (current_key > tmp->key)
			{
				tmp = tmp->right;
			}
			else if (current_key < tmp->key)
			{
				tmp = tmp->left;
			}
			else
				return tmp;
		}
		return nullptr;
	}

	Node* minNode(Node* root_subtree)
	{
		Node* i = root_subtree;
		for (; i->left != nullptr; i = i->left) {}

		return i;
	}

	T getMinimum()
	{
		return minNode(getRoot())->value;
	}

	void Extract(N current_key)
	{
		Node* curr_ptr = AVLSearch(current_key);
		if (curr_ptr != nullptr)
		{
			Node* p = curr_ptr->parent;
			if (curr_ptr->left == nullptr && curr_ptr->right == nullptr)
			{
				if (curr_ptr == root)
					root = nullptr;

				delete curr_ptr;
			}
			else if (curr_ptr->left == nullptr || curr_ptr->right == nullptr)
			{
				Node* p = curr_ptr->parent;
				Node* child;
				child = curr_ptr->left;
				if (curr_ptr->left == nullptr)
					child = curr_ptr->right;
				if (p != nullptr && child->key > p->key)
				{
					p->right = child;
					child->parent = p;
				}
				else if (p != nullptr && child->key < p->key)
				{
					p->left = child;
					child->parent = p;
				}
				else
				{
					root = child;
					root->parent = nullptr;
				}

				/*if (curr_ptr == root)
					root = nullptr;*/

				delete curr_ptr;
			}
			else
			{
				Node* p = curr_ptr->parent;
				Node* child_r = curr_ptr->right;
				Node* child_l = curr_ptr->left;
				Node* minimum = minNode(child_r);
				if (p != nullptr && minimum->key > p->key)
					p->right = minimum;
				else if (p != nullptr && minimum->key < p->key)
					p->left = minimum;
				else
				{
					root = minimum;
				}
				minimum->parent = p;
				minimum->left = child_l;
				minimum->right = child_r;
				if (curr_ptr == nullptr)
					root = nullptr;

				delete curr_ptr;
			}
			
			for (Node* tmp = p; p != nullptr && tmp != nullptr; tmp = tmp->parent)
			{
				fixHeight(p);
			}

			if (p != nullptr)
				balance(p);
		}
		else
		{

		}
	}

	void extractMin()
	{
		Extract(minNode(getRoot())->key);
	}

	void show()
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << std::setw(20) << std::left << "| NAME" << "| POLINOM" << std::endl;
		for (iterator it = begin(); it != end(); it++)
		{
			show(*it);
		}
	}

	void show(Node* t)
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << std::setw(20) << std::left << "| " + t->key;
		std::cout << "| ";
		t->value.show();
		std::cout << '\n';
		std::cout << std::string(60, '-') << std::endl;
	}

	~AVL_Tree()
	{
		for (iterator it = begin(); it != end(); )
		{
			if ((*it)->left == nullptr && (*it)->right == nullptr)
			{
				Node* tmp = (*it);
				it++;
				delete tmp;
			}
			else
			{
				it++;
			}
		}
	}
};