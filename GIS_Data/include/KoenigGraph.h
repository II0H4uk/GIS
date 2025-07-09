#pragma once

#include <vector>
#include "Subcircuit.h"

namespace GIS_Data {

    class KoenigGraph {
    private:
        int nodeCount;
        int hyperEdgeCount;
        int tagsLevel;
        std::vector<std::vector<int>> adjList;
        std::vector<std::vector<int>> netList;
        Circuits::Utils::Subcircuit circuit;
        void CalcTags();

    public:
        KoenigGraph(const Circuits::Utils::Subcircuit& circuit, int tagsLevel);

        std::vector<std::vector<int>>& GetAdjList();
        std::vector<std::vector<int>>& GetNetList();
        Circuits::Utils::Subcircuit& GetCircuit();
        int GetNodeCount();
        int GetHyperEdgeCount();

        void NormalizeGraph(int diff, int offset, bool isNode);
    };
}
