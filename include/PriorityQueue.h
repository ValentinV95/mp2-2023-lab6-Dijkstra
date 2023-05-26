#pragma once

#include<utility>
#include<string>

using namespace std;

template<class T>
class PriorityQueue
{
public:
	virtual const T& getMin() const = 0;

	virtual void extractMin() = 0;

	virtual void insert(const T& elem) = 0;
};