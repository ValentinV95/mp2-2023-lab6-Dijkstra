#pragma once
#include "Dijkstra.hpp"

using namespace std;

Graph::Graph() {}
void Graph::createCompliteGraph()
{
	vector<size_t> vertecs(vertexCount);

	for (int i = 0; i < vertexCount; i++)
		vertecs[i] = i;

	random_shuffle(vertecs.begin(), vertecs.end());
	vector<size_t> linkedVertecs = { vertecs[0] };

	random_device r;

	size_t someLinkedVertecsInd;
	for (int i = 1; i < vertecs.size(); i++)
	{
		someLinkedVertecsInd = r() % linkedVertecs.size();
		addEdge(linkedVertecs[someLinkedVertecsInd], vertecs[i], r() % MAX_RANDOM_WAY_COST + 1);
		linkedVertecs.push_back(vertecs[i]);
	}
}

Graph::Graph(const Graph& graph)
{
	adjMatrix = graph.adjMatrix;
	edgeCount = graph.edgeCount;
	vertexCount = graph.vertexCount;
}

Graph::Graph(size_t vertexCount, size_t edgeCount) :vertexCount(vertexCount), edgeCount(edgeCount), adjMatrix(vertexCount)
{
	if (edgeCount < (vertexCount - 1))
		throw exception("Not enough edge to create connected graph");

	if(edgeCount > (vertexCount*(vertexCount-1)/2))
		throw exception("To large edge count");

	for (vector<size_t>& vec : adjMatrix)
		vec.resize(vertexCount, INF);

	for (int i = 0; i < vertexCount; i++)
		adjMatrix[i][i] = 0;

	createCompliteGraph();

	size_t currentEdgeCount = vertexCount - 1;

	random_device r;
	size_t v1, v2;

	while (currentEdgeCount <= edgeCount)
	{
		v1 = r() % vertexCount;
		v2 = r() % vertexCount;

		if (v1 != v2 && getCost(v1, v2) == INF)
		{
			addEdge(v1, v2, r() % MAX_RANDOM_WAY_COST + 1);
			currentEdgeCount++;
		}
	}
}

Graph::Graph(size_t vertexCount):vertexCount(vertexCount), edgeCount(edgeCount), adjMatrix(vertexCount)
{
	for (vector<size_t>& vec : adjMatrix)
	{
		vec.resize(vertexCount, 0);
	}

	for (int i = 0; i < vertexCount; i++)
	{
		for (size_t j = 0; j < vertexCount; j++)
		{
			if (i != j)
				adjMatrix[i][j] = INF;
		}
	}
}

void Graph::addEdge(const size_t& v1, const size_t& v2, size_t weight)
{
	if (v1 == v2)
		throw exception("It is impossible to set the price of the path from the vertex to itself");

	adjMatrix[v1][v2] = weight;
	adjMatrix[v2][v1] = weight;
}

size_t Graph::getCost(const size_t& v1, const size_t& v2) const
{
	return adjMatrix[v1][v2];
}

vector<pair<size_t, size_t>> Graph::getSiblings(const size_t& v)  const
{
	vector<pair<size_t, size_t>> res;

	for (size_t i = 0; i < vertexCount; i++)
	{
		if (adjMatrix[v][i] != INF && i != v)
			res.push_back(make_pair(i, adjMatrix[v][i]));
	}

	return res;
}

void Graph::printTable()  const
{
	size_t max = 0;
	size_t padding;

	for (int i = 0; i < vertexCount; i++)
	{
		for (size_t j = 0; j < vertexCount; j++)
		{
			if (adjMatrix[i][j] != INF && max < adjMatrix[i][j])
				max = adjMatrix[i][j];
		}
	}

	if (trunc(log10(max)) + 1 > trunc(log10(vertexCount)) + 1)
	{
		padding = trunc(log10(max)) + 2;
	}
	else
	{
		padding = trunc(log10(vertexCount)) + 2;
	}

	cout << setw(padding) << " " <<" ";
	for (size_t j = 0; j < vertexCount; j++)
		cout << setw(padding) << j << "|";
	cout << endl << endl;

	for (int i = 0; i < vertexCount; i++)
	{
		cout << setw(padding) <<  i<< " ";

		for (size_t j = 0; j < vertexCount; j++)
			if (adjMatrix[i][j] != INF)
				cout << setw(padding) << adjMatrix[i][j] << "|";
			else
				cout << setw(padding) <<"n" << "|";
		cout << setw(padding) << endl;
	}
}

