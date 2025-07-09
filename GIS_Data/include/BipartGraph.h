#pragma once

#include "Subcircuit.h"
#include "GraphPair.h"

namespace GIS_Data {

    class BipartGraph {
    private:
        std::vector<std::vector<int>> adjList;

        std::vector<double> TagToVector(const Circuits::Utils::Subcircuit& circuit);
        double EuclideanDistance(const std::vector<double>& vec1, const std::vector<double>& vec2);
        std::vector<int> FindClosest(const std::vector<double>& target, const std::vector<std::vector<double>>& points, double threshold, size_t k);

    public:
        BipartGraph(const GIS_Data::GraphPair& circuits);
        BipartGraph(const std::vector<std::vector<int>>& adjacencyList);
        const std::vector<std::vector<int>>& GetAdjList() const { return adjList; }
    };
}
