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
        static void CorrectGraphsNodes(GIS_Data::Graph& graph1, GIS_Data::Graph& graph2);
        static GIS_Data::GraphPair GenGraphs(int nodeCount, bool isomorph);
        static GIS_Data::GraphPair ReadGraphs(const std::string& input1, const std::string& input2, bool isomorph);
        static std::tuple<GIS_Data::GraphPair, std::vector<int>, std::vector<int>> ReadHyperGraphs(const std::string& input1, const std::string& input2, bool isomorph);
    public:
        static void Init(const GIS_Data::Config config);
    };
}


