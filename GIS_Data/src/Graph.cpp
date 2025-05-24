#include "pch.h"
#include "Graph.h"
#include <unordered_set>

namespace GIS_Data {

    Graph::Graph(const std::vector<std::vector<int>>& adjList, int nodeCount, int neighDegLv) : adjList(adjList), nodeCount(nodeCount), neighDegLv(neighDegLv) {

        tag = CalcNodesDeg(adjList, neighDegLv);
    }

    std::vector<std::vector<TagType>> Graph::CalcNodesDeg(const std::vector<std::vector<int>>& adjList, int maxDepth) {
        int nodeCount = adjList.size();
        std::vector<std::vector<TagType>> tags(nodeCount, std::vector<TagType>(maxDepth + 1, 0));

        std::vector<int> degrees(nodeCount);
        for (int i = 0; i < nodeCount; ++i) {
            degrees[i] = adjList[i].size();
            tags[i][0] = degrees[i];
        }

        for (int i = 0; i < nodeCount; ++i) {
            std::unordered_set<int> visited;
            visited.insert(i);
            std::unordered_set<int> currentLevel = { i };

            for (int depth = 1; depth <= maxDepth; ++depth) {
                std::unordered_set<int> nextLevel;

                for (int u : currentLevel) {
                    for (int v : adjList[u]) {
                        if (visited.insert(v).second) {
                            AddToTagInt(tags[i][depth], degrees[v]);
                            nextLevel.insert(v);
                        }
                    }
                }

                currentLevel = std::move(nextLevel);
            }
        }

        return tags;
    }

    void Graph::AddToTagInt(TagType& tag, int value) {
        if (auto pval = std::get_if<int>(&tag)) {
            *pval += value;
        }
        else {
            tag = value;
        }
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

    int Graph::GetNeighDegLv() const {
        return neighDegLv;
    }

    void Graph::NormalizeGraph(int diff) {
        int baseNodeCount = nodeCount;
        nodeCount += diff;

        adjList.resize(nodeCount);
        tag.resize(nodeCount);
        for (int i = 0; i < nodeCount - baseNodeCount; ++i) {
            tag[baseNodeCount + i].resize(tag[0].size());
        }
    }
}
