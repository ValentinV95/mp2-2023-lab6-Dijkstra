#pragma once

#include <stdexcept>

template <class K, class T>
class PriorityQueue
{
public:
	virtual void insert(const K&, const T&) = 0;
	virtual const T& get_min() const = 0;
	virtual void extract_min() = 0;
	virtual ~PriorityQueue() {}
};