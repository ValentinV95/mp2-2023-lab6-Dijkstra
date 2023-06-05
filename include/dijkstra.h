#pragma once
#include <vector>
#include <list>
#include <string>
#include "graph.h"
#include "priorityqueue.hpp"

struct Vertex
{
	int dest;
	int indName;

	Vertex() {}

	Vertex(int _dist, int _indName) : dest(_dist), indName(_indName) {}

	const Vertex& operator =(const Vertex& other)
	{
		this->dest = other.dest;
		this->indName = other.indName;

		return *this;
	}

	bool operator <(const Vertex& other) const
	{
		return this->dest < other.dest;
	}

	bool operator >(const Vertex& other) const
	{
		return this->dest > other.dest;
	}

	bool operator <=(const Vertex& other) const
	{
		return this->dest <= other.dest;
	}

	bool operator >=(const Vertex& other) const
	{
		return this->dest >= other.dest;
	}

	bool operator ==(const Vertex& other) const
	{
		return this->dest == other.dest;
	}

	bool operator !=(const Vertex& other) const
	{
		return this->dest != other.dest;
	}
};

class Dijkstra
{
private:
	int* adjMatrix;                                        // Матрица смежности
	int size;                                              // Размер матрицы
	int startPoint;                                        // Начальная вершина
	std::map<int, bool> markedVert;                        // Посещенные вершины
	std::map<int, int> destVert;                           // Расстояния до вершин

	void algorithmDijkstra(int);                           // Алгоритм Дейкстры

public:
	Dijkstra(const Graph&, int _startPoint, int type);     // Конструктор
	~Dijkstra();                                           // Деструктор
	int getCostMinWay(int);                                // Получить минимальную стоимость до вершины
	std::list<int> getMinWay(int);                         // Получить список вершин до введенной

};
