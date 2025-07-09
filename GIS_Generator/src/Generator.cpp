#include "pch.h"
#include "Generator.h"
#include <unordered_set>

namespace GIS_Generator {

    //GIS_Data::GraphPair Generator::GenerateGraphPair(const int nodeCount, int numCliques, int maxClSize) {
    //    //GIS_Data::Graph g1 = GenGraph(nodeCount);
    //    GIS_Data::Graph g1 = GenerateCliqueOverlapGraph(nodeCount, numCliques, maxClSize);
    //    auto [g2, perm] = GenIsoGraph(g1);
    //    throw std::logic_error("Not implemented");
    //    //return GIS_Data::GraphPair(GIS_Data::KoenigGraph(std::vector<std::vector<int>>{}, 0), GIS_Data::KoenigGraph(std::vector<std::vector<int>>{}, 0), std::vector<std::pair<int, int>>{});
    //}

    /*GIS_Data::Graph Generator::GenGraph(const int nodeCount) {
        std::vector<std::vector<int>> adjList(nodeCount);

        for (int i = 0; i < nodeCount - 1; ++i) {
            AddEdge(adjList, i, i + 1);
        }*/

        /*for (int i = 0; i < nodeCount; ++i) {
            while (deg[i] < 3) {
                int j = GenRandNum(nodeCount);
                if (i == j || deg[j] > 4 || CheckEdge(adjList, i, j))
                    continue;

                AddEdge(adjList, deg, i, j);
                deg[j]++;
                deg[i]++;
            }
        }*/

        /*for (int k = 0; k < nodeCount * 2; ++k) {
            int j = GenRandNum(nodeCount);
            int i = GenRandNum(nodeCount);

            if (i == j || CheckEdge(adjList, i, j))
                continue;

            AddEdge(adjList, i, j);
        }

        return GIS_Data::Graph(adjList, nodeCount);
    }*/

    /*bool Generator::CheckEdge(const std::vector<std::vector<int>>& adjList, int u, int v) {
        return std::find(adjList[u].begin(), adjList[u].end(), v) != adjList[u].end();
    }

    int Generator::GenRandNum(int max) {
        std::uniform_int_distribution<> dis(0, max - 1);
        return dis(gen);
    }

    void Generator::AddEdge(std::vector<std::vector<int>>& adjList, int i, int j) {
        adjList[i].push_back(j);
        adjList[j].push_back(i);
    }

    std::pair<GIS_Data::Graph, std::vector<int>> Generator::GenIsoGraph(const GIS_Data::Graph& g1) {
        std::vector<int> permutation = GetPermutation(g1.GetNodeCount());

        std::vector<std::vector<int>> adjList(g1.GetNodeCount());

        for (int i = 0; i < g1.GetNodeCount(); ++i) {
            for (auto neighbor : g1.GetAdjList()[i]) {
                adjList[permutation[i]].push_back(permutation[neighbor]);
            }
        }

        AddNoise(adjList, permutation, 0.0);

        return { GIS_Data::Graph(adjList, g1.GetNodeCount(), 2), permutation };
    }

    std::vector<int> Generator::GetPermutation(const int n) {
        std::vector<int> permutation(n);
        iota(permutation.begin(), permutation.end(), 0);
        shuffle(permutation.begin(), permutation.end(), gen);

        return permutation;
    }*/

    /*void Generator::AddNoise(std::vector<std::vector<int>>& adjList, std::vector<int>& permutation, double noise) {
        int baseSize = adjList.size();
        int noiseNodes = baseSize * noise;
        int edgeCount = 0;
        for (int i = 0; i < baseSize; ++i) {
            edgeCount += adjList[i].size();
        }
        int noiseEdges = edgeCount * noise / 2;

        for (int i = 0; i < noiseNodes; ++i) {
            int j = GenRandNum(adjList.size());
            if (j == baseSize + i) {
                i--;
                continue;
            }
            permutation.push_back(-1);

            adjList.push_back(std::vector<int>());
            adjList[baseSize + i].push_back(j);
            adjList[j].push_back(baseSize + i);
            noiseEdges--;
        }

        for (int i = 0; i < noiseEdges; ++i) {
            int j = GenRandNum(adjList.size());
            if (j == baseSize + i) {
                i--;
                continue;
            }
            adjList[baseSize + i].push_back(j);
            adjList[j].push_back(baseSize + i);
        }
    }*/

    /*GIS_Data::Graph Generator::GenerateCliqueOverlapGraph(const int nodeCount, int numCliques, int maxClSize) {
        std::vector<std::vector<int>> adjList(nodeCount);
        //int numCliques = nodeCount / 10;

        for (int c = 0; c < numCliques; ++c) {
            int cliqueSize = GenRandNum(maxClSize) + 3;

            std::unordered_set<int> cliqueNodes;
            while (cliqueNodes.size() < cliqueSize) {
                int v = GenRandNum(nodeCount);
                cliqueNodes.insert(v);
            }

            std::vector<int> nodes(cliqueNodes.begin(), cliqueNodes.end());

            for (int i = 0; i < nodes.size(); ++i) {
                for (int j = i + 1; j < nodes.size(); ++j) {
                    int u = nodes[i];
                    int v = nodes[j];
                    if (!HasEdge(adjList, u, v)) {
                        AddEdge(adjList, u, v);
                    }
                }
            }
        }

        return GIS_Data::Graph(adjList, nodeCount, 2);
    }*/

    /*bool Generator::HasEdge(const std::vector<std::vector<int>>& adjList, int u, int v) {
        return std::find(adjList[u].begin(), adjList[u].end(), v) != adjList[u].end();
    }*/
}