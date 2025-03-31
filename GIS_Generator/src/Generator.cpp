#include "pch.h"
#include "Generator.h"

namespace GIS_Generator {

    GIS_Data::GraphPair Generator::GenerateGraphPair(const int nodeCount, bool isIsomorphic) {
        GIS_Data::Graph g1 = GenerateGraph(nodeCount);
        GIS_Data::Graph g2 = isIsomorphic ? GenerateIsomorphicGraph(nodeCount, g1) : GenerateGraph(nodeCount);

        return GIS_Data::GraphPair(g1, g2, true);
    }

    GIS_Data::Graph Generator::GenerateGraph(const int nodeCount) {
        std::vector<std::vector<int>> adjList(nodeCount);

        for (int i = 0; i < nodeCount; ++i) {
            for (int j = i + 1; j < nodeCount; ++j) {
                if (GenerateRandomNumber(nodeCount - 1) % 2) {
                    AddEdge(adjList, i, j);
                }
            }
        }

        return GIS_Data::Graph(adjList, nodeCount);
    }

    int Generator::GenerateRandomNumber(int max) {
        std::uniform_int_distribution<> dis(0, max - 1);
        return dis(gen);
    }

    void Generator::AddEdge(std::vector<std::vector<int>>& adjList, int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    GIS_Data::Graph Generator::GenerateIsomorphicGraph(const int nodeCount, GIS_Data::Graph graph) {
        std::vector<int> permutation = GetPermutation(nodeCount);

        std::vector<std::vector<int>> adjList1 = graph.GetAdjList();
        std::vector<std::vector<int>> adjList2(nodeCount);

        for (int i = 0; i < nodeCount; ++i) {
            for (auto neighbor : adjList1[i]) {
                adjList2[permutation[i]].push_back(permutation[neighbor]);
            }
        }

        return GIS_Data::Graph(adjList2, nodeCount);
    }

    std::vector<int> Generator::GetPermutation(const int n) {
        std::vector<int> permutation(n);
        iota(permutation.begin(), permutation.end(), 0);
        shuffle(permutation.begin(), permutation.end(), gen);

        return permutation;
    }
}