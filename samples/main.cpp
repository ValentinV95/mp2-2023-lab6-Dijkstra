#include <iostream>
#include <conio.h>

#include "rbtree.h"
#include "dheap.h"
#include "bheap.h"
#include "graph.h"

#define d 3 // ������� d-����

using std::cout;
using std::endl;

template <typename type>
void input(type& buffer)
{
	std::cin >> buffer;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void do_actions(WeightedGraph& g, ShortestPaths& sp)
{
	enum actions {
		OUTPUT_GRAPH = 1,
		GET_SHORTEST_PATH,
		GET_TOTAL_COST,
		EXIT
	};
	int select = 0;
	while (true)
	{
		cout << "\n�������� ��������: " << endl;
		cout << " 1 - ������� ���� � ���� ������� ���������" << endl;
		cout << " 2 - �������� ���������� ���� � �������" << endl;
		cout << " 3 - �������� ����� ��������� ���� �� �������" << endl;
		cout << " 4 - �����" << endl;
		cout << "��������: ";
		input(select);
		if (select == EXIT) return;

		switch (select)
		{
		case OUTPUT_GRAPH:
		{
			cout << endl;
			g.print();
			break;
		}
		case GET_SHORTEST_PATH:
		{
			int vertex;
			cout << "\n������� �������: ";
			input(vertex);
			try
			{
				cout << "\n���������� ����: ";
				cout << sp.get_shortest_path(vertex) << endl;
			}
			catch (const std::exception& except)
			{
				cout << "������: " << except.what() << endl;
			}
			break;
		}
		case GET_TOTAL_COST:
		{
			int vertex;
			cout << "\n������� �������: ";
			input(vertex);
			try
			{
				cout << "\n����� ����������: ";
				cout << sp.get_total_cost(vertex) << endl;
			}
			catch (const std::exception& except)
			{
				cout << "������: " << except.what() << endl;
			}
			break;
		}
		default:
		{
			cout << "������: ������� ����������� ����� ��� ������" << endl;
			return;
		}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int vertices;
	int edges;

	cout << "\n���������� ������ �����: ";
	input(vertices);
	if (vertices <= 0)
	{
		cout << "\n������: ������������ ���������� ������";
		return 1;
	}
	cout << "\n���������� ����� �����: ";
	input(edges);
	if (edges < vertices - 1 || edges > vertices * (vertices - 1) / 2)
	{
		cout << "\n������: ������������ ���������� �����";
		return 1;
	}

	WeightedGraph G(vertices, edges);

	int select = 0;
	cout << "�������� ������ ���������� �����: " << endl;
	cout << " 1 - ������ ����" << endl;
	cout << " 2 - ��������� ����" << endl;
	cout << "�����: ";
	input(select);

	if (select == 1) // ������ ����
	{
		cout << "\n���������� �������� ������� ������: [0;" << vertices << ")" << endl;
		for (int i = 0; i < edges; i++)
		{
			int enter_departure;
			int enter_destination;
			int enter_weight;
			cout << "\n������� ����� ������� ������: ";
			input(enter_departure);
			if (enter_departure < 0 || enter_departure >= vertices)
			{
				cout << "������: " << "������������ ����� �������" << endl;
				return 1;
			}
			cout << "\n������� ����� �������� �������: ";
			input(enter_destination);
			if (enter_destination < 0 || enter_destination >= vertices)
			{
				cout << "������: " << "������������ ����� �������" << endl;
				return 1;
			}
			cout << "\n������� ������: ";
			input(enter_weight);

			try
			{
				G.add_edge(enter_departure, enter_destination, enter_weight);
			}
			catch (const std::exception& except)
			{
				cout << "������: " << except.what() << endl;
				return 1;
			}
		}
	}
	else if (select == 2) // random filling
	{
		G.random_fill();
	}
	else
	{
		cout << "������: �������� ����� ������ ����������" << endl;
		return 1;
	}

	enum priority_queue {
		SEARCH_TREE = 1,
		DHEAP,
		BINOMUAL_HEAP,
	};
	if (G.is_connected())
	{
		cout << "\n���� ������!" << endl;
		int start;
		cout << "\n������� ��������� ������� ��� ��������� ��������: ";
		input(start);

		if (start < 0 || start >= vertices)
		{
			cout << "������: ������������ ��������� �������" << endl;
			return 1;
		}

		cout << "\n�������� ������������ ������� ��� ��������� ��������" << endl;
		cout << " 1 - �������� ������ ������ (������-������ ������)" << endl;
		cout << " 2 - ������� ����" << endl;
		cout << " 3 - ������������ ����" << endl;
		cout << "�����: ";
		input(select);

		switch (select)
		{
		case SEARCH_TREE:
		{
			RedBlackTreeQueue<size_t, size_t> Q_tree;
			ShortestPaths SP(start, G, Q_tree);
			do_actions(G, SP);
			break;
		}
		case DHEAP:
		{
			DHeapQueue<d, size_t, size_t> Q_Dheap(vertices * edges);
			ShortestPaths SP(start, G, Q_Dheap);
			do_actions(G, SP);
			break;
		}
		case BINOMUAL_HEAP:
		{
			BinomialHeapQueue<size_t, size_t> Q_binheap;
			ShortestPaths SP(start, G, Q_binheap);
			do_actions(G, SP);
			break;
		}
		default:
		{
			cout << "������: ������������ ����� ������������ �������" << endl;
			return 1;
		}
		}
	}
	else
	{
		cout << "������: ���� �� ��������" << endl;
		return 1;
	}
	_getch();
	return 0;
}