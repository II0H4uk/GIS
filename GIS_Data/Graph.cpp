#include "Graph.h"
#include "pch.h"

namespace GIS_Data {

    Graph::Graph(const std::vector<std::vector<int>>& adjList, int nodeCount) :adjList(adjList) {
        tag.resize(nodeCount);

        for (int i = 0; i < nodeCount; ++i)
            tag[i] = static_cast<int>(adjList[i].size());
    }

    std::vector<std::vector<int>> Graph::GetAdjList() const {
        return adjList;
    }
}
