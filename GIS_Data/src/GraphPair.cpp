#include "pch.h"
#include "GraphPair.h"

namespace GIS_Data {

    GraphPair::GraphPair(const Graph& g1, const Graph& g2, bool flag)
        : graph1(g1), graph2(g2), flag(flag) {
    }
}