size_t Graph::getVertexCount() const { return vertexCount; }

ostream& operator << (ostream& out, const Graph& g)
{
	for (size_t i = 0; i < g.vertexCount; i++)
	{
		for (size_t j = i + 1; j < g.vertexCount; j++)
		{
			if (g.adjMatrix[i][j] != INF)
			{
				cout << i << " -- " << j << ", " << g.adjMatrix[i][j] << endl;
			}
		}
		cout << endl;
	}


	return out;
}

//GRAPH_NODE
GraphNode::GraphNode(size_t weight, size_t  from, size_t current) :weight(weight), from(from), current(current) {}
GraphNode::GraphNode() :weight(0), from(0), current(0) {}

bool GraphNode::operator < (const GraphNode& node) const
{
	return weight < node.weight;
}

bool GraphNode::operator > (const GraphNode& node) const
{
	return weight > node.weight;
}

bool GraphNode::operator == (const GraphNode& node) const
{
	return weight == node.weight;
}

bool GraphNode::operator != (const GraphNode& node) const
{
	return weight != node.weight;
}

bool GraphNode::operator <= (const GraphNode& node) const
{
	return weight <= node.weight;
}

bool GraphNode::operator >= (const GraphNode& node) const
{
	return weight >= node.weight;
}

//DEIJKSTRA
Dijkstra::Dijkstra(const Graph& g, size_t start, QueueType queueType) :g(g), start(start), queueType(queueType)
{
	switch (queueType)
	{
	case DHeap:
		queue = new TDHeap<GraphNode>;
		break;
	case RBTree:
		queue = new TRbTree<GraphNode>;
		break;
	case FibonacciHep:
		queue = new TBinomialTree<GraphNode>;
		break;
	default:
		throw exception("Uncnown queue type");
	}

	setStart(start);
}

void Dijkstra::setStart(const size_t& v)
{
	S.clear();

	graphChek();

	start = v;

	vector<pair<size_t, size_t>> siblings;

	size_t currentVertex = start;
	S.insert(make_pair(currentVertex, GraphNode(0, currentVertex, currentVertex)));
	IPriorityQueue<GraphNode>* D = queue;

	while (S.size() < g.getVertexCount())
	{
		siblings = g.getSiblings(currentVertex);

		for (int i = 0; i < siblings.size(); i++)
		{
			if (S.count(siblings[i].first) == 0)
			{
				D->insert(GraphNode(g.getCost(siblings[i].first, currentVertex) + S[currentVertex].weight, currentVertex, siblings[i].first));
			}
		}

		if (S.count(D->getMin().current) == 0 || S[D->getMin().current].weight > D->getMin().weight)
		{
			S[D->getMin().current] = D->getMin();
			currentVertex = D->getMin().current;

			while (!D->isEmpty() && S.count(D->getMin().current) != 0)
			{
				D->extractMin();
			}
		}
	}

	while (!D->isEmpty())
	{
		D->extractMin();
	}
}

stack<GraphNode> Dijkstra::getWay(size_t v)
{
	if (S.empty())
		throw exception("Start hav not been seted");

	if (v >= g.getVertexCount())
		throw exception("Uncorrect vertex name");

	stack<GraphNode> way;
	way.push(S[v]);

	while (way.top().current != start)
	{
		size_t from = way.top().from;
		way.push(S[from]);
	}

	return way;
}

Dijkstra::~Dijkstra() { delete queue; }

void Dijkstra::graphChek()
{
	stack<size_t> vertexes;
	map<size_t,size_t> visitedVertexes;
	vector<pair<size_t, size_t>> siblings = g.getSiblings(0);

	for (int i=0;i<siblings.size();i++)
	{
		vertexes.push(siblings[i].first);
	}

	while (!vertexes.empty())
	{
		if (visitedVertexes.count(vertexes.top()) == 0)
			visitedVertexes.insert(make_pair(vertexes.top(),0));

		siblings = g.getSiblings(vertexes.top());

		for (int i = 0; i < siblings.size(); i++)
			vertexes.push(siblings[i].first);

		while(!vertexes.empty() && visitedVertexes.count(vertexes.top()) != 0)
			vertexes.pop();
	}

	if (visitedVertexes.size() < g.getVertexCount())
		throw invalid_argument("The graph is not connected");
}



