#pragma once

#include <vector>
#include "Subcircuit.h"
#include "Element.h"
#include <unordered_set>

namespace GIS_Data {

    class KoenigGraph {
    private:
        int nodeCount;
        int hyperEdgeCount;
        int tagsLevel;
        std::vector<std::vector<int>> adjList;
        std::vector<std::vector<int>> adjListT;
        std::vector<std::vector<int>> netList;
        std::vector<int> inputChains;
        std::unordered_map<char, std::vector<int>> elemsType;
        std::vector<Element> elements;

        std::vector<std::vector<int>> CalcNeighDeg();
        std::vector<std::vector<int>> CalcAdjLevels();
        std::vector<int> FindStart();
        std::vector<int> FindEnd();
        std::vector<int> Levels(const std::vector<std::vector<int>>& adjList, const std::vector<int>& startNodes);
        void InitElems(const Circuits::Utils::Subcircuit& circuit, bool topology);
    public:
        KoenigGraph(const Circuits::Utils::Subcircuit& circuit, int tagsLevel);

        const std::vector<std::vector<int>>& GetAdjList() const;
        const std::vector<std::vector<int>>& GetAdjListT() const;
        const std::vector<std::vector<int>>& GetNetList() const;
        const std::vector<Element>& GetElements() const;
        const std::vector<int>& GetInputChains() const;
        const int GetNodeCount() const;
        const int GetHyperEdgeCount() const;
        const std::unordered_map<char, std::vector<int>>& GetElemsType() const;

        void NormalizeGraph(int diff, int offset, bool isNode);
        const std::vector<std::vector<int>> TranspAdjList() const;
    };
}
