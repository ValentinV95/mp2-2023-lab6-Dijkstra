#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <chrono>
#include "Graph.h"
#include "BinHeap.h"
#include "FibHeap.h"
#include "dheap.h"
#include "fstream"

using namespace std;

Graph::minpath::minpath(int ind_, double dist) {
	ind=ind_;
	distance = dist;
}

bool Graph::minpath::operator==(const minpath& p) const noexcept { return distance == p.distance; };

bool Graph::minpath::operator>=(const minpath& p) const noexcept { return distance >= p.distance; };

bool Graph::minpath::operator<=(const minpath& p) const noexcept { return distance <= p.distance; };

bool Graph::minpath::operator>(const minpath& p) const noexcept { return distance > p.distance; };

bool Graph::minpath::operator<(const minpath& p) const noexcept { return distance < p.distance; };

Graph::Graph() {
	paths = nullptr;
}

Graph::~Graph() {
	clear();
}

void Graph::clear() {
	graph.clear();
	names.clear();
	delete[] paths;
	paths = nullptr;
}


void Graph::addV(const string& str) {
	graph.push_back({});
	names.push_back(str);
	for (int i = 0; i < graph.size()-1; i++) {
		graph[i].push_back(INFINITY);
		graph[graph.size()-1].push_back(INFINITY);
	}
	graph[graph.size() - 1].push_back(0);
	delete[] paths;
	paths = nullptr;
};


void Graph::addE(const string& v1, const string& v2, double weight) {
	if (v1 == v2) throw invalid_argument("Can't create loops");
	int ind1=-1, ind2=-1;
	for (int i = 0; i < names.size() && (ind1==-1 || ind2==-1); i++) {
		if (names[i] == v1) ind1 = i;
		if (names[i] == v2) ind2 = i;
	}
	if (ind1 == -1) throw invalid_argument("Vertex with name " + v1 + " doesn't exist");
	if (ind2 == -1) throw invalid_argument("Vertex with name " + v2 + " doesn't exist");
	if (graph[ind1][ind2] != INFINITY) throw invalid_argument("This edge already exists");
	graph[ind1][ind2] = weight;
	graph[ind2][ind1] = weight;
	delete[] paths;
	paths = nullptr;
}


void Graph::delV(const string& str) {
	int ind;
	int sz = names.size() - 1;
	for (ind = 0; ind < names.size() && names[ind] != str; ind++);
	if (ind < names.size()) {
		names[ind] = names[sz];
		names.pop_back();
		graph[ind] = graph[sz];
		graph.pop_back();
		for (int i = 0; i < sz; i++) {
			graph[i][ind] = graph[i][sz];
			graph[i].pop_back();
		}
		delete[] paths;
		paths = nullptr;
	}
}


void Graph::delE(const string& v1, const string& v2) {
	int ind1 = -1, ind2 = -1;
	for (int i = 0; i < names.size() && (ind1 == -1 || ind2 == -1); i++) {
		if (names[i] == v1) ind1 = i;
		if (names[i] == v2) ind2 = i;
	}
	if (ind1 == -1 || ind2 == -1) return;
	if (graph[ind1][ind2] != INFINITY) {
		graph[ind1][ind2] = INFINITY;
		graph[ind2][ind1] = INFINITY;
		delete[] paths;
		paths = nullptr;
	}
}


bool Graph::check_Dijkstra() const noexcept {
	if (paths) return true;
	for (int i = 0; i<graph.size(); i++) 
		for (int j = i+1; j < graph.size(); j++)
		{
			if (graph[i][j] < 0) return false;
		}
	return true;
}


void Graph::generate_ost_tree(const int countV, int& countE) {
	if (countE < countV - 1) throw invalid_argument("Can't generate connected graph wtih such count of edges");
	addV(to_string(0));
	int ind;
	double weight;
	for (int i = 1; i < countV; i++) {
		addV(to_string(i));
		ind = rand() % i;
		weight=double(rand()) / RAND_MAX * 100;
		addE(to_string(ind), to_string(i), weight);
	}
	countE -= (countV - 1);
}


void Graph::rnd(int countV, double percentE) {
	if (percentE > 100 || percentE < 0) throw invalid_argument("Percent cant be greater than 100or lower than 0");
	if (countV < 0) throw invalid_argument("Count of vertices must be greater than 0");
	clear();
	if (countV == 0) return;
	int countE = floor(countV * percentE / 200 * (countV - 1));
	generate_ost_tree(countV, countE);
	int ind1, ind2;
	double weight;
	for (int i = 0; i < countE; i++) {
	ind1 = rand() % countV;
	ind2 = rand() % countV;
	if (graph[ind1][ind2] != INFINITY || ind1==ind2) {
		i--;
		continue;
	}
	else {
		weight = double(rand()) / RAND_MAX * 100;
		graph[ind1][ind2] = weight;
		graph[ind2][ind1] = weight;
	  }
	}
}


