#pragma once

#include"PriorityQueue.h"

#include<string>
#include<stack>

using namespace std;

enum Colors{RED, BLACK};

template<class T>
class TRBTree: public PriorityQueue<T>
{
	struct Node
	{
		Node* parent;
		Node* rChild;
		Node* lChild;
		T data;
		Colors color;
	};

	Node* root;

	Node* null;

	Node* grandparent(Node* node)
	{
		if ((node != null) && (node->parent != null)) 
		{
			return node->parent->parent;
		}
		else 
		{
			return null;
		}
	}

	Node* uncle(Node* node)
	{
		Node* gp = grandparent(node);
		if (gp == null) 
		{
			return null;
		}
		if (node->parent == gp->lChild) 
		{
			return gp->rChild;
		}
		else 
		{
			return gp->lChild;
		}
	}

	Node* sibling(Node* node)
	{
		if (node == node->parent->lChild)
		{
			return node->parent->rChild;
		}
		else 
		{
			return node->parent->lChild;
		}
	}

	void replaceNode(Node* node, Node* child) 
	{
		child->parent = node->parent;
		if (node == node->parent->lChild) 
		{
			node->parent->lChild = child;
		}
		else 
		{
			node->parent->rChild = child;
		}
	}
	
	bool isLeaf(Node* node)
	{
		if(node == null)
		{
			return true;
		}
		return false;
	}

	void deleteTwoChild(Node* node)
	{
		Node* max = node->lChild;
		while (max->rChild != null)
		{
			max = max->rChild;
		}
		node->data = max->data;
		deleteOneChild(max);
	}

	void deleteOneChild(Node* node)
	{
		Node* child = isLeaf(node->rChild) ? node->lChild : node->rChild;

		replaceNode(node, child);
		if(node == root)
		{
			root = child;
		}
		if (node->color == BLACK) {
			if (child->color == RED)
				child->color = BLACK;
			else
				deleteCase1(child);
		}
		delete node;
	}

	void deleteCase1(Node* node)
	{
		if (node->parent != null)
		{
			deleteCase2(node);
		}
	}

	void deleteCase2(Node* node)
	{
		Node* sib = sibling(node);

		if (sib->color == RED) 
		{
			node->parent->color = RED;
			sib->color = BLACK;
			if (node == node->parent->lChild)
			{
				rotateLeft(node->parent);
			}
			else 
			{
				rotateRight(node->parent);
			}
		}
		deleteCase3(node);
	}

	void deleteCase3(Node* node)
	{
		Node* sib = sibling(node);
		if (
			(node->parent->color == BLACK) &&
			(sib->color == BLACK) &&
			(sib->lChild->color == BLACK) &&
			(sib->rChild->color == BLACK)
			)
		{
			sib->color = RED;
			deleteCase1(node->parent);
		}
		else
		{
			deleteCase4(node);
		}
	}

	void deleteCase4(Node* node)
	{
		Node* sib = sibling(node);

		if (
			(node->parent->color == RED) &&	
			(sib->color == BLACK) &&
			(sib->lChild->color == BLACK) &&
			(sib->rChild->color == BLACK)
			)
		{
			sib->color = RED;
			node->parent->color = BLACK;
		}
		else
		{
			deleteCase5(node);
		}
	}

	void deleteCase5(Node* node)
	{
		Node* sib = sibling(node);

		if (sib->color == BLACK) 
		{ 
			if (
				(node == node->parent->lChild) &&
				(sib->rChild->color == BLACK) &&
				(sib->lChild->color == RED)
				)
			{
				sib->color = RED;
				sib->lChild->color = BLACK;
				rotateRight(sib);
			}
			else if (
				(node == node->parent->rChild) &&
				(sib->lChild->color == BLACK) &&
				(sib->rChild->color == RED)
				)
			{
				sib->color = RED;
				sib->rChild->color = BLACK;
				rotateLeft(sib);
			}
		}
		deleteCase6(node);
	}

	void deleteCase6(Node* node)
	{
		Node* sib = sibling(node);

		sib->color = node->parent->color;
		node->parent->color = BLACK;

		if (node == node->parent->lChild) 
		{
			sib->rChild->color = BLACK;
			rotateLeft(node->parent);
		}
		else 
		{
			sib->lChild->color = BLACK;
			rotateRight(node->parent);
		}
	}

	void rotateLeft(Node* node)
	{
		Node* pivot = node->rChild;

		pivot->parent = node->parent;
		if (node->parent != null) {
			if (node->parent->lChild == node)
			{
				node->parent->lChild = pivot;
			}
			else
			{
				node->parent->rChild = pivot;
			}
		}

		node->rChild = pivot->lChild;
		if (pivot->lChild != null)
		{
			pivot->lChild->parent = node;
		}
		if(node == root)
		{
			root = pivot;
		}
		node->parent = pivot;
		pivot->lChild = node;
	}

