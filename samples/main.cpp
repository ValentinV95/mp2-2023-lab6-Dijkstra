#include <iostream>
#include "graph.h"
#include "avlTree.h"
#include "dHeap.h"
#include "priorityQueue.h"
#include "fibonacciHeap.h"

int main()
{
	int size = 0;
	do
	{
		std::cout << "Enter the number of vertices in the graph: ";
		std::cin >> size;
	} while (size <= 0);
	char autoNames;
	std::cout << "\nSet vertex names automatically?\ny - Yes, n - No : ";
	std::cin >> autoNames;

	char queueType = 'w';

	std::cout << "\nSelect the queue type :";
	do
	{
		std::cout << "\nd - queue on the dHeap, f - queue on the FibonacciHeap, a - queue on the avlTree : ";
		std::cin >> queueType;
	} while (queueType != 'd' && queueType != 'f' && queueType != 'a');

	Dijkstra d(size, queueType, autoNames == 'y');
	d.showTable();

	char autoGener = 'n';
	std::cout << "\nGenerate a graph automatically?\ny - Yes, n - No : ";
	std::cin >> autoGener;
	if (autoGener == 'y')
	{
		d.generateRandom();
	}
	else
	{
		std::cout << "\nEnter the names of the two verticesand their weights (for example a b 3)";
		std::cout << "\nto complete, enter 0 0 0";
		char v1 = 'q', v2 = 'w'; int w = 3;
		while (true)
		{
			std::cout << "\n";
			d.showTable();
			std::cout << "\n";
			std::cin >> v1 >> v2 >> w;
			if (v1 == '0' && v2 == '0' && w == 0)
				break;
			try
			{
				d.addEdge(v1, v2, w);
			}
			catch (const std::exception& ex)
			{
				std::cout << "Failed to add : " << ex.what() << '\n';
			}
		}
		if (!d.isConnected())
		{
			std::cout << "Add edges for graph connectivity?\ny - Yes, n - No : ";
			std::cin >> autoGener;
			if(autoGener == 'y')
				d.addConnected();
		}
	}


	std::cout << "\n";
	d.showTable();
	std::cout << "\n";
	char v1, v2;
	std::cout << "\nEnter two vertexes the path between which you want to find : ";
	std::cin >> v1 >> v2;
	try
	{
		d.setStartVert(v1);
		std::cout << "\nWay : " << d.getMinWay(v2)<< ", len : " << d.wayLen(v2);
	}
	catch (const std::exception&ex)
	{
		std::cout << "No such vertexes!";
	}
	return 0;
}