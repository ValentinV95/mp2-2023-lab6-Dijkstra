#include <iostream>
#include "priorityqueue.hpp"
#include "graph.hpp"

using namespace std;


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	Graph graph;

	graph.autoGenerateGraph(5, 0);
	cout << graph.check() << endl;
	graph.getAdjacencyMatrix();
	cout << graph.check() << endl;
	cout << graph.vertexsSize() << " " << graph.edgesSize() << endl;
}