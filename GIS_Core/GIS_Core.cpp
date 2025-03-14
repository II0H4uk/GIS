#include "Graph.h"
#include "pch.h"

int main(int argc, char* argv[])
{
    int nodeCount = 3;

    std::vector<std::vector<int>> adjList = {
        {1, 2},
        {0, 2},
        {0, 1}
    };

    GIS_Data::Graph graph = GIS_Data::Graph(adjList, nodeCount);
    std::cout << graph.GetAdjList()[0][0];
    return 0;
}
