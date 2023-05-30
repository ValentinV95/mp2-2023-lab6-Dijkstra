#pragma once

#include <iostream>

enum TreeColor
{
	black = 0,
	red = 1
};

template<class T>
struct RBNode
{
	unsigned char tcolor;                                  // 0 - black, 1 - red
	T data;                                                // Данные 
	RBNode* left;                                          // Указатель на левого потомка
	RBNode* right;                                         // Указатель на правого потомка
	RBNode* parent;                                        // Указатель на родителя

	RBNode() : tcolor(red), data(T()), left(nullptr), right(nullptr), parent(nullptr)
	{}

	RBNode(const T& var) : tcolor(red), data(var), left(nullptr), right(nullptr), parent(nullptr)
	{}

	RBNode<T>* maxLeft()                                   // Максимальный левый потомок
	{
		RBNode<T>* temp = this->left;

		while (temp->right)
		{
			temp = temp->right;
		}

		return temp;
	}

	RBNode<T>* minRight()                                  // Минимальный правый потомок
	{
		RBNode<T>* temp = this->right;

		while (temp->left)
		{
			temp = temp->left;
		}


		return temp;
	}

	RBNode<T>* maxRight()                                   // Максимальный правый потомок
	{
		RBNode<T>* temp = this->right;

		while (temp->right)
		{
			temp = temp->right;
		}

		return temp;
	}

	RBNode<T>* minLeft()                                  // Минимальный левый потомок
	{
		RBNode<T>* temp = this->left;

		while (temp->left)
		{
			temp = temp->left;
		}


		return temp;
	}

};

template<class T>
class Tree
{
private:
	RBNode<T>* root;                                       // Указатель на корень
	int tsize;                                             // Количество узлов в данный момент

	void swapData(RBNode<T>*, RBNode<T>*);                 // Обмен данными
	void swapColor(RBNode<T>*, RBNode<T>*);                // Обмен цветами
	void rightRotate(RBNode<T>*);                          // Правое вращение
	void leftRotate(RBNode<T>*);                           // Левое вращение
	void balancePush(RBNode<T>*);                          // Балансировка вставки
	void balanceDelete(RBNode<T>*);                        // Балансировка удаления
	void DFS(RBNode<T>*) const;                            // Поиск в глубину

public:
	Tree();                                                // Конструктор по умолчанию
	Tree(const T&);                                        // Конструктор инициализации корня
	~Tree();                                               // Деструктор
	RBNode<T>* search(const T&) const;                     // Поиск
	void push(const T&);                                   // Вставка
	void deleteNode(RBNode<T>*);                           // Удаление узла
	RBNode<T>* begin() const;                              // Получение корня
	bool isEmpty() const;                                  // Проверка пустоты дерева
	int size() const;                                      // Получение количества узлов в данный момент
	void clear();                                          // Удаление всех узлов в дереве
	void getTree() const;                                  // Функция вызова поиска в глубину
	RBNode<T>* getMin();                                   // Минимальный элемент
	void extractMin();                                     // Удаление минимального
};

template<class T>
void Tree<T>::swapData(RBNode<T>* one, RBNode<T>* other)
{
	T temp = one->data;
	one->data = other->data;
	other->data = temp;
}

template<class T>
void Tree<T>::swapColor(RBNode<T>* one, RBNode<T>* other)
{
	unsigned char temp = one->tcolor;
	one->tcolor = other->tcolor;
	other->tcolor = temp;
}

template<class T>
void Tree<T>::rightRotate(RBNode<T>* cur)
{
	RBNode<T>* temp = cur->left;
	temp->parent = cur->parent;

	if (cur == this->root)
	{
		this->root = temp;
	}

	else
	{
		if (cur == cur->parent->left) cur->parent->left = temp;
		else cur->parent->right = temp;
	}

	cur->parent = temp;
	cur->left = temp->right;
	if (temp->right) temp->right->parent = cur;
	temp->right = cur;
}

template<class T>
void Tree<T>::leftRotate(RBNode<T>* cur)
{
	RBNode<T>* temp = cur->right;
	temp->parent = cur->parent;

	if (cur == this->root)
	{
		this->root = temp;
	}

	else
	{
		if (cur == cur->parent->left) cur->parent->left = temp;
		else cur->parent->right = temp;
	}

	cur->parent = temp;
	cur->right = temp->left;
	if (temp->left) temp->left->parent = cur;
	temp->left = cur;
}

template<class T>
void Tree<T>::balancePush(RBNode<T>* cur)
{
	if (cur->parent == nullptr)                                             // Вставка корня
	{
		this->root->tcolor = black;
		return;
	}

	if (cur->parent->tcolor == red)                                         // Отец вставляемого узла красный
	{
		RBNode<T>* father = cur->parent;
		RBNode<T>* grandpa = father->parent;
		RBNode<T>* uncle = father->data > grandpa->data ? grandpa->left : grandpa->right;
		RBNode<T>* temp = cur;

		if (uncle && uncle->tcolor == red)                                  // Дядя вставляемого узла красный
		{
			father->tcolor = black;
			uncle->tcolor = black;
			grandpa->tcolor = red;
			balancePush(grandpa);
		}

		else                                                               // Дядя вставляемого узла черный(или его нет)
		{
			if (father == grandpa->left && cur == father->right)           // Отец левый сын дедушки и вставляемый узел правый сын
			{
				leftRotate(father);
				temp = father;
				father = cur;
			}

			if (father == grandpa->right && cur == father->left)           // Отец правый сын дедушки и вставляемый узел левый сын
			{
				rightRotate(father);
				temp = father;
				father = cur;
			}

			father->tcolor = black;
			grandpa->tcolor = red;

			if (grandpa->left == father) rightRotate(grandpa);             // Отец вставляемого узла левый сын дедушки
			else leftRotate(grandpa);                                      // Отец вставляемого узла правый сын дедушки
		}
	}
}

