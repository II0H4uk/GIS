#pragma once

#include <AlgStrat.h>
#include <Config.h>
#include <KoenigGraph.h>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace GIS_Algs {

    struct InputSignature {
        double mean;
        double variance;
    };

    class SignalMatching : public AlgStrat {
    private:

        static std::vector<InputSignature> ComputeInputSignatures(const GIS_Data::KoenigGraph& g, const std::vector<int>& topoOrder, const std::vector<int>& inputs, int numSimulations);
        static double Similarity(const InputSignature& a, const InputSignature& b);
        static std::vector<int> MatchInputsStochastic(const std::vector<InputSignature>& A, const std::vector<InputSignature>& B, double threshold);

        static void Process6TSRAM(std::vector<int>& order, std::vector<int>& visDeg, std::vector<bool>& isTrigger, const GIS_Data::KoenigGraph& g, int firstCh);
        static void findPowerNets(const std::vector<std::string>& nets_name, const std::string& name, std::vector<int>& power_net, int node_count);
        static std::vector<int> GetInputNets(const GIS_Data::KoenigGraph& g);
        static std::vector<int> GetTopoOrder(const GIS_Data::KoenigGraph& g, const std::vector<int>& inputs);
        static std::vector<int> HungarianAlg(const std::vector<std::vector<double>>& cost);
        static std::vector<int> GetInputSign(const GIS_Data::KoenigGraph& g, const std::unordered_set<std::string>& allTypes, int inputNet, int maxDepth = 3);
        static double L2(const std::vector<int>& a, const std::vector<int>& b);
        static void SimulateOnce(const GIS_Data::KoenigGraph& g, const std::vector<int>& topoOrder, const std::vector<int>& inputNets, const std::vector<int>& inputBits, std::vector<int>& result);
        static std::vector<std::vector<int>> RunStochastic(const GIS_Data::KoenigGraph& g, const std::vector<int>& topoOrder, const std::vector<int>& inputNetsG, int iterations, std::vector<std::vector<int>>& inputBits);
        static std::string QuantKey(const std::vector<int>& sig, int scale = 1000);
        static void MatchInputs(const GIS_Data::KoenigGraph& g1, const std::vector<int>& in1, const GIS_Data::KoenigGraph& g2, std::vector<int>& in2);
        static std::vector<std::vector<int>> GenerateSignals(const std::vector<int>& inputs, const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, const GIS_Data::Config& config);
        //static void CorrectPower(const std::vector<int> inputs, std::vector<std::vector<int>> signals, );
        static std::vector<std::pair<std::vector<int>, std::vector<int>>> MatchElems(const GIS_Data::KoenigGraph& g1, const std::vector<std::vector<int>>& S1, const GIS_Data::KoenigGraph& g2, const std::vector<std::vector<int>>& S2, int quantScale = 1000);
    public:
        std::vector<std::pair<std::vector<int>, std::vector<int>>> Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, const GIS_Data::Config& config) override;
    };
}
