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
        bool flag;
    public:
        GraphPair(const Graph& g1, const Graph& g2, bool flag);
        Graph& GetGraph1();
        Graph& GetGraph2();
    };
}
