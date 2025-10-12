#pragma once

#include <KoenigGraph.h>
#include <AlgStrat.h>
#include <random>

namespace GIS_Algs {
    class SignalMatching : public AlgStrat {
    private:
        static int FindId(const std::vector<std::string>& netNames, const std::string& name, int n);
        static std::vector<int> GetInputNets(const GIS_Data::KoenigGraph& g);
        static std::vector<int> GetTopoOrder(const GIS_Data::KoenigGraph& g, const std::vector<int>& inputs);
        static std::vector<int> HungarianAlg(const std::vector<std::vector<double>>& cost);
        static std::vector<int> GetInputSign(const GIS_Data::KoenigGraph& g, const std::unordered_set<char>& allTypes, int inputNet, int maxDepth = 3);
        static double L2(const std::vector<int>& a, const std::vector<int>& b);
        static std::vector<int> SimulateOnce(const GIS_Data::KoenigGraph& g, const std::vector<int>& topoOrder, const std::vector<int>& inputNets, const std::vector<int>& inputBits);
        static std::vector<std::vector<int>> RunStochastic(const GIS_Data::KoenigGraph& g, const std::vector<int>& topoOrder, const std::vector<int>& inputNetsG, int iterations, std::vector<std::vector<int>>& inputBits);
        static std::string QuantKey(const std::vector<int>& sig, int scale = 1000);
        static void MatchInputs(const GIS_Data::KoenigGraph& g1, const std::vector<int>& in1, const GIS_Data::KoenigGraph& g2, std::vector<int>& in2);
        static std::vector<std::vector<int>> GenerateSignals(int inputsCount, int iterations, const std::vector<int>& vdd, const std::vector<int>& gnd);
        static std::vector<std::pair<std::vector<int>, std::vector<int>>> MatchElems(const GIS_Data::KoenigGraph& g1, const std::vector<std::vector<int>>& S1, const GIS_Data::KoenigGraph& g2, const std::vector<std::vector<int>>& S2, int quantScale = 1000);
    public:
        std::vector<std::pair<std::vector<int>, std::vector<int>>> Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, const GIS_Data::Config& config) override;
    };
}
