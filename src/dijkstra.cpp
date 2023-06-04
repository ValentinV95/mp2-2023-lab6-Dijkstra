#include "dijkstra.h"

void Dijkstra::algorithmDijkstra(int type)
{
	PriorityQueue<Vertex> queue(type);                     // Приоритетная очередь, хранящая расстояние и индекс вершины
	Vertex cur;                                            // Текущая вершина
	int row;                                               // Текущий элемент

	queue.push(Vertex(0, startPoint));
	destVert[startPoint] = 0;

	while (!queue.isEmpty())
	{
		cur = queue.front();
		queue.pop();
		row = cur.indName;

		if (markedVert[row] == true) continue;
		else markedVert[row] = true;

		for (int i = 0; i < size; i++)
		{
			if (adjMatrix[row * size + i] != INF && row != i)
			{
				if (i != startPoint && destVert[i] > (adjMatrix[row * size + i] + cur.dest))
				{
					destVert[i] = adjMatrix[row * size + i] + cur.dest;
					queue.push({destVert[i], i});
				}
			}
		}
	}
}

Dijkstra::Dijkstra(const Graph& graph, int _startPoint, int type)
{
	startPoint = _startPoint;
	size = graph.vertSize();

	if (size <= startPoint || startPoint < 0)
	{
		std::string error = "Вершина не найдена. Повторите попытку.";
		throw error;
	}

	adjMatrix = new int[size * size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			adjMatrix[i * size + j] = graph.getAdjMatrix()[i * size + j];

	for (int i = 0; i < size; i++)
	{
		destVert.insert({i,  INF});
		markedVert.insert({i, false});
	}

	algorithmDijkstra(type);
}

Dijkstra::~Dijkstra()
{
	delete[] adjMatrix;
	adjMatrix = nullptr;
}

int Dijkstra::getCostMinWay(int endPoint)
{
	if (size <= endPoint || endPoint < 0)
	{
		std::string error = "Вершина не найдена. Повторите попытку.";
		throw error;
	}

	return destVert[endPoint];
}

std::list<int> Dijkstra::getMinWay(int endPoint)
{
	if (size <= endPoint || endPoint < 0)
	{
		std::string error = "Вершина не найдена. Повторите попытку.";
		throw error;
	}

	std::list<int> result;
	int cur = endPoint;
	int temp;

	result.push_front(cur);

	while (cur != startPoint)
	{
		for (int i = 0; i < size; i++)
		{
			if (adjMatrix[cur * size + i] != INF && cur != i)
			{
				temp = destVert[cur] - adjMatrix[cur * size + i];

				if (temp == destVert[i])
				{
					result.push_front(i);
					cur = i;
					break;
				}
			}
		}
	}

	return result;
}