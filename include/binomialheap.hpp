#pragma once
#include <cmath>
#include <queue>

template <class T>
struct HNode
{
	T data;                                      // Данные
	HNode* parent;                               // Указатель на родителя
	HNode* lchild;                               // Указатель на левого ребенка
	HNode* sibling;                              // Указатель на правого брата
	int degree;                                  // Степень вершины

	HNode() : data(T()),                         // Конструктор по умолчанию 
		      parent(nullptr),
		      lchild(nullptr),
		      sibling(nullptr),
		      degree(0) 
	{}

	HNode(const T& var) : data(var),             // Конструктор инициализации
		                  parent(nullptr), 
		                  lchild(nullptr),
		                  sibling(nullptr),
		                  degree(0) 
	{}

};

template <class T>
class BinHeap
{
private:
	HNode<T>* head;                              // Указатель на фиктивную голову

	HNode<T>* mergeNode(HNode<T>*, HNode<T>*);   // Слияние двух вершин
	void mergeHeap(BinHeap& other);              // Слияние двух куч
	void unionHeap(BinHeap& other);              // Объединение 2 куч в 1

public:
	BinHeap();                                   // Конструктор по умолчанию
	BinHeap(const T&);                           // Конструктор инициализации корня
	~BinHeap();                                  // Деструктор
	int size();                                  // Получить количество элементов
	bool isEmpty();                              // Проверка на пустоту
	T getMin();                                  // Получить минимум
	void extractMin();                           // Удалить минимум
	void insert(const T&);                       // Вставка
	void clear();                                // Очистка кучи

	friend std::istream& operator >>(std::istream& istr, BinHeap& bheap)
	{
		T buffer;

		while (istr >> buffer)
		{
			bheap.insert(buffer);
		}

		return istr;
	}

	friend std::ostream& operator <<(std::ostream& ostr, const BinHeap& bheap)
	{
		HNode<T>* temp = bheap.head->sibling;
		HNode<T>* ptr;
		HNode<T>* ptr2;
		std::queue<HNode<T>*> queue;

		while (temp)
		{
			ostr << temp->data << " ";

			if (temp->lchild)
			{
				queue.push(temp->lchild);
				ptr = temp->lchild->sibling;

				while (!queue.empty())
				{
					while (ptr)
					{
						queue.push(ptr);
						ptr = ptr->sibling;
					}

					ptr2 = queue.front();
					queue.pop();

					if (ptr2->lchild)
					{
						ptr = ptr2->lchild->sibling;
						queue.push(ptr2->lchild);
					}

					ostr << ptr2->data << " ";
				}
			}

			ostr << "  ";

			temp = temp->sibling;
		}

		return ostr;
	}

};

template<class T>
HNode<T>* BinHeap<T>::mergeNode(HNode<T>* one, HNode<T>* other)
{
	if (one == nullptr) return other;
	if (other == nullptr) return one;

	HNode<T>* minNode;
	HNode<T>* maxNode;

	if (one->data > other->data)
	{
		minNode = other;
		maxNode = one;
	}

	else
	{
		minNode = one;
		maxNode = other;
	}

	maxNode->sibling = minNode->lchild;
	maxNode->parent = minNode;
	minNode->lchild = maxNode;
	minNode->degree++;
	one = nullptr;
	other = nullptr;

	return minNode;
}

template<class T>
void BinHeap<T>::mergeHeap(BinHeap<T>& other)
{
	if (other.isEmpty()) return;

	HNode<T>* slow = this->head;
	HNode<T>* ptr1 = this->head->sibling;
	HNode<T>* ptr2 = other.head->sibling;
	HNode<T>* temp;

	while (ptr2)
	{
		if (ptr1 && ptr2)
		{
			if (ptr1->degree > ptr2->degree)
			{
				slow->sibling = ptr2;
				temp = ptr2->sibling;
				ptr2->sibling = ptr1;
				ptr2 = temp;
			}

			slow = ptr1;
			ptr1 = ptr1->sibling;

		}

		else
		{
			while (ptr2)
			{
				slow->sibling = ptr2;
				slow = ptr2;
				ptr2 = ptr2->sibling;
			}
		}
	}

	other.head->sibling = nullptr;
}

template<class T>
void BinHeap<T>::unionHeap(BinHeap<T>& other)
{
	mergeHeap(other);

	if (!isEmpty())
	{
		HNode<T>* fast;
		HNode<T>* slow = this->head;
		HNode<T>* ptr1 = this->head->sibling;

		while (ptr1->sibling)
		{
			if (ptr1->degree == ptr1->sibling->degree)
			{
				fast = ptr1->sibling->sibling;
				ptr1 = mergeNode(ptr1, ptr1->sibling);
				ptr1->sibling = fast;
				slow->sibling = ptr1;
			}

			else
			{
				slow = ptr1;
				ptr1 = ptr1->sibling;
			}
		}
	}
}

template<class T>
BinHeap<T>::BinHeap() : head(new HNode<T>()) {}

template<class T>
BinHeap<T>::BinHeap(const T& var) : head(new HNode<T>())
{
	head->sibling = new HNode<T>(var);
}

template<class T>
BinHeap<T>::~BinHeap()
{
	this->clear();
	delete head;
}

template<class T>
int BinHeap<T>::size()
{
	HNode<T>* temp = head->sibling;
	int result = 0;

	while (temp)
	{
		result += static_cast<int>(pow(2, temp->degree));
		temp = temp->sibling;
	}

	return result;
}

template<class T>
bool BinHeap<T>::isEmpty()
{
	return head->sibling == nullptr;
}

template<class T>
T BinHeap<T>::getMin()
{
	if (isEmpty())
	{
		std::string error = "BinHeap is empty. Try again.";
		throw error;
	}

	HNode<T>* temp = head->sibling;
	HNode<T>* min = temp;

	while (temp)
	{
		if (min->data > temp->data)
		{
			min = temp;
		}

		temp = temp->sibling;
	}

	return min->data;
}

template<class T>
void BinHeap<T>::extractMin()
{
	if (isEmpty()) return;

	HNode<T>* temp = head->sibling;
	HNode<T>* min = temp;

	while (temp)
	{
		if (min->data > temp->data)
		{
			min = temp;
		}

		temp = temp->sibling;
	}

	temp = min;

	HNode<T>* prev = head;
	HNode<T>* cur = head->sibling;
	BinHeap bheap;

	while (cur != temp)
	{
		prev = cur;
		cur = cur->sibling;
	}

	prev->sibling = temp->sibling;
	cur = temp->lchild;

	while (cur)
	{
		cur->parent = nullptr;
		prev = bheap.head->sibling;
		bheap.head->sibling = cur;
		cur = cur->sibling;
		bheap.head->sibling->sibling = prev;
	}

	this->unionHeap(bheap);

	delete temp;
}

template<class T>
void BinHeap<T>::insert(const T& var)
{
	BinHeap<T> A(var);
	this->unionHeap(A);
}

template<class T>
void BinHeap<T>::clear()
{
	while (!isEmpty())
	{
		this->extractMin();
	}
}