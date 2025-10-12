#pragma once

#include "Subcircuit.h"
#include "GraphPair.h"

namespace GIS_Data {

    class BipartGraph {
    private:
        std::vector<std::vector<int>> adjList;

        bool AreSimilar(const Element& a, const Element& b);

    public:
        BipartGraph();
        BipartGraph(const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2);
        BipartGraph(const std::vector<std::vector<int>>& adjacencyList);
        const std::vector<std::vector<int>>& GetAdjList() const { return adjList; }
        void ChangeEdge(int i, int j, int edgeStatus);
        void EraseElem(int i, int j);
    };
}
