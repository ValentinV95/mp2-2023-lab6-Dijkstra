#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <cmath>

template<class T>
class SquareMatrix
{
public:
	SquareMatrix(size_t _sz) : data(new T* [_sz]), sz(_sz)
	{
		if (sz == 0) throw std::invalid_argument("Can't create empty matrix");
		for (size_t i = 0; i < sz; ++i)
			data[i] = new T[_sz]();
	}

	SquareMatrix(const SquareMatrix& m) : data(new T* [m.sz]), sz(m.sz)
	{
		for (size_t i = 0; i < sz; ++i)
		{
			data[i] = new T[sz];
			std::copy(m.data[i], m.data[i] + sz, data[i]);
		}
	}

	~SquareMatrix() 
	{
		for (size_t i = 0; i < sz; ++i)
			delete[] data[i];
		delete[] data;

		data = nullptr;
		sz = 0;
	}

	SquareMatrix& operator=(const SquareMatrix& m)
	{
		if (this == &m)
			return *this;

		SquareMatrix tmp(m);
		swap(*this, tmp);
		return *this;
	}

	T& pos(size_t i, size_t j) { return data[i][j]; }
	size_t size() const { return sz; }

	void fromString(const std::string& s)
	{
		if (s.length() != sz * sz)
			throw std::invalid_argument("Can't create square matrix from this string");

		for (size_t i = 0; i < sz; ++i)
		{
			for (size_t j = 0; j < sz; ++j)
			{
				data[i][j] = data[j][i] = s[i * j + j];
			}
		}
	}

	friend void swap(SquareMatrix& lhs, SquareMatrix& rhs)
	{
		std::swap(lhs.data, rhs.data);
		std::swap(lhs.sz, rhs.sz);
	}

	friend std::istream& operator>>(std::istream& istr, const SquareMatrix& m)
	{
		for (size_t i = 0; i < m.sz; ++i)
			for (size_t j = 0; j < m.sz; ++j)
				if (!(istr >> m.data[i][j]))
					throw std::invalid_argument("Invalid input into matrix");

		return istr;
	}

	friend std::ostream& operator<<(std::ostream& ostr, const SquareMatrix& m)
	{
		for (size_t i = 0; i < m.sz; ++i)
		{
			for (size_t j = 0; j < m.sz; ++j)
				ostr << m.data[i][j] << " ";
			ostr << "\n";
		}

		return ostr;
	}

private:
	T** data;
	size_t sz;
};

#endif