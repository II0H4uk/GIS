#pragma once

#ifdef _WIN32
    #ifdef GISALGS_EXPORTS
        #define GISALG_API __declspec(dllexport)
    #else
        #define GISALG_API __declspec(dllimport)
    #endif
#else
    #define GISALG_API
#endif

#include "Graph.h"
#include <vector>

namespace GIS_Algs {

    class GISALG_API SubGraphIso {
    private:
        static const std::vector<int> InitBijection(int fixNodeCount, int nodeCount);
        static void MatchNodes(std::vector<int>& bijection, const std::vector<int>& subGraph1, const std::vector<int>& subGraph2, const GIS_Data::Graph& graph1, const GIS_Data::Graph& graph2);
    public:
        static const std::vector<int> Start(const GIS_Data::Graph& graph1, const GIS_Data::Graph& graph2, int fixNodeCount);
    };
}


