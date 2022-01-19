#include "Graph.h"
#include <iostream>
#include <set>

Graph::Graph()
{
	nodeCount = 1;
	adjList.resize(nodeCount);
}

Graph::Graph(int n)
{
	nodeCount = n;
	adjList.resize(nodeCount);
}

void Graph::addEdge(int a, int b)
{
	adjList.at(a).push_back(b);
	adjList.at(b).push_back(a);
}

int Graph::containsCycleRecursive(const int currentNode, const int parent, std::vector<bool>& visited, std::vector<int>& cycle)
{
	visited.at(currentNode) = true;
	for (auto& toVisitNode : adjList.at(currentNode))
	{
		if (!visited.at(toVisitNode))
		{
			int result = containsCycleRecursive(toVisitNode, currentNode, visited, cycle);
			if (result >= 0)
			{
				cycle.push_back(toVisitNode);
				if (currentNode != result)
				{
					return result;
				}
				return complete;
			}
			else if (result == complete)
			{
				return complete;
			}
		}
		else if (toVisitNode != parent)
		{
			//for (auto i : cycle) std::cout << i << "\t";
			cycle.push_back(toVisitNode);
			return toVisitNode;
		}
	}
	return noCycle;
}

bool Graph::containsCycle(std::vector<int>& cycle)
{
	std::vector<bool> visited(nodeCount, false);
	for (int i = 0; i < adjList.size(); i++)
	{
		if (!visited[i])
		{
			if (containsCycleRecursive(i, -1, visited, cycle) == complete)
			{
				/*std::cout << "\n";
				for (auto i : cycle) std::cout << i << "\t";
				std::cout << "\n";*/
				return true;
			}
		}
	}
}

void Graph::printGraph()
{
	for (int i = 0; i < adjList.size(); i++)
	{
		std::cout << "\n" << i << " -> ";
		for (auto& node : adjList.at(i))
		{
			std::cout << node << "\t";
		}
	}
	std::cout << "\n";
}

void generateGraph(int v, Graph& graph)
{
	std::vector<std::set<int>> container(v);
	for (int i = 0; i < v; i++)
	{
		int count = (rand() % 2) + 1;
		while (count--)
		{
			int val = rand() % v;
			while (container.at(i).count(val) || i == val)
			{
				val = rand() % v;
			}
			container.at(i).insert(val);
			container.at(val).insert(i);
			graph.addEdge(i, val);
		}
	}
}