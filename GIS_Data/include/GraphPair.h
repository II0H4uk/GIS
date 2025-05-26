#pragma once

#ifdef _WIN32
    #ifdef GISDATA_EXPORTS
        #define GISDATA_API __declspec(dllexport)
    #else
        #define GISDATA_API __declspec(dllimport)
    #endif
#else
    #define GISDATA_API
#endif

#include "KoenigGraph.h"

namespace GIS_Data {

    class GISDATA_API GraphPair {
    
    private:
        KoenigGraph graph1;
        KoenigGraph graph2;
        std::vector<std::pair<int, int>> fixedNodes;
    public:
        GraphPair(const KoenigGraph& g1, const KoenigGraph& g2, const std::vector<std::pair<int, int>>& fixedNodes);

        KoenigGraph& GetGraph1();
        KoenigGraph& GetGraph2();
        const std::vector<std::pair<int, int>>& GetBijection() const;
    };
}
