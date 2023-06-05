#pragma once

#include <iostream>

template <typename T, typename N>
class priority_queue {
public:
	priority_queue() {}
	
	virtual void insert(T data, N key) = 0;

	virtual T getMinimum() = 0;

	virtual void extractMin() = 0;

	~priority_queue() {}
};