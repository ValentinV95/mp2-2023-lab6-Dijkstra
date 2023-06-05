// sample.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include "../include/graph.h"
#include "../include/queue.h"
#include "../include/AVL_Tree.h"
#include "../include/D-heap.h"
#include "../include/binomial-heap.h"

void AlgD(AlgDijkstra& D, Graph& G)
{
    while (true)
    {
        int select;
        std::cout << "Enter action:\n1 - print cost and path choose vertex,\n2 - print matrix of graph,\n3 - exit" << std::endl;
        std::cin >> select;
        if (select == 1)
        {
            int numV;
            std::cout << "enter number vertex:" << std::endl;
            std::cin >> numV;
            D.min_cost_path_vertex(numV);
        }
        else if (select == 2)
        {
            G.show_Graph();
        }
        else
        {
            exit(0);
        }
        std::cout << "\n";
    }
}

int main()
{
    int select, countV, countE, start_vertex;
    std::cout << "ALGHORITM DIJKSTRA" << std::endl;
    std::cout << "enter action:\n1 - user generate graph,\n2 - random generate graph" << std::endl;
    std::cin >> select;
    std::cout << "enter count vertex:" << std::endl;
    std::cin >> countV;
    std::cout << "enter count edge:(range: " << countV - 1 << " to " << (countV*(countV-1)) / 2 << ")" << std::endl;
    std::cin >> countE;
    std::cout << "enter number of start vertex:" << std::endl;
    std::cin >> start_vertex;
    Graph G(countV, countE);
    switch (select)
    {
    case 1:
        G.User_generate();
        break;
    case 2:
        G.Random_generate();
        break;
    default:
        break;
    }

    int choose;
    std::cout << "choose structure for queue:\n1 - AVLTree,\n2 - DHeap,\n3 - Binomial Heap" << std::endl;
    std::cin >> choose;
    AVL_Tree<size_t, size_t> structure_AVL;
    DHeap<size_t, size_t, 2> structure_DH;
    BinomHeap<size_t, size_t> structure_BH;

    AlgDijkstra D1(G, &structure_AVL, start_vertex);
    AlgDijkstra D2(G, &structure_DH, start_vertex);
    //AlgDijkstra D3(G, &structure_BH, start_vertex);
    switch (choose)
    {
    case 1:
        AlgD(D1, G);
        break;
    case 2:
        AlgD(D2, G);
        break;
    case 3:
        //AlgD(D3, G);
        break;
    default:
        break;
    }

    /*Graph A(4, 4);

    A.Random_generate();

    A.show_Graph();
    
    AVL_Tree<size_t, size_t> structure_AVL;

    DHeap<size_t, size_t, 2> structure_DH;

    BinomHeap<size_t, size_t> structure_BH;

    AlgDijkstra D(A, &structure_BH, 0);

    std::cout << "\n" << D.min_cost_path_vertex(2) << std::endl;*/
}
