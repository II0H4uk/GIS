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
    public:
        KoenigGraph(const Circuits::Utils::Subcircuit& circuit, int tagsLevel);

        const std::vector<std::vector<int>>& GetAdjList() const;
        const std::vector<std::vector<int>>& GetNetList() const;
        const std::vector<Element>& GetElements() const;
        const int GetNodeCount() const;
        const int GetHyperEdgeCount() const;

        void NormalizeGraph(int diff, int offset, bool isNode);
        const std::vector<std::vector<int>> TranspAdjList() const;
    };
}
