#include "pch.h"
#include "Graph.h"

namespace GIS_Data {

    Graph::Graph(const std::vector<std::vector<int>>& adjList, int nodeCount) : adjList(adjList), nodeCount(nodeCount) {
        tag.resize(nodeCount);

        for (int i = 0; i < nodeCount; ++i)
            tag[i].push_back(static_cast<int>(adjList[i].size()));
    }

    bool Graph::CompareTags(const TagType& first, const TagType& second) const {
        return first == second;
    }

    std::vector<std::vector<int>> Graph::GetAdjList() const {
        return adjList;
    }

    int Graph::GetNodeCount() const {
        return nodeCount;
    }
}
