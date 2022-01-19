#include <iostream>
#include "Graph.h"
#include <chrono>
#include <fstream>

using namespace std;

int main(void)
{
    /*Graph graph(9);
    graph.addEdge(0, 2);
    graph.addEdge(1, 0);
    graph.addEdge(2, 4);
    graph.addEdge(3, 1);
    graph.addEdge(4, 0);
    graph.addEdge(5, 6);
    graph.addEdge(6, 7);*/
    //graph.addEdge(7, 5);

    /*Graph graph(8);
    graph.addEdge(0, 1, 5);
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 6, 6);
    graph.addEdge(6, 7, 2);
    graph.addEdge(2, 4, 4);
    graph.addEdge(2, 3, 7);
    graph.addEdge(4, 5, 3);
    graph.addEdge(5, 3, 1);
    graph.addEdge(7, 0, 1);*/

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
    graph.convertToMST();
    cout << "\n\n" << graph.getTotalWeight();

    //ofstream file;
    //file.open("11.csv");
    /*for (int i = 100; i < 1000001; i += 400)
    {
        int size = i;
        Graph graph(size);
        generateGraph(size, graph);
        //graph.printGraph();
        auto start = std::chrono::high_resolution_clock::now();
        graph.converToMST();
        auto finish = std::chrono::high_resolution_clock::now();
        std::cout << size << "," << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << "\n";
    }*/
    //file.close();
    return 0;
}

