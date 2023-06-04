#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <map>
#include <string>
#include<cmath>

#include "IPriorityQueue.hpp"
#include "TBinomialTree.hpp"
#include "TDHeap.hpp"
#include "TRbTree.hpp"
#include "Dijkstra.hpp"

#define INF SIZE_MAX //Связи между вершинами нет
#define MAX_RANDOM_WAY_COST 10 

using namespace std;
class Graph
{
	vector<vector<size_t>> adjMatrix;
	size_t edgeCount = 0 /*Число ребер*/, vertexCount = 0/*Число вершин*/;

	void createCompliteGraph();

public:
	Graph();
	Graph(const Graph& graph);
	Graph(size_t vertexCount, size_t edgeCount);
	Graph(size_t vertexCount);

	void addEdge(const size_t& v1, const size_t& v2, size_t weight);
	size_t getCost(const size_t& v1, const size_t& v2) const;
	vector<pair<size_t, size_t>> getSiblings(const size_t& v)  const;
	void printTable()  const;
	size_t getVertexCount() const;
	friend ostream& operator << (ostream& out, const Graph& g);
};

struct GraphNode
{
	size_t weight, from, current;

	GraphNode(size_t weight, size_t  from, size_t current);
	GraphNode();

	bool operator < (const GraphNode& node) const;
	bool operator > (const GraphNode& node) const;
	bool operator == (const GraphNode& node) const;
	bool operator != (const GraphNode& node) const;
	bool operator <= (const GraphNode& node) const;
	bool operator >= (const GraphNode& node) const;
};

enum QueueType
{
	DHeap,
	RBTree,
	FibonacciHep
};

class Dijkstra
{
	const Graph& g;
	IPriorityQueue<GraphNode>* queue;
	map<size_t, GraphNode> S;
	size_t start;
	QueueType queueType;

	void graphChek();
public:
	Dijkstra(const Graph& g, size_t start, QueueType queueType);
	void setStart(const size_t& v);
	stack<GraphNode> getWay(size_t v);
	~Dijkstra();
};