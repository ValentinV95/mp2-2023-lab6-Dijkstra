#pragma once

#include"PriorityQueue.h"

#include<vector>
#include<string>
#include<tuple>
#include<random>
#include<map>
#include<queue>
#include<stack>

using namespace std;

struct rec
{
	size_t v;
	size_t from;
	size_t cost;

	bool operator < (rec a)
	{
		return cost < a.cost;
	}

	bool operator > (rec a)
	{
		return cost > a.cost;
	}

	bool operator == (rec a)
	{
		return cost == a.cost;
	}

	bool operator != (rec a)
	{
		return cost != a.cost;
	}

	bool operator <= (rec a)
	{
		return cost <= a.cost;
	}

	bool operator >= (rec a)
	{
		return cost >= a.cost;
	}
};

class Graph
{
	vector<vector<size_t>> adjMatrix;
	map<string, size_t> indByName;
	map<size_t, string> nameByInd;

	size_t V;
	size_t E;
public:
	Graph(size_t V)
	{
		this->V = V;
		adjMatrix = vector<vector<size_t>>(V);
		for(auto& vec : adjMatrix)
		{
			vec = vector<size_t>(V);
		}
	}

	~Graph() = default;

	size_t getV() const { return V; }

	vector<vector<size_t>>& getMatrix() { return adjMatrix; }

	map<string, size_t>& getIndByName() { return indByName; }

	map<size_t, string>& getNameByInd() { return nameByInd; }

	void generateGraph(size_t E)
	{
		random_device r;
		default_random_engine eng(r());
		uniform_int_distribution<size_t> randInd(0, V-1);
		uniform_int_distribution<size_t> randNum(0, 100);

		for(size_t i = 0; i < V; i ++)
		{
			indByName[string("A") + to_string(i)] = i;
			nameByInd[i] = string("A") + to_string(i);
		}
		vector<size_t> bound;
		bound.push_back(0);
		vector<size_t> unBound;

		for(size_t i = 1; i < V; i++)
		{
			unBound.push_back(i);
		}
		while(!unBound.empty())
		{
			size_t u = randInd(eng) % unBound.size();
			size_t b = randInd(eng) % bound.size();
			size_t num = randNum(eng);
			adjMatrix[unBound[u]][bound[b]] = num;
			adjMatrix[bound[b]][unBound[u]] = num;
			bound.push_back(unBound[u]);
			unBound[u] = unBound[unBound.size()-1];
			unBound.pop_back();
			this->E++;
		}
		while(this->E < E)
		{
			size_t i = randInd(eng);
			size_t j = randInd(eng);
			if(adjMatrix[i][j] == 0 && i!= j)
			{
				size_t num = randNum(eng);
				adjMatrix[i][j] = num;
				adjMatrix[j][i] = num;
				this->E++;
			}
		}
	}

	bool check()
	{
		vector<bool> v(V);
		queue<size_t> q;

		for(size_t i = 0; i < V; i++)
		{
			v[i] = false;
		}
		q.push(0);
		v[0] = true;

		while(!q.empty())
		{
			size_t i = q.front();
			for (size_t j = 0; j < V; j++)
			{
				if (adjMatrix[i][j] != 0)
				{
					if (v[j] == false)
					{
						v[j] = true;
						q.push(j);
					}
				}
			}
			q.pop();
		}
		for (size_t i = 0; i < V; i++)
		{
			if (v[i] == false)
			{
				return false;
			}
		}
		return true;
	}

	void setFKb()
	{
		for (size_t i = 0; i < V; i++)
		{
			cout << "Введите имя вершины " << i+1 << " :";
			string buff;
			cin >> buff;
			indByName[buff] = i;
			nameByInd[i] = buff;
		}
		for (size_t i = 0; i < V; i++)
		{
			int cont = 1;
			cout << "Ввести для вершины " << nameByInd[i] << "?" << endl;
			cout << "1-да, 0-нет" << endl;
			cin >> cont;
			while (cont)
			{
				cout << "Введите вершину, которая связана с " << nameByInd[i] << endl;
				string buff;
				cin >> buff;
				try
				{
					indByName.at(buff);
				}
				catch (out_of_range& ex)
				{
					cout << "В графе нет вершины с именем: " << buff << endl;
					continue;
				}
				cout << "Введите вес пути: ";
				int e = -1;
				cin >> e;
				if(e < 0)
				{
					cout << "Вес пути для графа должен быть положительным" << endl;
					continue;
				}
				adjMatrix[i][indByName[buff]] = e;
				cout << "Продолжить ввод для вершины " << nameByInd[i] << "?" << endl;
				cout << "1-да, 0-нет" << endl;
				cin >> cont;
			}
		}
	}

