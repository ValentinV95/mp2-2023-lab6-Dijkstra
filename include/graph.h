#pragma once
#include <string>
#include <exception>
#include <iostream>
#include <limits.h>
#include "priorityQueue.h"
#include <algorithm>

class Graph
{
private:
	struct edge
	{
		char left, right;
		edge() { left = ' ', right = ' '; }
		edge(char l, char r) { left = l; right = r; }
		void set(char l, char r) { left = l; right = r; }
	};

	int edgeSize, edgeRealSize;
	edge* edges = nullptr;
	bool* visited;

	void resizeEdge()
	{
		edge* tmp = new edge[edgeRealSize * 2];
		for (int i = 0; i < edgeRealSize; i++)
			tmp[i] = edges[i];
		delete[] edges;
		edges = tmp;
		edgeRealSize *= 2;
	}
	
	void dfs(bool* visited, char vert)
	{
		if (!visited[nameIndex(vert)])
		{
			visited[nameIndex(vert)] = true;
			for (int i = 0; i < edgeSize; i++)
			{
				if (edges[i].left == vert)
				{
					dfs(visited, edges[i].right);
				}
			}
		}
		return;
	}

protected:
	int* array = nullptr;
	char* names = nullptr;
	int size = 0;

	int nameIndex(char ch)
	{
		for (int i = 0; i < size; i++)
			if (names[i] == ch)
				return i;
		throw std::exception("no such vertices!");
	}

	int& at(int i, int j)
	{
		if (i >= size || j >= size)
			throw std::exception("incorrect index!");
		return array[i * size + j];
	}
public:
	Graph(int size = 5, bool autoNames = true)
	{
		if (size <= 0)
			throw std::exception("graph size must be greater than 0!");
		this->size = size;
		array = new int[size * size];
		names = new char[size];
		if (autoNames)
		{
			for (int i = 0; i < size; i++)
			{
				names[i] = 97 + i;
			}
		}
		else
		{
			std::cout << "input the name of " << size <<" vertices:";
			for (int i = 0; i < size; i++)
			{
				std::cin >> names[i];
			}
		}
		for (int i = 0; i < size * size; i++)
		{
			array[i] = 0;
		}
		edgeRealSize = 10;
		edgeSize = 0;
		edges = new edge[edgeRealSize];
		visited = new bool[size];
	}

	Graph(const Graph& gr)
	{
		size = gr.size;
		array = new int[size * size];
		names = new char[size];
		for (int i = 0; i < size; i++)
		{
			names[i] = gr.names[i];
		}
		for (int i = 0; i < size * size; i++)
		{
			array[i] = gr.array[i];
		}

		edgeRealSize = gr.edgeRealSize;
		edgeSize = gr.edgeSize;
		edges = new edge[edgeRealSize];
		for (int i = 0; i < edgeSize; i++)
			edges[i] = gr.edges[i];
		visited = new bool[size];
	}

	~Graph() 
	{
		delete[] array;
		delete[] names;
		delete[] edges;
		delete[] visited;
	}



	

	void addEdge(char vert1, char vert2, int val)
	{
		if (vert1 == vert2)
			throw std::exception("incorrect vertices!");
		if (val < 0)
			throw std::exception("the edge weight must be positive!");
		int i = nameIndex(vert1), j = nameIndex(vert2);
		at(i, j) = val;
		if (edgeSize == edgeRealSize)
			resizeEdge();
		edges[edgeSize++] = edge(vert1, vert2);
	}
	void addEdge(int vert1, int vert2, int val)
	{
		if (vert1 == vert2)
			throw std::exception("incorrect vertices!");
		if (val < 0)
			throw std::exception("the edge weight must be positive!");
		at(vert1, vert2) = val;
		if (edgeSize == edgeRealSize)
			resizeEdge();
		edges[edgeSize++] = edge(names[vert1], names[vert2]);
	}

	void showTable()
	{
		std::cout << " \t";
		for (int i = 0; i < size; i++)
		{
			std::cout << names[i] << "\t";
		}
		std::cout << "\n";
		for (int i = 0; i < size; i++)
		{
			std::cout << names[i] << "\t";
			for (int j = 0; j < size; j++)
			{
				std::cout << array[i * size + j] << "\t";
			}
			std::cout << '\n';
		}
	}

	bool isConnected()
	{
		bool* visited = new bool[size];
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				visited[j] = false;
			dfs(visited, names[i]);
			for (int j = 0; j < size; j++)
			{
				if (!visited[j])
					return false;
			}
		}
		delete[] visited;
		return true;
	}

	void addConnected(bool autoAdd = false)
	{ 
		int num;
		srand(NULL);
		int notNull = 0;
		for (int i = 0; i < size; i++)
		{
			notNull = 0;
			for (int j = 0; j < size; j++)
				visited[j] = false;
			
			dfs(visited, names[i]);
			
			for (int j = 0; j < size; j++)
				if (visited[j] == true)
					notNull++;

			for (int j = 0; j < size; j++)
			{
				if (!visited[j] && !array[i*size + j] && !array[j*size + i] && notNull < size-1)
				{
					notNull++;
					if (autoAdd)
					{
						num = rand() % 20 + 1;
						std::cout << "add edge : " << names[i] << "->" << names[j] << " : " << num << "\n";
						addEdge(names[i], names[j], num);
					}
					else
					{
						std::cout << "input : " << names[i] << "->" << names[j] << " : ";
						std::cin >> num;
						addEdge(names[i], names[j], num);
					}

				}
			}
		}
		if (!isConnected())
		{
			int addConnect = -1;

			for (int i = 0; i < size; i++)
			{
				notNull = 0;
				for (int j = 0; j < size; j++)
					visited[j] = false;

				dfs(visited, names[i]);

				for (int j = 0; j < size; j++)
					if (visited[j] == true)
						notNull++;
				if (notNull == size)
				{
					addConnect = i;
					break;
				}
			}
			for (int j = 0; j < size; j++)
			{
				if (array[j * size + addConnect] == 0 && addConnect != j)
				{
					if (autoAdd)
					{
						num = rand() % 20 + 1;
						std::cout << "add edge : " << names[j] << "->" << names[addConnect] << " : " << num << "\n";
						addEdge(j, addConnect, num);
					}
					else
					{
						std::cout << "input : " << names[j] << "->" << names[addConnect] << " : ";
						std::cin >> num;
						addEdge(j, addConnect, num);
					}

				}
			}
		}
	}

	void generateRandom()
	{
		for (int i = 0; i < size * size; i++)
		{
			array[i] = 0;
		}
		delete[] edges;
		edgeRealSize = 10;
		edgeSize = 0;
		edges = new edge[edgeRealSize];
		srand(NULL);
		int num, r;
		for (int i = 0; i < size * size; i++)
		{
			r = rand() % 20;
			if (!r && i/size != i%size)
			{
				num = rand() % 20 + 1;
				addEdge(i/size, i%size, num);
				std::cout << "add edge : " << names[i/size] << "->" << names[i%size] << " : " << num << "\n";
			}
		}
		addConnected(true);
	}
};

