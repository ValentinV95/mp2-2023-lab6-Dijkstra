#pragma once
#include "dHeap.h"
#include "avlTree.h"
#include "fibonacciHeap.h"


template<class T>
class priorityQueue
{
private:
public:
	dHeap<T, 3> heap;
	avlTree<T, T> tree;
	FibonacciHeap<T, T> fib;
	virtual T getMin() = 0;
	virtual void insert(const T& element) = 0;
	virtual bool isEmpty() = 0;
};


template<class T>
class dHeapQueue: public priorityQueue<T>
{
private:
public:
	dHeapQueue() {}
	~dHeapQueue() {}
	T getMin()
	{
		return priorityQueue<T>::heap.getMin();
	}
	void insert(const T& element)
	{
		priorityQueue<T>::heap.insert(element);
	}
	bool isEmpty()
	{
		return priorityQueue<T>::heap.isEmpty();
	}
};


template<class T>
class avlQueue : public priorityQueue<T>
{
private:
public:
	avlQueue() {}
	~avlQueue() {}
	T getMin()
	{
		return priorityQueue<T>::tree.getMin();
	}
	void insert(const T& element)
	{
		priorityQueue<T>::tree.insert(element, element);
	}
	bool isEmpty()
	{
		return priorityQueue<T>::tree.isEmpty();
	}
};


template<class T>
class fibonacciQueue : public priorityQueue<T>
{
private:
public:
	fibonacciQueue() {}
	~fibonacciQueue() {}
	T getMin()
	{
		return priorityQueue<T>::fib.getMin();
	}
	void insert(const T& element)
	{
		priorityQueue<T>::fib.insert(element, element);
	}
	bool isEmpty()
	{
		return priorityQueue<T>::fib.isEmpty();
	}
};