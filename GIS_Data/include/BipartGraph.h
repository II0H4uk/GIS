#pragma once

#include "Element.h"
#include <cmath>

namespace GIS_Data {

    class BipartGraph {
    private:
        std::vector<std::vector<int>> adjList;

        std::vector<double> TagToVector(const std::vector<Element>& tag);
        double EuclideanDistance(const std::vector<double>& vec1, const std::vector<double>& vec2);
        std::vector<int> FindClosest(const std::vector<double>& target, const std::vector<std::vector<double>>& points, double threshold, size_t k);

    public:
        BipartGraph(const std::vector<Element>& elems1, const std::vector<Element>& elems2);
        BipartGraph(const std::vector<std::vector<int>>& adjacencyList);
        const std::vector<std::vector<int>>& GetAdjList() const { return adjList; }
    };
}
