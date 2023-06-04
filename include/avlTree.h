#pragma once
#include <iostream>

template <class T1, class T>
class avlTree
{
private:
	struct Node
	{
		T1 key;
		T data;
		int height;

		Node* left;
		Node* right;
		Node(T1 key,T value, int height = 0)
		{
			this->key = key;
			data = value;
			this->height = height;
			left = nullptr;
			right = nullptr;
		}
	};

	int size = 0;

	struct Log
	{
		std::string name;
		int operation = 0;
		Log() { name = "no operations"; operation = 0; };
	} loger;

	Node* root = nullptr;




	void delNode(T1 elem, Node* node, Node* last)
	{
		Node* delElem;
		loger.operation++;
		if (node == nullptr)
			throw std::exception("no such elem");
		else if (last == node && elem < node->key)
		{
			loger.operation++;
			delNode(elem, node->left, last);
		}
		else if (last == node && elem > node->key)
		{
			loger.operation += 2;
			delNode(elem, node->right, last);
		}
		else if (elem < node->key)
		{
			loger.operation += 3;
			delNode(elem, node->left, node);
		}
		else if (elem > node->key)
		{
			loger.operation += 4;
			delNode(elem, node->right, node);
		}
		else if (node->left != nullptr && elem == node->left->key)
		{
			loger.operation += 3;
			delNode(elem, node->left, node);
		}
		else if (node->right != nullptr && elem == node->right->key)
		{
			loger.operation += 4;
			delNode(elem, node->right, node);
		}
		else if ((node->left == nullptr) && (node->right == nullptr))
		{
			loger.operation += 6;
			
			if (node == root)
			{
				delete node;
				root = nullptr;
			}
			else if(last->left == node)
			{
				loger.operation++;
				last->left = nullptr;
				delete node;
			}
			else
			{
				loger.operation++;
				last->right = nullptr;
				delete node;
			}
			node = nullptr;

		}
		else if (node->left == nullptr)
		{
			loger.operation += 6;
			if (node == root)
			{
				root = node->right;
				delete node;
			}
			else if (last->left == node)
			{
				loger.operation++;
				last->left = node->right;
				delete node;
			}
			else
			{
				loger.operation++;
				last->right = node->right;
				delete node;
			}
			node = nullptr;
		}
		else if (node->right == nullptr)
		{
			loger.operation += 6;
			if (node == root)
			{
				loger.operation++;
				root = node->left;
				delete node;
			}
			else if (last->left == node)
			{
				loger.operation++;
				last->left = node->left;
				delete node;
			}
			else
			{
				loger.operation++;
				last->right = node->left;
				delete node;
			}
			node = nullptr;
		}
		else
		{
			loger.operation += 6;

			delElem = getMin(node->right);
			node->key = delElem->key;
			node->data = delElem->data;
			if(node != last)
				delNode(delElem->key, node->right, last->right);
			else
				delNode(delElem->key, node->right, last);
		}

		loger.operation++;
		if (node != nullptr)
		{
			updateHeight(node);
			balnce(node);
		}
		return;
	}


	void swap(Node* node_1, Node* node_2)
	{
		T tmp_data = node_1->data;
		node_1->data = node_2->data;
		node_2->data = tmp_data;
		T1 tmp_key = node_1->key;
		node_1->key = node_2->key;
		node_2->key = tmp_key;
	}

	Node* getMin(Node* node)
	{
		loger.operation++;
		if (node == nullptr)
			return nullptr;

		loger.operation++;
		if (node->left == nullptr)
			return node;
		return getMin(node->left);
	}

	Node* getMax(Node* node)
	{
		loger.operation++;
		if (node == nullptr)
			return nullptr;

		loger.operation++;
		if (node->right == nullptr)
			return node;
		return getMax(node->right);
	}

	void updateHeight(Node* node)
	{
		loger.operation++;
		if (getHeight(node->right) > getHeight(node->left))
			node->height = getHeight(node->right) + 1;
		else
			node->height = getHeight(node->left) + 1;
	}

	void delAll(Node* node)
	{
		if (node == nullptr)
			return;
		delAll(node->left);
		delAll(node->right);
		delete node;
	}

