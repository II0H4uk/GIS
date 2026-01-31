#pragma once

#include <AlgStrat.h>
#include <Config.h>
#include <KoenigGraph.h>
#include <random>

namespace GIS_Algs {

	class SignalMatchEnhanced : public AlgStrat {
	private:

        struct InputStats {
            double entropy;      // энтропия отклика
            double influence;    // |cone| / |V|
            double weight;       // итоговый вес
        };

        struct InputSignature {
            std::vector<uint64_t> hashes; // по раундам
            InputStats stats;
        };

        static uint64_t SimulateConeOnce(const GIS_Data::KoenigGraph& g, const std::vector<int>& topo, const std::vector<int>& cone, const std::vector<int>& inputs, std::mt19937& rng);
        static InputSignature BuildInputSignature(const GIS_Data::KoenigGraph& g, int input, const std::vector<int>& topo, int rounds, int maxDepth, std::mt19937& rng);
        static std::vector<int> MatchInputChainsHybrid(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, int rounds, int maxDepth, int outerRounds);
        static double CompareSignatures(const InputSignature& a, const InputSignature& b);
        static std::vector<int> ComputeCone(const GIS_Data::KoenigGraph& g, int input, int maxDepth);
        static std::vector<int> topoOrder(const GIS_Data::KoenigGraph& g, const std::vector<int>& inputs);
	public:
		std::vector<std::pair<std::vector<int>, std::vector<int>>> Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, const GIS_Data::Config& config) override;
	};
}
