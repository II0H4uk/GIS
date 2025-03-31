#pragma once

#ifdef _WIN32
    #ifdef GISGENERATOR_EXPORTS
        #define GISGENERATOR_API __declspec(dllexport)
    #else
        #define GISGENERATOR_API __declspec(dllimport)
    #endif
#else
    #define GISGENERATOR_API
#endif

#include "pch.h"
#include "Graph.h"
#include "GraphPair.h"

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <numeric>

namespace GIS_Generator {

    class GISGENERATOR_API Generator {
    private:
        std::random_device rd;
        std::mt19937 gen;
        std::vector<int> GetPermutation(const int n);
        int GenerateRandomNumber(int max);
        void AddEdge(std::vector<std::vector<int>>& adjList, int u, int v);

    public:
        Generator() : gen(rd()) {}
        GIS_Data::GraphPair GenerateGraphPair(const int nodeCount, bool isIsomorphic);
        GIS_Data::Graph GenerateIsomorphicGraph(const int nodeCount, GIS_Data::Graph graph);
        GIS_Data::Graph GenerateGraph(const int nodeCount);     
    };
}
