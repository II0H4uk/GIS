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

#include "Graph.h"

namespace GIS_Data {

    class GISDATA_API GraphPair {
    
    private:
        Graph graph1;
        Graph graph2;
        std::vector<int> bijection;
    public:
        GraphPair(const Graph& g1, const Graph& g2, const std::vector<int>& bijection);
        Graph& GetGraph1();
        Graph& GetGraph2();
        const std::vector<int>& GetBijection() const;
    };
}
