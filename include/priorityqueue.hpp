#pragma once
#include <string>
#include "dheap.hpp"
#include "binomialheap.hpp"
#include "tree.hpp"

enum { DHEAP = 1, BHEAP, TREE};

template<class T>
class PriorityQueue
{
private:
	DHeap<2, T> dheap;                           // Элементы в д-куче
	BinHeap<T> bheap;                            // Элементы в биномиальной куче
	Tree<T> tree;                                // Элементы в красно-черном дереве
	int type;                                    // Структура хранения

public:
	PriorityQueue(int type_of_storage_structure);// Конструктор по умолчанию
	~PriorityQueue() {}                          // Деструктор
	T front();                                   // Получение минимального элемента
	void push(const T&);                         // Вставка
	void pop();                                  // Изъятие минимума
	int size();                                  // Размер
	bool isEmpty();                              // Проверка на пустоту
	void show();                                 // Вывод на экран трех структур хранения

};

template<class T>
PriorityQueue<T>::PriorityQueue(int type_of_storage_structure) : type(type_of_storage_structure)
{
	if (TREE < type || type < DHEAP)
	{
		std::string error = "Введенный тип структуры хранения неправильный ";
		throw error;
	}
}

template<class T>
T PriorityQueue<T>::front()
{
	switch (type)
	{
	case DHEAP: return dheap.getMin();
	case BHEAP: return bheap.getMin();
	case TREE: return tree.getMin();
	}
}

template<class T>
void PriorityQueue<T>::push(const T& var)
{
	switch (type)
	{
	case DHEAP:
	{
		dheap.insert(var);
		break;
	}
	case BHEAP:
	{
		bheap.insert(var);
		break;
	}
	case TREE:
	{
		tree.push(var);
		break;
	}
	}
}

template<class T>
void PriorityQueue<T>::pop()
{
	switch (type)
	{
	case DHEAP:
	{
		dheap.extractMin();
		break;
	}
	case BHEAP:
	{
		bheap.extractMin();
		break;
	}
	case TREE:
	{
		tree.extractMin();
		break;
	}
	}
}

template<class T>
int PriorityQueue<T>::size()
{
	switch (type)
	{
	case DHEAP: return dheap.size();
	case BHEAP: return bheap.size();
	case TREE: return tree.size();
	}
}

template<class T>
bool PriorityQueue<T>::isEmpty()
{
	switch (type)
	{
	case DHEAP: return dheap.isEmpty();
	case BHEAP: return bheap.isEmpty();
	case TREE: return tree.isEmpty();
	}
}

template<class T>
void PriorityQueue<T>::show()
{
	switch (type)
	{
	case DHEAP:
	{
		std::cout << "Элементы в 2-куча: " << std::endl;
		std::cout << dheap << std::endl;
		break;
	}
	case BHEAP:
	{
		std::cout << "Элементы в биномиальной куче: " << std::endl;
		std::cout << bheap << std::endl;
		break;
	}
	case TREE:
	{
		std::cout << "Элементы в красно-черном дереве (от самого минимального до максимального): " << std::endl;
		tree.getTree();
		break;
	}
	}
}