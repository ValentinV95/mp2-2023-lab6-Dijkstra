#pragma once
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

public:
	PriorityQueue() {}                           // Конструктор по умолчанию
	~PriorityQueue() {}                          // Деструктор
	T* getMin(int type_of_storage_structure);    // Получение указателя на минимальный элемент
	void insert(const T&);                       // Вставка
	void extractMin();                           // Изъятие минимума
	int size(int type_of_storage_structure);     // Размер
	bool isEmpty(int type_of_storage_structure); // Проверка на пустоту
	void show();                                 // Вывод на экран трех структур хранения

};

template<class T>
T* PriorityQueue<T>::getMin(int type_of_storage_structure)
{
	switch (type_of_storage_structure)
	{
	case DHEAP: return dheap.getMin();
	case BHEAP: return &bheap.getMin()->data;
	case TREE: return &tree.getMin()->data;
	default: throw std::runtime_error("Wrong type");
	}
}

template<class T>
void PriorityQueue<T>::insert(const T& var)
{
	dheap.insert(var);
	bheap.insert(var);
	tree.push(var);
}

template<class T>
void PriorityQueue<T>::extractMin()
{
	dheap.extractMin();
	bheap.extractMin();
	tree.extractMin();
}

template<class T>
int PriorityQueue<T>::size(int type_of_storage_structure)
{
	switch (type_of_storage_structure)
	{
	case DHEAP: return dheap.size();
	case BHEAP: return bheap.size();
	case TREE: return tree.size();
	default: throw std::runtime_error("Wrong type");
	}
}

template<class T>
bool PriorityQueue<T>::isEmpty(int type_of_storage_structure)
{
	switch (type_of_storage_structure)
	{
	case DHEAP: return dheap.isEmpty();
	case BHEAP: return bheap.isEmpty();
	case TREE: return tree.isEmpty();
	default: throw std::runtime_error("Wrong type");
	}
}

template<class T>
void PriorityQueue<T>::show()
{
	std::cout << "Элементы в 2-куча: " << std::endl;
	std::cout << dheap << std::endl;
	std::cout << "Элементы в биномиальной куче: " << std::endl;
	std::cout << bheap << std::endl;
	std::cout << "Элементы в красно-черном дереве (от самого минимального до максимального): " << std::endl;
	tree.getTree();
}