	int getHeight(Node* node)
	{
		loger.operation++;
		if (node == nullptr)
			return -1;
		return node->height;
	}

	void balnce(Node* node)
	{
		loger.operation++;
		int balance = getBalance(node);
		if (balance == -2)
		{
			loger.operation++;
			if (getBalance(node->left) == 1)
				leftRotate(node->left);
			rightRotate(node);
		}
		else if (balance == 2)
		{
			loger.operation+=2;
			if (getBalance(node->right) == -1)
				rightRotate(node->right);
			leftRotate(node);
		}

	}

	void insert(Node* node, T1 key, T value)
	{
		loger.operation++;
		if (root == nullptr)
		{
			Node* elem = new Node(key, value);
			root = elem; node = root;
		}
		else if (node->key > key)
		{
			loger.operation += 2;
			if (node->left == nullptr)
			{
				Node* elem = new Node(key, value);
				node->left = elem;
			}
			else
				insert(node->left, key, value);
		}
		else if (node->key <= key)
		{
			loger.operation += 3;
			if (node->right == nullptr)
			{
				Node* elem = new Node(key, value);
				node->right = elem;
			}
			else
				insert(node->right, key, value);
		}



		updateHeight(node);
		balnce(node);
	}

	Node* findNode(Node* node, T1 key)
	{
		loger.operation += 2;
		if (node == nullptr) throw std::exception("no such element");
		if (node->key > key)
			findNode(node->left, key);
		else if (node->key < key)
		{
			loger.operation++;
			findNode(node->right, key);
		}
		else
		{
			loger.operation++;
			return node;
		}
	}

	
	void L_R(Node* node)
	{
		if (node == nullptr)
			return;
		L_R(node->left);
		std::cout << node->key << "  " << node->data << "\n";
		L_R(node->right);
	}


	void L_R_keys(Node* node)
	{
		if (node == nullptr)
			return;
		L_R_keys(node->left);
		std::cout << node->key << "\n";
		L_R_keys(node->right);
	}

	int getBalance(Node* node)
	{
		loger.operation++;
		if (node == nullptr)
			return 0;
		return getHeight(node->right) - getHeight(node->left);
	}

	void rightRotate(Node* node)
	{
		swap(node, node->left);
		Node* tmp_R = node->right;
		node->right = node->left;
		node->left = node->right->left;
		node->right->left = node->right->right;
		node->right->right = tmp_R;
		updateHeight(node->right);
		updateHeight(node);
	}

	void leftRotate(Node* node)
	{
		swap(node, node->right);
		Node* tmp_R = node->left;
		node->left = node->right;
		node->right = node->left->right;
		node->left->right = node->left->left;
		node->left->left = tmp_R;
		updateHeight(node->left);
		updateHeight(node);
	}

public:
	avlTree(T1 key, T value)
	{
		root = new Node(key, value);
	}

	avlTree()
	{
		root = nullptr;
	}

	~avlTree()
	{
		delAll(root);
	}


	void L_R_print()
	{
		L_R(root);
		std::cout << '\n';
	}

	void L_R_keys()
	{
		L_R_keys(root);
		std::cout << '\n';
	}

	T getMin()
	{
		Node* n = getMin(root);
		if (n == nullptr)
			throw std::exception("avlTree is empty!");
		T1 key = n->key;
		T data = n->data;
		delNode(key, root, root);
		size--;
		return data;
	}

	void insert(T1 key, T elem)
	{
		loger.name = "insert";
		loger.operation = 0;

		insert(root, key, elem);
		size++;
	}

	void delElem(T1 key)
	{
		loger.name = "delete";
		loger.operation = 0;

		delNode(key, root, root);
		size--;
	}

	T& getElement(T1 key)
	{
		loger.name = "search";
		loger.operation = 0;

		Node* find = root;
		find = findNode(root, key);
		return find->data;
	}

	void getLog()
	{
		std::cout << loger.name << " : " << loger.operation << "\n";
	}

	bool isEmpty()
	{
		//std::cout << size;
		return size == 0;
	}
};