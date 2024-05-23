#include <iostream>
#include <string>
#include "graph.h"
#include "dheap.h"
#include "bheap.h"
#include "fheap.h"

int main()
{
	// "Graph" stub
	Graph g;
	bool flag = false;
	size_t n, e, i;

	std::cout << "Dijkstra\'s algorithm sample." << std::endl;

	while (true)
	{
		std::string s;
		std::string buff_to_ignore;

		try
		{
			if (!flag)
			{
				std::cout << "1. Generate a connected graph.\n"
					"2. Input your own graph with an adjacency matrix.\n"
					<< "> ";
				std::getline(std::cin, s);

				if (s == "q" || s == "quit")
					break;

				else if (s == "1")
				{
					std::cout << "Enter the verticles number, then the number of edges.\n";
					std::cin >> n >> e;
					std::cin.clear();
					std::getline(std::cin, buff_to_ignore);
					g = generateConnectedGraph(n, e);

					std::cout << "Adjacency list:\n";
					g.printAdjacencyList();

					std::cout << "Enter the verticle number you want to start the search from.\n";
					std::cin >> i;
					--i;
					if (i > g.verticles())
						throw std::invalid_argument("Invalid verticle");

					std::cin.clear();
					std::getline(std::cin, buff_to_ignore);

					g.dijkstra<DHeap>(i);
					g.dijkstra<BHeap>(i);
					g.dijkstra<FHeap>(i);

					while (true)
					{
						std::cout << "Do you want to reuse your graph? (yes\\no)\n";
						std::getline(std::cin, s);

						switch (s[0])
						{
						case 'y':
						case 'Y':
							flag = true;
							break;
						case 'n':
						case 'N':
							flag = false;
							break;
						default:
							std::cout << "What?\n";
							continue;
						}
						break;
					}
				}


				else if (s == "2")
				{
					std::cout << "Enter the verticles number, then the number of edges.\n";
					std::cin >> n >> e;
					std::cin.clear();
					std::getline(std::cin, buff_to_ignore);
					std::cout << "Now input your adjacency matrix.\n";
					g = g.inputMatrix(n, e);

					if (!g.isConnected())
						throw std::invalid_argument("Trying to input non-connected graph");

					std::cout << "Adjacency list:\n";
					g.printAdjacencyList();

					std::cout << "Enter the verticle number you want to start the search from.\n";
					std::cin >> i;
					--i;
					if (i > g.verticles())
						throw std::invalid_argument("Invalid verticle");

					std::cin.clear();
					std::getline(std::cin, buff_to_ignore);

					g.dijkstra<DHeap>(i);
					g.dijkstra<BHeap>(i);
					g.dijkstra<FHeap>(i);

					while (true)
					{
						std::cout << "Do you want to reuse your graph? (yes\\no)\n";
						std::getline(std::cin, s);

						switch (s[0])
						{
						case 'y':
						case 'Y':
							flag = true;
							break;
						case 'n':
						case 'N':
							flag = false;
							break;
						default:
							std::cout << "What?\n";
							continue;
						}

						break;
					}
				}

				else
					std::cout << "Please try again.\n";

			}

			else
			{
				std::cout << "Enter the verticle number you want to start the search from.\n";
				std::cin >> i;
				--i;
				if (i > g.verticles())
					throw std::invalid_argument("Invalid verticle");

				std::cin.clear();
				std::getline(std::cin, buff_to_ignore);

				g.dijkstra<DHeap>(i);
				g.dijkstra<BHeap>(i);
				g.dijkstra<FHeap>(i);

				while (true)
				{
					std::cout << "Do you want to reuse your graph? (yes\\no)\n";
					std::getline(std::cin, s);

					switch (s[0])
					{
					case 'y':
					case 'Y':
						flag = true;
						break;
					case 'n':
					case 'N':
						flag = false;
						break;
					default:
						std::cout << "What?\n";
						continue;
					}
					break;
				}
			}
		}

		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	return 0;
}