template<class T>
void Tree<T>::balanceDelete(RBNode<T>* cur)
{
	RBNode<T>* father = cur->parent;
	RBNode<T>* brother;
	RBNode<T>* nephewleft;
	RBNode<T>* nephewright;

	if (cur->tcolor == red) return;                        // Если удаляемый узел - красный, то просто удаляем его

	if (!father)                                           // Если удаляемый узел - корень, то красим в черный
	{
		cur->tcolor = black;
		return;
	}

	brother = father->right == cur ? father->left : father->right;	
	nephewleft = brother->left;
	nephewright = brother->right;

	if (brother->tcolor == red)                            // Брат удаляемого узла - красный
	{
		swapColor(father, brother);

		if (father->left == cur) leftRotate(father);       // Удаляемый узел - левый сын
		else rightRotate(father);                          // Удаляемый узел - правый сын

		balanceDelete(cur);
	}

	else                                                   // Брат удаляемого узла - черный
	{
		if ((!nephewleft || nephewleft->tcolor == black) &&  // Дети брата - черные или их нет
			(!nephewright || nephewright->tcolor == black))
		{
			if (father->tcolor == red)                     // Отец красный
			{
				swapColor(father, brother);
			}

			else                                           // Отец черный
			{
				brother->tcolor = red;
				balanceDelete(father);
			}
		}

		else                                               // Есть хоть один красный сын у брата
		{
			if (father->left == cur)                       // Удаляемый узел - левый сын
			{
				if (nephewleft && nephewleft->tcolor == red) // Левый сын брата - красный
				{
					swapColor(brother, nephewleft);
					rightRotate(brother);
					balanceDelete(cur);
				}

				else                                       // Правый сын брата - черный
				{
					swapColor(brother, father);
					nephewright->tcolor = black;
					leftRotate(father);
				}
			}

			else                                           // Удаляемый узел - правый сын
			{
				if (nephewleft && nephewleft->tcolor == red) // Левый сын брата - красный
				{
					swapColor(brother, father);
					nephewleft->tcolor = black;
					rightRotate(father);
				}

				else                                       // Правый сын брата - красный
				{
					swapColor(brother, nephewright);
					leftRotate(brother);
					balanceDelete(cur);
				}
			}
		}
	}
}

template<class T>
Tree<T>::Tree() : root(nullptr), tsize(0)
{}

template<class T>
Tree<T>::Tree(const T& var) : root(new RBNode<T>(var)), tsize(1)
{
	this->root->tcolor = black;
}

template<class T>
Tree<T>::~Tree()
{
	this->clear();
	this->root = nullptr;
}

template<class T>
RBNode<T>* Tree<T>::search(const T& var) const
{
	RBNode<T>* temp = this->root;

	while (temp)
	{
		if (temp->data > var) temp = temp->left;
		else if (temp->data < var) temp = temp->right;
		else return temp;
	}

	return nullptr;
}

template<class T>
void Tree<T>::push(const T& var)
{
	RBNode<T>* cur = new RBNode<T>(var);

	if (this->isEmpty())                                      // Вставка корня
	{
		this->root = cur;
	}

	else                                                      // Вставка не корня
	{
		RBNode<T>* fast = this->root;
		RBNode<T>* slow = nullptr;

		while (fast)
		{
			slow = fast;

			if (var == fast->data) return;

			else if (var > fast->data)
			{
				if (fast->right)
				{
					fast = fast->right;
				}

				else
				{
					slow->right = cur;
					cur->parent = slow;
					break;
				}

			}

			else
			{
				if (fast->left)
				{
					fast = fast->left;
				}

				else
				{
					slow->left = cur;
					cur->parent = slow;
					break;
				}
			}
		}
	}

	balancePush(cur);
	this->tsize++;
}

template<class T>
void Tree<T>::deleteNode(RBNode<T>* cur)
{
	if (cur)
	{
		RBNode<T>* temp;
		RBNode<T>* father = cur->parent;

		if (!cur->left && !cur->right)
		{
			if (!father) this->root = nullptr;
			else
			{
				balanceDelete(cur);
				father->left == cur ? father->left = nullptr : father->right = nullptr;
			}

			delete cur;
			cur = nullptr;
			tsize--;
		}

		else
		{
			if (cur->left && cur->right) temp = cur->minRight();
			else cur->left ? temp = cur->left : temp = cur->right;
			swapData(temp, cur);
			deleteNode(temp);
		}
	}
}

template<class T>
RBNode<T>* Tree<T>::begin() const
{
	return this->root;
}

template<class T>
bool Tree<T>::isEmpty() const
{
	return this->root == nullptr;
}

template<class T>
int Tree<T>::size() const
{
	return  this->tsize;
}

template<class T>
void Tree<T>::clear()
{
	while (this->tsize)
	{
		this->deleteNode(this->root);
	}
}

template<class T>
void Tree<T>::getTree() const
{
	if (!isEmpty())
	{
		DFS(this->root);
	}

	std::cout << std::endl;
}

template<class T>
RBNode<T>* Tree<T>::getMin()
{
	if (isEmpty()) return nullptr;
	return this->root->minLeft();
}

template<class T>
void Tree<T>::extractMin()
{
	if (!isEmpty())
	{
		deleteNode(this->root->minLeft());
	}
}