#pragma once

#ifdef _WIN32
    #ifdef GISDATA_EXPORTS
        #define GISDATA_API __declspec(dllexport)
    #else
        #define GISDATA_API __declspec(dllimport)
    #endif
#else
    #define GISDATA_API
#endif

#include "Element.h"
#include <cmath>

namespace GIS_Data {

    class GISDATA_API BipartGraph {
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
