#pragma once
#include <iostream>

template <class T>
class DHeap {
	T* mas;
	int size, capacity;
	int d;
	void resize() {
		int add = d * d;
		while (capacity > add) add*=d;
		capacity += add;
		T* tmp = new T[capacity]{};
		std::copy(mas, mas + size, tmp);
		delete[] mas;
		mas = tmp;
	}
	void up(int ind) {
		while (ind!=0 && mas[ind] < mas[(ind - 1) / d]) {
			std::swap(mas[ind], mas[(ind - 1) / d]);
			ind = (ind - 1) / d;
		}
	}
	void down(int ind) {
		int min=ind;
		while (ind * d + 1 < size) {
			for (int i = ind * d + 1; i <= std::min(ind * d + d,size); i++) if (mas[min] > mas[i]) min = i;
			if (min == ind) break;
			std::swap(mas[min], mas[ind]);
			ind=min;
		}
	}
public:
	DHeap(int d_=3) {
		if (d_ < 3) d = 3;
		else d = d_;
		mas = new T[d+1]{};
		capacity = d+1;
		size = 0;
	}
	~DHeap() {
		delete[] mas;
		mas = nullptr;
	}
	bool empty() { return size == 0; }
	void push(const T& val) {
		if (size == capacity) resize();
		int ind=size;
		mas[size++] = val;
		up(ind);
	}
	T top() {
		if (size) {
			return mas[0];
		}
		throw std::logic_error("There are no elements in this heap");
	}
	void pop() {
		if (size) {
			mas[0] = mas[--size];
			down(0);
		} 
		else throw std::logic_error("There are no elements in this heap");
	}
};