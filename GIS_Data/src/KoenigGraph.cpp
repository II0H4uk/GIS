#include "pch.h"
#include "KoenigGraph.h"
#include <Subcircuit.h>

namespace GIS_Data {
    KoenigGraph::KoenigGraph(const Circuits::Utils::Subcircuit& circuit, int tagsLevel) :
        nodeCount(circuit.components.size()),
        hyperEdgeCount(circuit.netsCount),
        netList(hyperEdgeCount),
        adjList(nodeCount + hyperEdgeCount),
        tagsLevel(tagsLevel) {

        for (int i = 0; i < circuit.components.size(); ++i) {
            for (int j = 0; j < circuit.components[i].chainInt.size(); ++j) {
                netList[circuit.components[i].chainInt[j]].push_back(i);
            }
        }

        for (int i = 0; i < hyperEdgeCount; ++i) {
            int currHyperEdge = nodeCount + i;

            for (int node : netList[i]) {
                if (circuit.components[node].chainInt.back() == i)
                    adjList[node].push_back(currHyperEdge);
                else
                    adjList[currHyperEdge].push_back(node);
            }
        }

        std::vector<std::vector<int>> neighDeg = CalcNeighDeg();
        std::vector<std::vector<int>> adjLv = CalcAdjLevels();

        std::vector<Circuits::Utils::TopologyComponent> c = circuit.components;
        for (int i = 0; i < nodeCount; ++i)
            elements.push_back(Element(c[i].id, c[i].chainInt, { c[i].lengthComponent, c[i].widthComponent }, neighDeg[i], adjLv[0][i], adjLv[1][i]));
    }

    void KoenigGraph::NormalizeGraph(int diff, int offset, bool isNode) {

        adjList.insert(adjList.begin() + offset, diff, std::vector<int>{});

        if (isNode) {
            nodeCount += diff;
            for (int i = 0; i < diff; ++i) {
                elements.push_back(Element("empty", {}, {}, {}, 0, 0));
            }
        }
        else {
            hyperEdgeCount += diff;
        }
    }

    std::vector<std::vector<int>> KoenigGraph::CalcNeighDeg() {
        int totalVertices = adjList.size();
        std::vector<std::vector<int>> neighDeg(totalVertices, std::vector<int>(tagsLevel + 1));

        for (int start = 0; start < totalVertices; ++start) {
            std::vector<bool> visited(totalVertices, false);
            std::queue<std::pair<int, int>> q;
            visited[start] = true;
            q.push({start, 0});
            neighDeg[start][0] = adjList[start].size();

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
                        neighDeg[start][depth + 1] += adjList[neighbor].size();
                    }
                }
            }
        }

        return neighDeg;
    }

    std::vector<std::vector<int>> KoenigGraph::CalcAdjLevels() {

        std::vector<int> startNodes = FindStart();
        std::vector<int> endNodes = FindEnd();

        std::vector<int> forwardLv = Levels(adjList, startNodes);

        std::vector<std::vector<int>> revList = TranspAdjList();
        std::vector<int> backwardLv = Levels(revList, endNodes);

        return {forwardLv, backwardLv};
    }

    std::vector<int> KoenigGraph::Levels(const std::vector<std::vector<int>>& adjList, const std::vector<int>& startNodes) {
        std::vector<int> levels(adjList.size(), -1);
        std::queue<int> q;

        for (int i = 0; i < startNodes.size(); ++i) {
            levels[startNodes[i]] = 0;
            q.push(startNodes[i]);
        }

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int i = 0; i < adjList[curr].size(); ++i) {
                if (levels[adjList[curr][i]] == -1) {
                    levels[adjList[curr][i]] = levels[curr] + 1;
                    q.push(adjList[curr][i]);
                }
            }
        }

        return levels;
    }

    std::vector<std::vector<int>> KoenigGraph::TranspAdjList() {
        std::vector<std::vector<int>> revList(adjList.size());
        for (int i = 0; i < adjList.size(); ++i) {
            for (int j = 0; j < adjList[i].size(); ++j) {
                revList[adjList[i][j]].push_back(i);
            }
        }
        
        return revList;
    }

    std::vector<int> KoenigGraph::FindStart() {
        std::vector<int> startNodes;

        std::vector<bool> isUsed(hyperEdgeCount);
        for (int i = 0; i < nodeCount; ++i) {
            for (int j = 0; j < adjList[i].size(); ++j) {
                isUsed[adjList[i][j] - nodeCount] = true;
            }
        }

        for (int i = 0; i < isUsed.size(); ++i) {
            if (!isUsed[i])
                startNodes.push_back(nodeCount + i);
        }

        return startNodes;
    }

    std::vector<int> KoenigGraph::FindEnd() {
        std::vector<int> endNodes;

        for (int i = 0; i < hyperEdgeCount; ++i) {
            int netNode = nodeCount + i;

            if (adjList[netNode].size() == 0)
                endNodes.push_back(netNode);
        }

        return endNodes;
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
}
