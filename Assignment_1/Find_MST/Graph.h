#pragma once

#include <vector>
#include <list>
#include <stack>
#include <tuple>

enum Status
{
	complete = -1,
	noCycle = -2
};

enum Edge
{
	weight = 0,
	source = 1,
	destination = 2
};

class Graph
{
	int nodeCount;
	std::vector <std::list <std::pair<int, int>>> adjList;
	void removeEdge(const int a, const int b, const int w);

public:
	Graph();
	Graph(const int n);
	void addEdge(const int a, const int b, const int w);
	int containsCycle(const int currentNode, const int parent, std::vector<bool>& visited, std::vector<int>& maxEdge);
	bool convertToMST();
	void printGraph();
	long long int getTotalWeight();
};

void generateGraph(int v, Graph& graph);