#pragma once

#include "GraphPair.h"
#include <BipartGraph.h>
#include <random>

namespace GIS_Generator {

    class Generator {
    private:
        std::random_device rd;
        std::mt19937 gen;
        std::vector<int> GetPermutation(const int n);
        int GenRandNum(int max);
        void AddEdge(std::vector<std::vector<int>>& adjList, int i, int j);
        bool CheckEdge(const std::vector<std::vector<int>>& adjList, int i, int j);
        void AddNoise(std::vector<std::vector<int>>& adjList, std::vector<int>& permutation, double noise);
        bool HasEdge(const std::vector<std::vector<int>>& adjList, int u, int v);
    public:
        /*Generator() : gen(rd()) {}
        GIS_Data::GraphPair GenerateGraphPair(const int nodeCount, int numCliques, int maxClSize);
        std::pair<GIS_Data::Graph, std::vector<int>> GenIsoGraph(const GIS_Data::Graph& graph);
        GIS_Data::Graph GenGraph(const int nodeCount);
        GIS_Data::Graph GenerateCliqueOverlapGraph(const int nodeCount, int numCliques, int maxClSize);*/
    };
}
