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

#include "pch.h"
#include "Graph.h"

namespace GIS_Data {

    class GISDATA_API GraphPair {
    public:
        GraphPair(const Graph& g1, const Graph& g2, bool flag);

    private:
        Graph graph1;
        Graph graph2;
        bool flag;
    };
}
