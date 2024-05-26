#ifndef DHEAP_H
#define DHEAP_H

#include <algorithm>

template<class T>
class DHeap
{
public:
	DHeap() : arr(new T[128]), sz(0), cap(128) {}
	DHeap(const DHeap& h) : arr(new T[h.cap]), sz(h.sz), cap(h.cap) { std::copy(h.arr, h.arr + sz, arr); }
	~DHeap() { delete[] arr; }
	DHeap& operator=(const DHeap& h)
	{
		if (this == &h)
			return *this;
		DHeap tmp(h);
		swap(*this, tmp);
		return *this;
	}

	const T& top() const
	{
		if (sz == 0)
			throw std::runtime_error("Trying to access the empty heap");
		return arr[0];
	}
	int size() const { return sz; }
	bool empty() const { return sz == 0; }

	void push(const T& t)
	{
		if (sz == cap)
			resize();
		arr[sz++] = t;
		shift_up(sz - 1);
	}

	void pop()
	{
		if (sz == 0)
			return;

		std::swap(arr[0], arr[--sz]);
		shift_down(0);
	}

	friend void swap(DHeap& lhs, DHeap& rhs)
	{
		std::swap(lhs.arr, rhs.arr);
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.cap, rhs.cap);
	}

private:
	T* arr;
	int sz;
	int cap;

	void resize()
	{
		cap *= 2;
		T* tmp = new T[cap];
		std::copy(arr, arr + sz, tmp);
		delete[] arr;
		arr = tmp;
	}

	void shift_up(int i)
	{
		int i_p = (i - 1) / 2;
		while (i > 0 && arr[i] < arr[i_p])
		{
			std::swap(arr[i], arr[i_p]);
			i = i_p;
			i_p = (i - 1) / 2;
		}
	}

	void shift_down(int i)
	{
		while (2 * i + 1 < sz)
		{
			int i_lc = 2 * i + 1;
			int i_rc = 2 * i + 2;
			int i_c = i_lc;

			if (i_rc < sz && arr[i_rc] < arr[i_lc])
				i_c = i_rc;

			if (arr[i] > arr[i_c])
			{
				std::swap(arr[i], arr[i_c]);
				i = i_c;
			}

			else
				break;
		}
	}
};

#endif