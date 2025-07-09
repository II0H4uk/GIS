#pragma once

#include "Config.h"
#include "GraphPair.h"

namespace GIS_Core {

    class Benchmark {
    private:
        static GIS_Data::GraphPair GenGraphs(int nodeCount, int numCliques = 5, int maxClSize = 6);
        static GIS_Data::GraphPair ReadGraphs(const std::string& input1, const std::string& input2);
        static GIS_Data::GraphPair ReadHyperGraphs(const std::string& input1, const std::string& input2, int tagsLevel);
        static void NormalizeGraphs(GIS_Data::KoenigGraph& g1, GIS_Data::KoenigGraph& g2);
        static void Normalize(GIS_Data::KoenigGraph& g1, GIS_Data::KoenigGraph& g2, int g1Nodes, int g2Nodes, int offset1, int offset2, bool isNode);
    public:
        static void Init(const GIS_Data::Config config);
    };
}


