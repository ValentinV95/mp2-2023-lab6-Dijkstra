#include "Graph.h"
#include <string>

using namespace std;

int main() {
	int choose;
	string str1,str2;
	Graph G;
	do {
		try {
			cout << "Choose your action:\n";
			cout << "\t1)randomly generate connected graph\n";
			cout << "\t2)add new vertex to graph\n";
			cout << "\t3)remove vertex from graph\n";
			cout << "\t4)add new edge to graph\n";
			cout << "\t5)remove edge from graph\n";
			cout << "\t6)checks the graph for connectivity\n";
			cout << "\t7)checks the graph against the criteria of Dijkstra's algorithm\n";
			cout << "\t8)run Dijkstra's algorithm\n";
			cout << "\t9)find the shortest path between vertices in a graph\n";
			cout << "\t10)clear graph\n";
			cout << "\t11)look at graph\n";
			cout << "\t12)draw graph\n";
			cout << "\t0)to end work with program\n";
			cin >> choose;
			switch (choose) {
			case(1):
				system("cls");
				int V;
				double E;
				cout << "Enter the desired number of vertices(>=0) in the graph" <<
					" and the percentage(between 0 and 100) of the maximum number of edges in this graph\n";
				cin >> V >> E;
				G.rnd(V, E);
				system("cls");
				break;
			case(2):
				system("cls");
				cout << "Enter the name of new vertex\n";
				cin >> str1;
				G.addV(str1);
				system("cls");
				break;
			case(3):
				system("cls");
				cout << "Enter the name of the vertex you want to delete\n";
				cin >> str1;
				G.delV(str1);
				system("cls");
				break;
			case(4):
				system("cls");
				cout << "Enter the names of the vertices between which you want to add an edge and the future weight of this edge\n";
				cin >> str1 >> str2 >> E;
				G.addE(str1, str2, E);
				system("cls");
				break;
			case(5):
				system("cls");
				cout << "Enter the names of the vertices between which you want to delete an edge\n";
				cin >> str1 >> str2;
				G.delE(str1, str2);
				system("cls");
				break;
			case(6):
				system("cls");
				if (G.check_connected()) cout << "This graph is connected\n";
				else cout << "This graph isn't connected\n";
				break;
			case(7):
				system("cls");
				if (G.check_Dijkstra()) cout << "You can run Dijkstra's algorithm on this graph\n";
				else cout << "You can't run Dijkstra's algorithm on this graph\n";
				break;
			case(8):
				system("cls");
				cout << "Enter name of start vertex\n";
				cin >> str1;
				system("cls");
				G.Dijkstra(str1);
				break;
			case(9):
				system("cls");
				cout << "Enter the names of the vertices between which you want to fin the minimum distance\n";
				cin >> str1 >> str2;
				system("cls");
				try {
					if (G.path(str1) != 0 && G.path(str2) != 0)
						G.Dijkstra(str1);
					cout << "Shortest path beween " << str1 << " and " << str2 << " : " << G.path(str2) << "\n";
				}
				catch (logic_error& l) {
					G.Dijkstra(str1);
					cout << "Shortest path beween " << str1 << " and " << str2 << " : " << G.path(str2) << "\n";
				}
				break;
			case(10):
				system("cls");
				G.clear();
				break;
			case(11):
				system("cls");
				G.look();
				break;
			case(12):
				system("cls");
				cout << "Enter a name for this graph\n";
				cin >> str1;
				G.GraphViz(str1);
				system("cls");
				break;
			}
		}
		catch (std::exception& e) {
			system("cls");
			std::cout << e.what() << "\n\n";
		}
	} while (choose);
}