struct queue_elem
{
	int way;
	char name;
	bool operator < (const queue_elem& r) { return way < r.way; }
	bool operator > (const queue_elem& r) { return way > r.way; }
	bool operator <= (const queue_elem& r) { return way <= r.way; }
	bool operator >= (const queue_elem& r) { return way >= r.way; }
	bool operator == (const queue_elem& r) { return way == r.way && name == r.name; }
	queue_elem operator = (const queue_elem& r) { way = r.way; name = r.name; return *this; }
	void set(int w, char n) { way = w; name = n; }
};


class Dijkstra : public Graph
{
private:
	struct Vertices
	{
		char name;
		int way;
		bool visit;
		Vertices()
		{
			name = ' ';
			way = INT_MAX;
			visit = false;
		}
		Vertices operator = (const Vertices& v)
		{
			name = v.name;
			way = v.way;
			visit = v.visit;
			return *this;
		}
	};

	priorityQueue<queue_elem>* queue;
	Vertices* vertices = nullptr;
	char vert = ' ';

	Vertices findVertices(char ch)
	{
		for (int i = 0; i < size; i++)
		{
			if (vertices[i].name == ch)
				return vertices[i];
		}
	}
	int findVerticesIndex(char ch)
	{
		for (int i = 0; i < size; i++)
		{
			if (vertices[i].name == ch)
				return i;
		}
	}
	
public:
	Dijkstra(int size = 5, char queueType = 'd', bool autoVert = true) : Graph(size, autoVert)
	{
		if (queueType != 'd' && queueType != 'f' && queueType != 'a')
			throw std::exception("no such queue type!");
		else if(queueType != 'd')
			queue = new dHeapQueue<queue_elem>;
		else if (queueType != 'f')
			queue = new fibonacciQueue<queue_elem>;
		else
			queue = new avlQueue<queue_elem>;
	}
	~Dijkstra() 
	{
		delete queue;
		if (vertices != nullptr)
			delete[] vertices;
	}

	void showVer()
	{
		if (vertices == nullptr)
			throw std::exception("need to set a starting vertice!");
		for (int i = 0; i < size; i++)
		{
			std::cout << vertices[i].name << '\t';
		}
		std::cout << '\n';
		for (int i = 0; i < size; i++)
		{
			std::cout << vertices[i].way << '\t';
		}
		std::cout << '\n';
		for (int i = 0; i < size; i++)
		{
			std::cout << vertices[i].visit << '\t';
		}
		std::cout << '\n';
	}

	void setStartVert(char vert1)
	{
		vert = vert1;
		if (vertices != nullptr)
			delete[] vertices;
		vertices = new Vertices[size];


		for (int i = 0; i < size; i++)
		{
			vertices[i].name = names[i];
			if (vertices[i].name == vert)
			{
				vertices[i].visit = true;
				vertices[i].way = 0;
			}
		}

		int index = nameIndex(vert);
		queue_elem addElem, getElem;
		Vertices v;
		for (int i = 0; i < size; i++)
		{
			if (array[index * size + i] != 0)
			{
				addElem.set(array[index * size + i], names[i]);
				queue->insert(addElem);
			}
		}
		while (!queue->isEmpty())
		{

			getElem = queue->getMin();
			int i = findVerticesIndex(getElem.name);
			if (vertices[i].way > getElem.way)
			{
				vertices[i].visit = true;
				vertices[i].way = getElem.way;


				index = nameIndex(getElem.name);
				for (int j = 0; j < size; j++)
				{
					if (array[index * size + j] != 0)
					{
						addElem.set(array[index * size + j] + vertices[i].way, names[j]);
						queue->insert(addElem);
					}
				}
			}
		}
	}


	std::string getMinWay(char vert2)
	{
		int index = nameIndex(vert2);
		Vertices v = findVertices(vert2);
		if (!v.visit)
			throw std::exception("no such way!");

		std::string str;
		str += v.name;
		while (v.name != vert)
		{
			for (int i = 0; i < size; i++)
			{
				if (array[index + i * size] != 0 && array[index + i * size] + findVertices(names[i]).way == v.way)
				{
					v = vertices[i];
					str += std::string(">-");
					str += v.name;
					index = i;
					break;
				}

			}
		}
		std::reverse(str.begin(), str.end());
		return str;
	}

	int wayLen(char vert)
	{
		if (!findVertices(vert).visit)
			throw std::exception("no such way!");
		return findVertices(vert).way;
	}
};


