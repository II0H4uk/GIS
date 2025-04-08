#include "pch.h"
#include "GraphPair.h"

namespace GIS_Data {

    GraphPair::GraphPair(const Graph& g1, const Graph& g2, bool flag)
        : graph1(g1), graph2(g2), flag(flag) {
    }

    const Graph GraphPair::GetGraph1() const{
        return graph1;
    }

    const Graph GraphPair::GetGraph2() const {
        return graph2;
    }
}
