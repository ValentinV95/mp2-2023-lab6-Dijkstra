#pragma once

template<typename T>
class IPriorityQueue
{
public:
	virtual const T& getMin() = 0;
	virtual void extractMin() = 0;
	virtual void insert(const T& data) = 0;
	virtual bool isEmpty() const = 0;
};