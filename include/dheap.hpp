#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <ostream>

template <int d, class T>
class DHeap
{
private:
	std::vector<T> tData;                        // Данные
	int tsize;                                   // Количество элементов на данный момент

	int minChild(int);                           // Поиск минимального ребенка
	void shiftUp(int);                           // "Всплытие"
	void shiftDown(int);                         // "Погружение"

public:
	DHeap();                                     // Конструктор по умолчанию  
	DHeap(const T&);                             // Конструктор инициализации корня
	void insert(const T&);                       // Вставка
	T getMin();                                  // Получить значение корня
	void extractMin();                           // Извлечение корня
	int size() const { return tsize; }           // Получить количество элементов
	bool isEmpty() const { return tsize == 0; }  // Проверка на пустоту

	friend std::istream& operator >>(std::istream& istr, DHeap& dheap)
	{
		T buffer;

		while (istr >> buffer)
		{
			dheap.insert(buffer);
		}

		return istr;
	}

	friend std::ostream& operator <<(std::ostream& ostr, const DHeap& dheap)
	{
		for (int i = 0; i < dheap.tsize; i++)
			ostr << dheap.tData[i] << " ";

		return ostr;
	}

};

template <int d, class T>
int DHeap<d, T>::minChild(int ind)
{
	int child = d * ind + 1;
	int min = child;

	for (int i = child + 1; i < std::min(tsize, child + d); i++)
	{
		if (tData[min] > tData[i])
			min = i;
	}

	return min;
}

template <int d, class T>
void DHeap<d, T>::shiftUp(int ind)
{
	int parent = (ind - 1) / d;

	while (ind != 0 && tData[ind] < tData[parent])
	{
		T temp = tData[ind];
		tData[ind] = tData[parent];
		tData[parent] = temp;
		ind = parent;
		parent = (ind - 1) / d;
	}
}

template <int d, class T>
void DHeap<d, T>::shiftDown(int ind)
{
	int child = minChild(ind);

	while (child < tsize && tData[ind] > tData[child])
	{
		T temp = tData[ind];
		tData[ind] = tData[child];
		tData[child] = temp;
		ind = child;
		child = minChild(ind);
	}
}

template <int d, class T>
DHeap<d, T>::DHeap() : tsize(0)
{
	if (d < 1) throw std::logic_error("Wrong child number");
}

template <int d, class T>
DHeap<d, T>::DHeap(const T& var) : tsize(1)
{
	if (d < 1) throw std::logic_error("Wrong child number");
	tData.push_back(var);
}

template <int d, class T>
void DHeap<d, T>::insert(const T& var)
{
	tData.push_back(var);
	shiftUp(tsize++);
}

template <int d, class T>
T DHeap<d, T>::getMin()
{
	if (isEmpty())
	{
		std::string error = "DHeap is empty. Try again.";
		throw error;
	}

	return tData[0];
}

template <int d, class T>
void DHeap<d, T>::extractMin()
{
	if (!isEmpty())
	{
		tData[0] = tData[--tsize];
		tData.pop_back();
		shiftDown(0);
	}
}