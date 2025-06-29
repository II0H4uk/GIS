#include "pch.h"
#include "GraphPair.h"

namespace GIS_Data {

    GraphPair::GraphPair(const KoenigGraph& g1, const KoenigGraph& g2, const std::vector<std::pair<int, int>>& fixedNodes)
        : graph1(g1), graph2(g2), fixedNodes(fixedNodes) { }

    KoenigGraph& GraphPair::GetGraph1() {
        return graph1;
    }

    KoenigGraph& GraphPair::GetGraph2() {
        return graph2;
    }

    const std::vector<std::pair<int, int>>& GraphPair::GetBijection() const {
        return fixedNodes;
    }
}
