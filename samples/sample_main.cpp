#include"TDHeap.h"
#include"TRBtree.h"
#include"TBinomialHeap.h"
#include"Dijksta.h"

#include<locale>

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "|������������ ��������� ���������, ������������� ������ ��������� ������ � �������� ������������ �������|" << endl
		<< "� ������ ���������� ������������ �������� ��������� ������ ��� ������������ �������" << endl
		<< "����� ������������ ���� ��� ��������� ���������� �����" << endl
		<< "������ ������������� ����� ������������ ��������� ��� �������, ��� ������� ����� ������� ���������� ����" << endl
		<< endl <<"����������: \n1)���� ������ ���� �������" << endl
		<< "2)���� ����� � ���������� ������������ � ��������� �������:" << endl
		<< "��������������� �������� ����� ������, � ����� ������� ��������� - ����������� (�� �������)" << "\n\n";
	
	cout << "�������� ��������� ������ ��� ������������ �������:" << endl
		<< "1 - d-heap, ��� � �������� d ����� 3." << endl
		<< "2 - ������������ ����" << endl
		<< "3 - ������ ������ ������" << "\n\n";

	PriorityQueue<rec>* queue = nullptr;

	int choose = 0;
	bool cont = true;
	
	while (cont) 
	{
		cin >> choose;
		cont = false;
		switch (choose)
		{
		case 1:
			queue = new TDHeap<rec,3>;
			break;
		case 2:
			queue = new TBinomialHeap<rec>;
			break;
		case 3:
			queue = new TRBTree<rec>;
			break;
		default:
			cout << "�������� ����!" << endl;
			cont = true;
			break;
		}
	}

	int V = 0;
	do 
	{
		cout << "������� ������ �����(����� ������)" << endl;
		cin >> V;
	} while (V < 2);

	Graph graph(V);

	cout << "�������� ������ ������� �����:" << endl
		<< "1 - ������������� �������������" << endl
		<< "2 - ������ � ����������" << endl;
	cin >> choose;
	switch (choose)
	{
	case 1:
		int E;
		cout << "������� ������� ��������� �����" << endl;
		cin >> E;
		graph.generateGraph(((V * (V - 1) / 2) * E) / 100);
		break;
	case 2:
		graph.setFKb();
		break;
	default:
		cout << "�������� ����!" << endl;
		break;
	}
	cout << "������� ��������� ��� ������ �����" << endl;
	cout << graph;
	cout << "\n\n" << "������� ��� �������, ���� ��� ������� ������ �����:" << endl;
	string vName;
	cin >> vName;

	cout << "������� � ������ �� ������:" << "\n\n";
	Dijkstra<size_t> dijkstra(graph, queue);
	try 
	{
		dijkstra.run(vName);
	}
	catch(exception& ex)
	{
		cout << ex.what() << endl;
		exit(-1);
	}
	dijkstra.showTable();

	while (true) 
	{
		cout << "������� 1, ����� ������ ���� �� �������" << endl
			<< "������� 2, ����� ��������� ������ � ������" << endl;

		cin >> choose;
		string to;
		switch (choose)
		{
		case 1:
			cout << "������� �������, ���� �� ������� ������ �����: ";
			cin >> to;
			cout << endl<<"���� �� �������: " << endl << dijkstra.getWay(to) << "\n\n";
			break;
		case 2:
			exit(0);
			break;
		default:
			cout << "�������� ����!" << endl;
			break;
		}
	}
	delete queue;
}