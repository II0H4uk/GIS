#pragma once

#include <KoenigGraph.h>

namespace GIS_Algs {
    class CheckMatching {
    private:
    public:
        static std::vector<bool> Start(std::vector<std::pair<int, int>> elemMap, int n, const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2);
    };
}