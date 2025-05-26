#include "pch.h"
#include "KoenigGraph.h"

namespace GIS_Data {
    KoenigGraph::KoenigGraph(const std::vector<std::vector<int>>& netList, int tagsLevel) : netList(netList), hyperEdgeCount(netList.size()), nodeCount(0), tagsLevel(tagsLevel) {

        for (int i = 0; i < hyperEdgeCount; ++i)
            for (int j = 0; j < netList[i].size(); ++j)
                if (nodeCount < netList[i][j]) nodeCount = netList[i][j];
        nodeCount++;

        adjList.resize(nodeCount + hyperEdgeCount);

        for (int i = 0; i < hyperEdgeCount; ++i) {
            int currHyperEdge = nodeCount + i;

            for (int node : netList[i]) {
                adjList[node].push_back(currHyperEdge);
                adjList[currHyperEdge].push_back(node);
            }
        }

        CalcTags();
    }

    std::vector<std::vector<int>>& KoenigGraph::GetAdjList() {
        return adjList;
    }

    std::vector<std::vector<int>>& KoenigGraph::GetNetList() {
        return netList;
    }

    std::vector<std::vector<TagType>> KoenigGraph::GetTags() {
        return tag;
    }

    int KoenigGraph::GetNodeCount() {
        return nodeCount;
    }

    int KoenigGraph::GetHyperEdgeCount() {
        return hyperEdgeCount;
    }

    void KoenigGraph::NormalizeGraph(int diff, int offset, bool isNode) {

        adjList.insert(adjList.begin() + offset, diff, std::vector<int>{});
        tag.insert(tag.begin() + offset, diff, std::vector<TagType>{});

        for (int i = 0; i < diff; ++i) {
            tag[offset + i].resize(tag[0].size());
        }

        if (isNode)
            nodeCount += diff;
        else
            hyperEdgeCount += diff;
    }

    void KoenigGraph::CalcTags() {
        int totalVertices = adjList.size();
        tag.resize(totalVertices, std::vector<TagType>(tagsLevel, 0));

        for (int start = 0; start < totalVertices; ++start) {
            std::vector<bool> visited(totalVertices, false);
            std::queue<std::pair<int, int>> q;
            visited[start] = true;
            q.push({start, 0});

            while (!q.empty()) {
                auto [v, depth] = q.front();
                q.pop();

                if (depth == tagsLevel) continue;

                for (int neighbor : adjList[v]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        if (depth < tagsLevel - 1) {
                            q.push({ neighbor, depth + 1 });
                        }
                        if (depth + 1 <= tagsLevel) {
                            std::get<int>(tag[start][depth]) += adjList[neighbor].size();
                        }
                    }
                }
            }
        }
    }
}
