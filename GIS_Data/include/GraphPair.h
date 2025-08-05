#pragma once

#include "KoenigGraph.h"

namespace GIS_Data {

    class GraphPair {
    
    private:
        KoenigGraph graph1;
        KoenigGraph graph2;
        std::vector<std::pair<int, int>> fixedNodes;
    public:
        GraphPair(const KoenigGraph& g1, const KoenigGraph& g2, const std::vector<std::pair<int, int>>& fixedNodes);

        const KoenigGraph& GetGraph1() const;
        const KoenigGraph& GetGraph2() const;
        const std::vector<std::pair<int, int>>& GetBijection() const;
    };
}
