#include "pch.h"
#include "Graph.h"

namespace GIS_Data {

    Graph::Graph(const std::vector<std::vector<int>>& adjList, int nodeCount) : adjList(adjList), nodeCount(nodeCount) {
        tag.resize(nodeCount);

        for (int i = 0; i < nodeCount; ++i)
            tag[i].push_back(static_cast<int>(adjList[i].size()));
    }

    bool CompareTags(const TagType& first, const TagType& second) {
        return first == second;
    }

    const std::vector<std::vector<int>>& Graph::GetAdjList() const {
        return adjList;
    }

    const std::vector<std::vector<TagType>>& Graph::GetTag() const {
        return tag;
    }

    int Graph::GetNodeCount() const {
        return nodeCount;
    }

    GraphPair::GraphPair(const Graph& g1, const Graph& g2, bool flag)
        : graph1(g1), graph2(g2), flag(flag) {}

}
