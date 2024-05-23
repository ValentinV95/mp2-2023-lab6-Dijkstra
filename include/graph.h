#ifndef GRAPH_H
#define GRAPH_H

#include <chrono>
#include <limits>
#include <stack>
#include <vector>
#include "matrix.h"
#define MAX_DIST 100

class Graph
{
public:
	struct dist
	{
		dist(int _d = 0, size_t _n = 0) : d(_d), n(_n) {}
		int d;
		size_t n;

		bool operator<(const dist& _d)  const { return d < _d.d; }
		bool operator<=(const dist& _d) const { return d <= _d.d; }
		bool operator>(const dist& _d)  const { return d > _d.d; }
		bool operator>=(const dist& _d) const { return d >= _d.d; }
		bool operator==(const dist& _d) const { return d == _d.d; }
		bool operator!=(const dist& _d) const { return d != _d.d; }
	};

	Graph(size_t _n = 1, size_t _e = 0);
	Graph(const Graph& g);
	Graph(const SquareMatrix<int>& _m);
	Graph& operator=(const Graph& g);

	inline int& pos(size_t i, size_t j) { return m.pos(i, j); }
	size_t verticles() const { return m.size(); }
	size_t edges() const { return _edges; }

	template<template<class> class HeapType>
	void dijkstra(size_t v_ind);

	void inputMatrix();
	Graph inputMatrix(size_t n, size_t e);
	void printMatrix();
	void printAdjacencyList();

	bool isConnected();

private:
	SquareMatrix<int> m;
	size_t _edges;
};

Graph generateConnectedGraph(size_t n, size_t e);

template<template<class> class HeapType>
void Graph::dijkstra(size_t v_ind)
{
	std::vector<dist> res(verticles(), { std::numeric_limits<int>::max(), std::numeric_limits<size_t>::max() });
	HeapType<dist> heap;

	const auto start{ std::chrono::steady_clock::now() };
	res[v_ind] = { 0, v_ind };
	heap.push(res[v_ind]);

	while (!heap.empty())
	{
		dist cur = heap.top();
		heap.pop();
		if (cur.d > res[cur.n].d)
			continue;

		for (size_t i = 0; i < m.size(); ++i)
		{
			if (m.pos(cur.n, i) != 0 && res[i].d > cur.d + m.pos(cur.n, i))
			{
				res[i] = { cur.d + m.pos(cur.n, i), cur.n };
				heap.push({ res[i].d, i });
			}
		}
	}

	const auto end{ std::chrono::steady_clock::now() };
	const std::chrono::duration<double> elapsed{ end - start };

	for (size_t i = 0; i < res.size(); ++i)
	{
		std::cout << "Verticle " << i + 1 << ": " << res[i].d << ", Path: ";

		size_t j = i;
		if (res[j].n != std::numeric_limits<size_t>::max())
		{
			std::stack<size_t> st;
			for (; j != v_ind;)
			{
				st.push(j + 1);
				j = res[j].n;
			}

			std::cout << v_ind + 1;

			while (!st.empty())
			{
				std::cout << "->" << st.top();
				st.pop();
			}
		}

		std::cout << std::endl;
	}

	std::cout << "Elapsed time using " << typeid(HeapType).name() << ": " << elapsed.count() << std::endl;
}

#endif