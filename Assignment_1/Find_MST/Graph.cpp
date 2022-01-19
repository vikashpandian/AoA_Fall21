#include "Graph.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <set>

Graph::Graph()
{
	nodeCount = 1;
	adjList.resize(nodeCount);
}

Graph::Graph(const int n)
{
	nodeCount = n;
	adjList.resize(nodeCount);
}

void Graph::addEdge(const int a, const int b, const int w)
{
	adjList.at(a).push_back({ b, w });
	adjList.at(b).push_back({ a, w });
}

void Graph::removeEdge(const int a, const int b, const int w)
{
	adjList.at(a).remove({ b,w });
	adjList.at(b).remove({ a,w });
}

int Graph::containsCycle(const int currentNode, const int parent, std::vector<bool>& visited, std::vector<int>& maxEdge)
{
	if (!visited.at(currentNode))
	{
		visited.at(currentNode) = true;

		for (auto& toVisitNodePair : adjList.at(currentNode))
		{
			int toVisitNode = toVisitNodePair.first;
			int nodeWeight = toVisitNodePair.second;
			if (toVisitNode != parent)
			{
				int result = containsCycle(toVisitNode, currentNode, visited, maxEdge);
				if (result >= 0)
				{
					if (nodeWeight > maxEdge.at(weight))
					{
						maxEdge.at(weight) = nodeWeight;
						maxEdge.at(source) = currentNode;
						maxEdge.at(destination) = toVisitNode;
					}
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
		}
	}
	else if (currentNode != parent)
	{
		//for (auto i : cycle) std::cout << i << "\t";
		return currentNode;
	}
	return noCycle;
}

bool Graph::convertToMST()
{
	std::vector<bool> visited(nodeCount, false);
	std::vector<int> maxEdge({ -1,-1,-1 });
	while (containsCycle(0, -1, visited, maxEdge) == complete)
	{
		//for (auto i : maxEdge) std::cout << i << "\t";
		removeEdge(maxEdge[source], maxEdge[destination], maxEdge[weight]);
		std::cout << "\n";
		for (int i = 0; i < adjList.size(); i++)
		{
			std::cout << i << " ->";
			for (auto &j : adjList.at(i)) std::cout << "\t" << j.first /* << "," << j.second*/;
			std::cout << "\n";
		}
		std::fill(visited.begin(), visited.end(), 0);
		maxEdge = { -1,-1,-1 };
	}
	return true;
}

void Graph::printGraph()
{
	for (int i = 0; i < adjList.size(); i++)
	{
		std::cout << "\n" << i << " -> ";
		for (auto& node : adjList.at(i))
		{
			std::cout << node.first << " [" << node.second << "]" << "\t";
		}
	}
	std::cout << "\n";
}

long long int Graph::getTotalWeight()
{
	long long int totalWeight = 0;
	for (int i = 0; i < adjList.size(); i++)
	{
		for (auto& node : adjList.at(i))
		{
			totalWeight += node.second;
		}
	}
	totalWeight /= 2;
	return totalWeight;
}

void generateGraph(int v, Graph& graph)
{
	std::vector<int> nodes(v);
	std::iota(nodes.begin(), nodes.end(), 0);
	random_shuffle(nodes.begin(), nodes.end());
	//for (auto& i : nodes) std::cout << i;
	for (int i = 1; i < v; i++)
	{
		int fromNode = nodes.at(rand() % i);
		graph.addEdge(fromNode, nodes.at(i), i);
	}
	int remainingEdges = rand() % 8 + 1;
	std::set<std::pair<int, int>> extraEdges;
	while (remainingEdges--)
	{
		int s = rand() % v;
		int d = rand() % v;
		while (s == d || extraEdges.count({ s,d }))
		{
			s = rand() % v;
		}
		graph.addEdge(s, d, rand() % 20 + 1);
	}
}