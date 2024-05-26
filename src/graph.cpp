#include <stdexcept>
#include <random>
#include <queue>
#include "graph.h"

Graph::Graph(size_t _n, size_t _e) : m(_n), _edges(_e) {}
Graph::Graph(const Graph& g) : m(g.m), _edges(g._edges) {}

Graph::Graph(const SquareMatrix<int>& _m) : m(_m), _edges(0)
{
	for (size_t i = 0; i < m.size(); ++i)
	{
		for (size_t j = i; j < m.size(); j++)
		{
			if (m.pos(i, j) < 0 || m.pos(j, i) < 0)
				throw std::invalid_argument("Can\'t create graph with negative weights");
			else if (m.pos(i, j) != 0 || m.pos(j, i) != 0)
				_edges++;
		}
	}
}

Graph& Graph::operator=(const Graph& g)
{
	if (this == &g)
		return *this;
	m = g.m;
	_edges = g._edges;
	return *this;
}

Graph generateConnectedGraph(size_t n, size_t e)
{
	if ((n > e + 1) || (e > (n * (n - 1) / 2)))
		throw std::invalid_argument("Trying to generate a non-connected graph");

	Graph res(n, e);
	
	res.pos(0, 1) = res.pos(1, 0) = std::rand() % MAX_DIST;
	for (size_t i = 2; i < n; ++i)
	{
		size_t r = std::rand() % i;
		res.pos(i, r) = res.pos(r, i) = std::rand() % MAX_DIST;
	}

	for (size_t i = 0; i < e - n + 1; ++i)
	{
		size_t j = std::rand() % n;
		size_t r = std::rand() % n;
		while (res.pos(j, r) != 0 || j == r)
		{
			j = std::rand() % n;
			r = std::rand() % n;
		}

		res.pos(j, r) = res.pos(r, j) = std::rand() % MAX_DIST;
	}

	return res;
}

void Graph::inputMatrix() { std::cin >> m; }

Graph Graph::inputMatrix(size_t n, size_t e)
{
	SquareMatrix<int> _m(n);
	std::cin >> _m;
	Graph g(_m);
	if (g.edges() != e)
		throw std::invalid_argument("Wrong adjacency matrix");
	return g;
}

void Graph::printMatrix() { std::cout << m; }

void Graph::printAdjacencyList()
{
	for(size_t i = 0; i < m.size(); ++i)
	{
		std::cout << "Verticle " << i + 1 << ": ";
		for (size_t j = 0; j < m.size(); ++j)
			if(m.pos(i,j) != 0)
				std::cout << j + 1 << ": " << m.pos(i,j) << ", ";
		std::cout << std::endl;
	}
}

bool Graph::isConnected()
{ 
	size_t counter = 0;
	bool* con = new bool[m.size()] {};
	std::queue<size_t> q;

	for (size_t i = 0; i < m.size(); ++i)
	{
		if (!con[i])
			counter++;

		q.push(i);
		con[i] = true;

		while (!q.empty())
		{
			for (size_t j = 0; j < m.size(); ++j)
			{
				if (!con[j] && (m.pos(q.front(), j) != 0 || m.pos(j, q.front()) != 0))
				{
					q.push(j);
				}
			}

			con[q.front()] = true;
			q.pop();
		}
	}

	delete[] con;
	return counter == 1;
}