	friend istream& operator>>(istream& in, Graph& g)
	{
		for (size_t i = 0; i < g.V; i++)
		{
			string buff;
			in >> buff;
			g.indByName[buff] = i;
			g.nameByInd[i] = buff;
		}
		for (size_t i = 0; i < g.V; i++)
		{
			for (size_t j = 0; j < g.V; j++)
			{
				in >> g.adjMatrix[i][j];
			}
		}
		return in;
	}

	friend ostream& operator<<(ostream& out, Graph& g)
	{
		out << "\t";
		for (size_t i = 0; i < g.V; i++)
		{
			out << g.nameByInd[i] << "\t";
		}
		out << "\n";
		for (size_t i = 0; i < g.V; i++)
		{
			out<< g.nameByInd[i] << "\t";
			for (size_t j = 0; j < g.V; j++)
			{
				out << g.adjMatrix[i][j] << "\t";
			}
			out << "\n";
		}
		return out;
	}
};

template<class T>
class Dijkstra
{
	map<size_t, pair<size_t, char>> table;
	vector<size_t> from;
	PriorityQueue<rec>* queue;
	Graph graph;
	size_t rootInd;

	bool stop()
	{
		for (size_t i = 0; i < graph.getV(); i++) 
		{
			if (table[i].second == 0) 
			{
				return false;
			}
		}
		return true;
	}
public:
	Dijkstra(const Graph& gr, PriorityQueue<rec>* q) : queue(q), graph(gr), from(gr.getV()), rootInd(0)
	{
		for(size_t i = 0;i < graph.getV(); i++)
		{
			table[i].first = SIZE_MAX;
			table[i].second = 0;
		}
	}

	~Dijkstra() = default;

	void run(string Vname)
	{
		if(!graph.check())
		{
			throw exception("Graph must be connected!");
		}
		vector<vector<size_t>>& adjMatrix = graph.getMatrix();
		map<string, size_t>& indByName = graph.getIndByName();
		
		rootInd = indByName[Vname];
		size_t ind = indByName[Vname];
		table[ind].first = 0;
		table[ind].second = 1;

		for (size_t j = 0; j < adjMatrix.size(); j++)
		{
			if (adjMatrix[ind][j] != 0 && j != indByName[Vname])
			{
				queue->insert({j,ind, adjMatrix[ind][j]});
			}
		}
		while (!stop()) 
		{
			auto min = queue->getMin();
			ind = min.v;
			table[ind].second = 1;
			for (size_t j = 0; j < adjMatrix.size(); j++)
			{
				if (adjMatrix[ind][j] != 0 && j != rootInd)
				{
					queue->insert({ j,ind, min.cost + adjMatrix[ind][j] });
				}
			}
			if(table[ind].first > min.cost)
			{
				table[ind].first = min.cost;
				from[ind] = min.from;
			}
			queue->extractMin();
		}
		from[rootInd] = rootInd;
	}

	string getWay(string to)
	{
		map<string, size_t>& indByName = graph.getIndByName();
		map<size_t, string>& nameByInd = graph.getNameByInd();

		size_t ind = indByName[to];
		stack<string> way;
		while(ind != rootInd)
		{
			way.push(nameByInd[from[ind]]);
			ind = from[ind];
		}
		string res;

		while(!way.empty())
		{
			res += way.top();
			res += string("->");
			way.pop();
		}
		res += to;
		return res;
	}

	void showTable()
	{
		map<size_t, string>& nameByInd = graph.getNameByInd();

		for(size_t i = 0; i < nameByInd.size(); i++)
		{
			cout << nameByInd[i] << "\t";
		}
		cout << "\n";
		for (size_t i = 0; i < graph.getV(); i++)
		{
			if(table[i].first == SIZE_MAX)
			{
				cout << "None" << "\t";
			}
			else 
			{
				cout << table[i].first << "\t";
			}
		}
		cout << "\n\n";
	}
};