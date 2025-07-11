#pragma once

#include <vector>
#include "Subcircuit.h"
#include "Element.h"

namespace GIS_Data {

    class KoenigGraph {
    private:
        int nodeCount;
        int hyperEdgeCount;
        int tagsLevel;
        std::vector<std::vector<int>> adjList;
        std::vector<std::vector<int>> netList;
        std::vector<Element> elements;

        std::vector<std::vector<int>> CalcNeighDeg();
        std::vector<std::vector<int>> CalcAdjLevels();
        std::vector<int> FindStart();
        std::vector<int> FindEnd();
        std::vector<int> Levels(const std::vector<std::vector<int>>& adjList, const std::vector<int>& startNodes);
        std::vector<std::vector<int>> TranspAdjList();
    public:
        KoenigGraph(const Circuits::Utils::Subcircuit& circuit, int tagsLevel);

        std::vector<std::vector<int>>& GetAdjList();
        std::vector<std::vector<int>>& GetNetList();
        std::vector<Element>& GetElements();
        int GetNodeCount();
        int GetHyperEdgeCount();

        void NormalizeGraph(int diff, int offset, bool isNode);
    };
}
