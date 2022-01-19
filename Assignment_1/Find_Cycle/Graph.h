#pragma once

#include <vector>
#include <list>
#include <stack>

enum Status
{
	complete = -1,
	noCycle = -2
};

class Graph
{
	int nodeCount;
	std::vector <std::list <int>> adjList;
	//bool containsCycle(std::vector<bool>& visited, std::stack<std::pair<int, int>>& toTraverse, std::vector<int>& cycle);
	int containsCycleRecursive(const int currentNode, const int parent, std::vector<bool>& visited, std::vector<int>& cycle);

public:
	Graph();
	Graph(int n);
	void addEdge(const int a, const int b);
	bool containsCycle(std::vector<int>& cycle);
	void printGraph();
};

void generateGraph(int v, Graph& graph);
