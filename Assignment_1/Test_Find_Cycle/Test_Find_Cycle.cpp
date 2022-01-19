#include "CppUnitTest.h"
#include "../Find_Cycle/Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFindCycle
{
	TEST_CLASS(TestFindCycle)
	{
	public:
		
		TEST_METHOD(TestDisconnectedGraph)
		{
            Graph graph(9);
            graph.addEdge(0, 2);
            graph.addEdge(1, 0);
            graph.addEdge(2, 4);
            graph.addEdge(3, 1);
            graph.addEdge(5, 6);
            graph.addEdge(6, 7);
            graph.addEdge(7, 5);
            std::vector<int> cycle;
            bool result = graph.containsCycle(cycle);
            std::vector<int> expectedOutput = {5,7,6};
            Assert::IsTrue(result);
            Assert::IsTrue(expectedOutput == cycle);
		}

        TEST_METHOD(TestConnectedGraph)
        {
            Graph graph(8);
            graph.addEdge(0, 1);
            graph.addEdge(1, 2);
            graph.addEdge(2, 6);
            graph.addEdge(6, 7);
            graph.addEdge(2, 4);
            graph.addEdge(2, 3);
            graph.addEdge(4, 5);
            graph.addEdge(5, 3);
            std::vector<int> cycle;
            bool result = graph.containsCycle(cycle);
            std::vector<int> expectedOutput = { 2,3,5,4 };
            Assert::IsTrue(result);
            Assert::IsTrue(expectedOutput == cycle);
        }

        TEST_METHOD(TestGraphWithoutCycle)
        {
            Graph graph(5);
            graph.addEdge(0, 1);
            graph.addEdge(1, 2);
            graph.addEdge(2, 3);
            graph.addEdge(3, 4);
            std::vector<int> cycle;
            bool result = graph.containsCycle(cycle);
            Assert::IsFalse(result);
        }
	};
}
