#include "CppUnitTest.h"
#include "../Find_MST/Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFindMST
{
	TEST_CLASS(TestFindMST)
	{
	public:
		
		TEST_METHOD(TestIfMST)
		{
            Graph graph(9);
            graph.addEdge(0, 1, 10);
            graph.addEdge(1, 2, 6);
            graph.addEdge(1, 3, 7);
            graph.addEdge(2, 3, 3);
            graph.addEdge(2, 6, 4);
            graph.addEdge(2, 4, 5);
            graph.addEdge(3, 5, 12);
            graph.addEdge(3, 4, 11);
            graph.addEdge(4, 6, 9);
            graph.addEdge(4, 7, 1);
            graph.addEdge(6, 8, 8);
            graph.addEdge(7, 8, 2);

            graph.convertToMST(); // Converting the Graph to MST

            std::vector<bool> visited(9, false);
            std::vector<int> maxEdge({ -1,-1,-1 });
            int expectedWeight = 43;
            auto weightMST = graph.getTotalWeight();

            //Choosing a random node in the MST and checking for cycle
            bool containsCycle = !(graph.containsCycle(2, -1, visited, maxEdge) == noCycle);
            Assert::IsFalse(containsCycle);

            // Checking if we get the minimum possible weight
            Assert::IsTrue(expectedWeight == weightMST);
		}
	};
}
