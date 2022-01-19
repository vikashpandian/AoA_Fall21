#include <iostream>
#include "Graph.h"
#include <chrono>
#include <fstream>

using namespace std;

int main(void)
{
    //ofstream file;
    //file.open("4.csv");
    for (int i = 10; i < 1000001; i += 10)
    {
        int size = i;
        Graph graph(size);
        generateGraph(size, graph);
        //graph.printGraph();

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> cycle;
        graph.containsCycle(cycle);
        auto finish = std::chrono::high_resolution_clock::now();
        //cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
        std::cout << size << "," << std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count() << "\n";
    }
    //file.close();
    return 0;
}

