#include "pch.h"
#include "KoenigGraph.h"

namespace GIS_Data {
    KoenigGraph::KoenigGraph(const std::vector<std::vector<int>>& netlist, const std::vector<Element>& elements, int tagsLevel) : netList(netList), hyperEdgeCount(netList.size()), nodeCount(0), tagsLevel(tagsLevel), elements(elements) {

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

    std::vector<Element>& KoenigGraph::GetElements() {
        return elements;
    }

    int KoenigGraph::GetNodeCount() {
        return nodeCount;
    }

    int KoenigGraph::GetHyperEdgeCount() {
        return hyperEdgeCount;
    }

    void KoenigGraph::NormalizeGraph(int diff, int offset, bool isNode) {

        adjList.insert(adjList.begin() + offset, diff, std::vector<int>{});

        if (isNode) {
            nodeCount += diff;
            for (int i = 0; i < diff; ++i) {
                elements.push_back(Element("empty", 0, {0}, {0, 0}));
            }
        }
        else {
            hyperEdgeCount += diff;
        }
    }

    void KoenigGraph::CalcTags() {
        int totalVertices = adjList.size();
        tag.resize(totalVertices, std::vector<TagType>(tagsLevel + 1, 0));

        for (int start = 0; start < totalVertices; ++start) {
            std::vector<bool> visited(totalVertices, false);
            std::queue<std::pair<int, int>> q;
            visited[start] = true;
            q.push({start, 0});
            std::get<int>(tag[start][0]) = adjList[start].size();

            while (!q.empty()) {
                auto [v, depth] = q.front();
                q.pop();

                if (depth == tagsLevel) continue;

                for (int neighbor : adjList[v]) {
                    if (visited[neighbor])
                        continue;

                    visited[neighbor] = true;
                    if (depth < tagsLevel - 1) {
                        q.push({ neighbor, depth + 1 });
                    }
                    if (depth + 1 <= tagsLevel) {
                        std::get<int>(tag[start][depth + 1]) += adjList[neighbor].size();
                    }
                }
            }
        }
    }
}
