#pragma once

#include "Config.h"
#include <AlgStrat.h>

namespace GIS_Core {

    class Benchmark {
    private:
        std::unique_ptr<GIS_Algs::AlgStrat> alg_;
        

        /*GIS_Data::GraphPair GenGraphs(int nodeCount, int numCliques = 5, int maxClSize = 6);
        GIS_Data::GraphPair ReadGraphs(const std::string& input1, const std::string& input2);
        GIS_Data::GraphPair ReadHyperGraphs(const std::string& input1, const std::string& input2, int tagsLevel);*/
        void Normalize(GIS_Data::KoenigGraph& g1, GIS_Data::KoenigGraph& g2, int g1Nodes, int g2Nodes, int offset1, int offset2, bool isNode);
    public:
        void SignalMatching(const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2, const GIS_Data::Config& config);
        void MaxMatching(const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2);
        void NormalizeGraphs(GIS_Data::KoenigGraph& g1, GIS_Data::KoenigGraph& g2);

        void SetStrat(std::unique_ptr<GIS_Algs::AlgStrat> alg);
        std::vector<std::pair<std::vector<int>, std::vector<int>>> Process(const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2, const GIS_Data::Config& config);
    };
}


