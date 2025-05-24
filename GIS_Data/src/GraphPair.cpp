#include "pch.h"
#include "GraphPair.h"

namespace GIS_Data {

    GraphPair::GraphPair(const Graph& g1, const Graph& g2, const std::vector<int>& bijection)
        : graph1(g1), graph2(g2), bijection(bijection) { }

    Graph& GraphPair::GetGraph1() {
        return graph1;
    }

    Graph& GraphPair::GetGraph2() {
        return graph2;
    }

    const std::vector<int>& GraphPair::GetBijection() const {
        return bijection;
    }
}