	void rotateRight(Node* node)
	{
		Node* pivot = node->lChild;

		pivot->parent = node->parent; 
		if (node->parent != null) 
		{
			if (node->parent->lChild == node)
			{
				node->parent->lChild = pivot;
			}
			else
			{
				node->parent->rChild = pivot;
			}
		}
		node->lChild = pivot->rChild;
		if (pivot->rChild != null)
		{
			pivot->rChild->parent = node;
		}
		node->parent = pivot;
		pivot->rChild = node;
	}

	void insertLeaf(Node* node)
	{
		if(root == null) 
		{
			root = node;
			return;
		}
		Node* prev = null;
		Node* cur = root;
		while (cur!= null)
		{
			prev = cur;
			if(node->data > cur->data)
			{
				cur = cur->rChild;
			}
			else
			{
				cur = cur->lChild;
			}
		}
		if (node->data > prev->data)
		{
			prev->rChild = node;
		}
		else
		{
			prev->lChild = node;
		}
		node->parent = prev;
	}
	
	void insertCase1(Node* node)
	{
		if (node->parent == null)
		{
			node->color = BLACK;
		}
		else 
		{
			insertCase2(node);
		}
	}

	void insertCase2(Node* node)
	{
		if (node->parent->color == BLACK)
		{
			return;
		}
		else 
		{
			insertCase3(node);
		}
	}

	void insertCase3(Node* node)
	{
		Node* un = uncle(node);

		if ((un != null) && (un->color == RED)) 
		{
			node->parent->color = BLACK;
			un->color = BLACK;
			Node* gp = grandparent(node);
			gp->color = RED;
			insertCase1(gp);
		}
		else 
		{
			insertCase4(node);
		}
	}

	void insertCase4(Node* node)
	{
		Node* gp = grandparent(node);

		if ((node == node->parent->rChild) && (node->parent == gp->lChild)) 
		{
			rotateLeft(node->parent);
			node = node->lChild;

		}
		else if ((node == node->parent->lChild) && (node->parent == gp->rChild))
		{
			rotateRight(node->parent);
			node = node->rChild;
		}
		insertCase5(node);
	}

	void insertCase5(Node* node)
	{
		Node* gp = grandparent(node);

		node->parent->color = BLACK;
		gp->color = RED;
		if ((node == node->parent->lChild) && (node->parent == gp->lChild)) 
		{
			rotateRight(gp);
		}
		else 
		{
			rotateLeft(gp);
		}
	}
public:
	TRBTree()
	{
		null = new Node{ nullptr, nullptr, nullptr, T(), BLACK };
		root = null;
	}

	~TRBTree()
	{
		if(root == null)
		{
			delete null;
			return;
		}
		stack<Node*> st;
		st.push(root);
		while (!st.empty())
		{
			Node* top = st.top();
			st.pop();
			if (top->rChild != null)
			{
				st.push(top->rChild);
			}
			if (top->lChild != null)
			{
				st.push(top->lChild);
			}
			delete top;
		}
		delete null;
	}

	const T& search(const T& data)
	{
		Node* cur = root;
		while(cur != null)
		{
			if(data == cur->data)
			{
				return cur->data;
			}
			else if(data > cur->data)
			{
				cur = cur->rChild;
			}
			else
			{
				cur = cur->lChild;
			}
		}
		throw exception("Not found!!!");
	}

	void erase(T data)
	{
		Node* cur = root;
		while (cur != null)
		{
			if (data == cur->data)
			{
				if(cur->lChild != null && cur->rChild != null)
				{
					deleteTwoChild(cur);
				}
				else
				{
					deleteOneChild(cur);
				}
				return;
			}
			else if (data > cur->data)
			{
				cur = cur->rChild;
			}
			else
			{
				cur = cur->lChild;
			}
		}
		throw exception("Element not found!");
	}

	void insert(const T& elem) override 
	{
		Node* cur = new Node{ null, null ,null, elem, RED };
		insertLeaf(cur);
		insertCase1(cur);
	}

	const T& getMin() const override  
	{
		Node* cur = root;
		while(cur->lChild != null)
		{
			cur = cur->lChild;
		}
		return cur->data;
	}

	void extractMin() override  
	{
		Node* cur = root;
		while (cur->lChild != null)
		{
			cur = cur->lChild;
		}
		deleteOneChild(cur);
	}
};

