#include "pch.h"
#include "Benchmark.h"
#include "Statistics.h"
#include "Generator.h"
#include "KoenigGraph.h"
#include "ValidateMatch.h"
#include <SignalMatching.h>
#include <Utils.h>
#include <queue>
#include <set>

namespace GIS_Core {

    void Benchmark::SetStrat(std::unique_ptr<GIS_Algs::AlgStrat> alg) {
        alg_ = std::move(alg);
    }

    std::vector<std::pair<std::vector<int>, std::vector<int>>> Benchmark::Process(const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2, const GIS_Data::Config& config) {
        if (!alg_)
            throw std::runtime_error("Алгоритм не выбран");
        
        return alg_->Start(kGraph1, kGraph2, config);
    }

    /*GIS_Data::GraphPair Benchmark::GenGraphs(int nodeCount, int numCliques, int maxClSize) {

        GIS_Generator::Generator generator;
        return generator.GenerateGraphPair(nodeCount, numCliques, maxClSize);
    }*/
}
