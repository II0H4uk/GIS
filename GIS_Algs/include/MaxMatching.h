#pragma once

#include "BipartGraph.h"

namespace GIS_Algs {

    class MaxMatching {
    private:

    public:
        static std::vector<std::pair<int, int>> Start(const GIS_Data::BipartGraph& bipartGraph, int n);
    };
}
