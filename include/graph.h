#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "queue.h"

class Graph {
private:
	std::vector<std::vector<int>> Matrix;
	size_t size;
	size_t count_edge;
public:
	Graph() {}

	Graph(Graph& _G)
	{
		this->size = _G.size;
		Matrix = std::vector<std::vector<int>>(size);
		for (size_t i = 0; i < size; i++)
		{
			Matrix[i] = std::vector<int>(size, 0);
		}
		this->count_edge = _G.count_edge;

		for (size_t i = 0; i < _G.size; i++)
			for (size_t j = 0; j < _G.size; j++)
				this->Matrix[i][j] = _G[i][j];
	}

	Graph(size_t size, int count_edge)
	{
		this->size = size;
		Matrix = std::vector<std::vector<int>>(size);
		for (size_t i = 0; i < size; i++)
		{
			Matrix[i] = std::vector<int>(size, 0);
		}
		this->count_edge = count_edge;
	}

	size_t Get_size()
	{
		return size;
	}

	void Random_generate()
	{
		std::vector<int> not_entry_vertex(size, 0);
		std::vector<int> entry_vertex(1);

		srand(time(NULL));
		not_entry_vertex[0] = -1;  //v1 is entry
		entry_vertex[0] = 0;
		int id_prev_vertex = 0;
		int real_count_edge = 0;
		for (; real_count_edge != size - 1; real_count_edge++)
		{
			int id_random_vertex = rand() % size;
			while (not_entry_vertex[id_random_vertex] == -1)
			{
				if (id_random_vertex == size-1)
					id_random_vertex = 0;
				else
					id_random_vertex++;
			}

			not_entry_vertex[id_random_vertex] = -1;

			this->Matrix[id_prev_vertex][id_random_vertex] = rand() % 101; //width of edge
			this->Matrix[id_random_vertex][id_prev_vertex] = this->Matrix[id_prev_vertex][id_random_vertex];

			entry_vertex.push_back(id_random_vertex);

			id_prev_vertex = entry_vertex[rand() % (real_count_edge + 1)];
		}

		srand(time(NULL));
		while (real_count_edge != this->count_edge)
		{
			int id_random_vertex1 = rand() % size;
			int id_random_vertex2 = rand() % size;
			if (id_random_vertex1 == id_random_vertex2)
			{
				if (id_random_vertex2 < size - 1)
					id_random_vertex2++;
				else
					id_random_vertex2--;
			}
				
			if (this->Matrix[id_random_vertex1][id_random_vertex2] == 0)/////
			{
				this->Matrix[id_random_vertex1][id_random_vertex2] = rand() % 101;
				this->Matrix[id_random_vertex2][id_random_vertex1] = this->Matrix[id_random_vertex1][id_random_vertex2];
				real_count_edge++;
			}
		}
	}

	void User_generate()
	{
		std::cout << "Enter cost trace first to second vertex or enter 0, if trace not make" << std::endl;
		for (int i = 0; i < size; i++)
			for (int j = 0; j < i; j++)
			{
				std::cout << i << "to" << j << ": ";
				std::cin >> this->Matrix[i][j];
				this->Matrix[j][i] = this->Matrix[i][j];
			}
	}

	std::vector<int>& operator[](const size_t& i)
	{
		return this->Matrix[i];
	}

	void show_Graph()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				std::cout << this->Matrix[j][i] << "\t";
			}
			std::cout << "\n";
		}
	}
};

class AlgDijkstra {
private:
	Graph G;
	std::vector<std::pair<size_t, size_t>> cost_path;  // first - width, second - vertex_path
	priority_queue<size_t, size_t>* queue;
	size_t start_vertex;
public:
	AlgDijkstra(Graph G, priority_queue<size_t, size_t>* q, size_t start_vertex)
	{
		this->G = G;
		cost_path = std::vector<std::pair<size_t, size_t>>(G.Get_size()); //first - cost, second - name prev Vertex
		for (size_t i = 0; i < G.Get_size(); i++)
		{
			cost_path[i].first = INFINITY;
			cost_path[i].second = 0;
		}
		this->queue = q;
		this->start_vertex = start_vertex;
		run(start_vertex);
	}

	void run(size_t start_vertex)
	{
		cost_path[start_vertex].first = 0;
		cost_path[start_vertex].second = start_vertex;

		queue->insert(0, start_vertex);

		for (size_t i = 0; i < G.Get_size(); i++)
		{
			size_t min_vertex = queue->getMinimum();
			queue->extractMin();

			for (size_t j = i; j < G.Get_size(); j++)
			{
				size_t min_vertex_cost = cost_path[min_vertex].first + G[min_vertex][j];
				
				if (j != start_vertex && min_vertex != j && G[min_vertex][j] != 0 && (min_vertex_cost < cost_path[j].first || cost_path[j].first == 0))
				{
					cost_path[j].first = min_vertex_cost;
					cost_path[j].second = min_vertex;

					queue->insert(min_vertex_cost, j);
				}
			}
		}
	}

	void min_cost_path_vertex(size_t vertex)
	{
		if (vertex == start_vertex)
		{
			std::cout << start_vertex << "->" << start_vertex << std::endl;
			std::cout << "cost = 0";
		}
		else if (cost_path[vertex].second == start_vertex)
		{
			std::cout << start_vertex << "->" << vertex << std::endl;
			std::cout << "cost = " << cost_path[vertex].first;
		}
		else
		{
			std::string path_to_vertex = std::to_string(vertex);
			for (size_t i = cost_path[vertex].second; i != start_vertex; i = cost_path[i].second)
			{
				path_to_vertex += std::to_string(i);
			}
			std::cout << start_vertex;
			for (int i = path_to_vertex.size() - 1; i >= 0; i--)
			{
				std::cout << "->";
				std::cout << path_to_vertex[i];
			}
			std::cout << "\ncost = " << cost_path[vertex].first;
		}
	}
};