void Graph::Dijkstra(const string& str) {
	fstream out;
	if (!check_Dijkstra()) throw logic_error("You cant use this algorithm on this graph");
	int ind;
	for (ind = 0; ind < names.size() && names[ind] != str; ind++); //search index of a vertev with a given name in names vector
	if (ind == names.size()) throw std::logic_error("Tere are no such vertex in this graph");
	if (paths && paths[ind] == 0) return;
	//
	auto start{ std::chrono::steady_clock::now() };
	work_with_heap<DHeap<minpath>>(ind);
	auto end{ std::chrono::steady_clock::now() };
	std::chrono::duration<double> elapsed_seconds{ end - start };
	std::cout << "DHeap time: " << elapsed_seconds.count() << "\n";
	//
	start = { std::chrono::steady_clock::now() };
	work_with_heap<BinHeap<minpath>>(ind);
	end = { std::chrono::steady_clock::now() };
	elapsed_seconds = { end - start };
	std::cout << "BinHeap time: " << elapsed_seconds.count() << "\n";
	//
	start = { std::chrono::steady_clock::now() };
	work_with_heap<FibHeap<minpath>>(ind);
	end = { std::chrono::steady_clock::now() };
	elapsed_seconds = { end - start };
	std::cout << "FibHeap time: " << elapsed_seconds.count() << "\n"; 
}


double Graph::path(const std::string& end) {
	if (paths) {
		int ind;
		for (ind = 0; ind < names.size() && names[ind] != end; ind++);
		if (ind == names.size()) throw invalid_argument("There is no such vertex in this graph");
		return paths[ind];
	}
	else throw logic_error("Dijkstra algorithm wasn't used at this garph");
}

bool Graph::check_connected() const {
	if (paths) {
		for (int i = 0; i < names.size(); i++) if (paths[i] == INFINITY) return false;
		return true;
	}
	if (names.size() < 2) return true;
	bool* mas = new bool[names.size()] {false};
	int tmp;
	std::stack<int> S;
	S.push(0);
	while (!S.empty()) {
		tmp = S.top();
		S.pop();
		for (int i = 1; i < names.size(); i++) 
			if (graph[tmp][i] != INFINITY) {
			if (!mas[i]) {
				mas[i] = true;
				S.push(i);
			};
		};
	}
	for (int i = 1; i < names.size(); i++) if (!mas[i]) return false;
	return true;
}


void Graph::look() {
	bool fl;
	if (names.size() == 1) std::cout << "The only vertex: " << names[0] << "\n";
	else if (names.size() > 0) {
		for (int i = 0; i < names.size(); i++) {
			fl = true;
			cout << names[i] << " connected with:\n";
			for (int j = 0; j < names.size(); j++) {
				if (i != j && graph[i][j] != INFINITY) {
					cout << "\t" << names[j] << ", distance between them: " << graph[i][j] << "\n";
					fl = false;
				}
			}
			if (fl) cout << " not connected to any vertex\n";
		}
	}
	else cout << "No elements in graph\n";
}


void Graph::GraphViz(const string& name) {
	ofstream out;
	bool fl;
	out.open("..\\..\\..\\..\\GraphViz\\graph.gv");
	out << "Graph " + name + " {\n";
	if (names.size() > 0) {
		for (int i = 0; i < names.size(); i++) {
			fl = true;
			for (int j = i + 1; j < names.size(); j++) {
				if (graph[i][j] != INFINITY) {
					out << "\t" << names[i] << "--" << names[j] << " [label=\"" << graph[i][j] << "\"];\n";
					fl = false;
				}
			}
			if (fl) out << "\t" << names[i] << ";\n";
		}
	}
	out << "}";
	out.close();
	std::string str = "..\\..\\..\\..\\GraphViz\\GraphViz\\bin\\dot -Tpng ..\\..\\..\\..\\GraphViz\\graph.gv -o ..\\..\\..\\..\\GraphViz\\GraphDrawings\\" + name + ".png";
	const char* chr1 = &(str[0]);
	system(chr1);
	str = "..\\..\\..\\..\\GraphViz\\GraphDrawings\\" + name + ".png";
	const char* chr2 = &(str[0]);
	system(chr2);
}