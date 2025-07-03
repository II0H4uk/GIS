#pragma once

#include <vector>
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
        void CalcTags();

    public:
        KoenigGraph(const std::vector<std::vector<int>>& netlist, const std::vector<Element>& elements, int tagsLevel);

        std::vector<std::vector<int>>& GetAdjList();
        std::vector<std::vector<int>>& GetNetList();
        std::vector<Element>& GetElements();
        int GetNodeCount();
        int GetHyperEdgeCount();

        void NormalizeGraph(int diff, int offset, bool isNode);
    };
}
