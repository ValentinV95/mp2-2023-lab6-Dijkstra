#pragma once
#include <iostream>
#include <vector>


class Graph {
	// struct for work with heap
	struct minpath {
		int ind; //index of vertex in names vector
		double* distance; //pointer to min found distance between the selected vertex and the vertex with index ind 
		minpath(int ind_=-1, double* dist=nullptr);
		bool operator==(const minpath& p) const noexcept;
		bool operator<=(const minpath& p) const noexcept;
		bool operator>=(const minpath& p) const noexcept;
		bool operator>(const minpath& p) const noexcept;
		bool operator<(const minpath& p) const noexcept;
	};


	template <class heap>
	void work_with_heap(const int ind) {
	delete[] paths;
	paths = nullptr;
	paths = new double[names.size()];
	for (int i = 0; i < names.size(); i++) paths[i] = INFINITY;
	paths[ind]= 0;
	heap H;
	H.push(minpath(ind, &(paths[ind])));
	minpath tmp;
	// Dijkstra algorithm
	while (!H.empty()) {
		tmp = H.top();
		H.pop();
		for (int i = 0; i < names.size(); i++) {
			// if there is a path to this vertex
			if (graph[tmp.ind][i] != INFINITY)
				// if this vertex already in heap
				if (paths[i] != INFINITY) {
					//if distnce less than saved
					if (paths[i] > graph[tmp.ind][i] + *tmp.distance)
						paths[i] = graph[tmp.ind][i] + *tmp.distance;
				}
				//if vertex isn't found in the heap
				else {
					//push it in a heap and save distance
					paths[i] = graph[tmp.ind][i] + *tmp.distance;
					H.push( minpath( i, &(paths[i]) ) );
				}
		}
	}
	};
	std::vector<std::vector<double>> graph;		// connectivity marix
	std::vector<std::string> names; 	// names for vertices
	double* paths; 	// rusults of Dijkstra algorithm
public:
	Graph();
	~Graph();
	void clear();
	void addV(const std::string& str);
	void addE(const std::string& v1, const std::string& v2, double weight);
	void delV(const std::string& str);
	void delE(const std::string& v1, const std::string& v2);
	bool check_Dijkstra() const noexcept;
	void rnd(int countV, double percentE);
	void Dijkstra(const std::string& str);
	double path(const std::string& end);
	bool check_connected() const;
	void look();
	void GraphViz(const std::string& name);
};