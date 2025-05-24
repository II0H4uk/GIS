#pragma once

#ifdef _WIN32
    #ifdef GISCORE_EXPORTS
        #define GISCORE_API __declspec(dllexport)
    #else
        #define GISCORE_API __declspec(dllimport)
    #endif
#else
    #define GISCORE_API
#endif

#include "Config.h"
#include "Graph.h"
#include "GraphPair.h"

namespace GIS_Core {

    class GISCORE_API Benchmark {
    private:
        static GIS_Data::GraphPair GenGraphs(int nodeCount, int numCliques = 5, int maxClSize = 6);
        static GIS_Data::GraphPair ReadGraphs(const std::string& input1, const std::string& input2);
        static void NormalizeGraphs(GIS_Data::Graph& g1, GIS_Data::Graph& g2);
        static std::tuple<GIS_Data::GraphPair, std::vector<int>, std::vector<int>> ReadHyperGraphs(const std::string& input1, const std::string& input2);
    public:
        static void Init(const GIS_Data::Config config);
    };
}


