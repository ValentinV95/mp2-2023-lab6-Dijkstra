#include <iostream>
#include "priorityqueue.hpp"
#include "graph.hpp"
#include <ctime>

using namespace std;


int main()
{
	//srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	Graph graph;
	std::map<std::string, int> map;

	graph.autoGenerateGraph(3, 0);
	graph.getAdjacencyMatrix();
	try
	{
		map = graph.Dijkstra(1, "A");
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}