#pragma once

#include <KoenigGraph.h>
#include <random>

namespace GIS_Algs {
    class SignalMatching {
    private:
        static std::vector<int> GetInputNets(const GIS_Data::KoenigGraph& g);
        static std::vector<int> GetTopoOrder(const GIS_Data::KoenigGraph& g, const std::vector<int>& inputs);
        static std::vector<int> HungarianAlg(const std::vector<std::vector<double>>& cost);
        static std::vector<int> GetInputSign(const GIS_Data::KoenigGraph& g, const std::unordered_set<char>& allTypes, int inputNet, int maxDepth = 3);
        static double L2(const std::vector<int>& a, const std::vector<int>& b);
        static std::vector<double> SimulateOnce(const GIS_Data::KoenigGraph& g, const std::vector<int>& topoOrder, const std::vector<int>& inputNets, const std::vector<double>& inputBits);
        static std::vector<std::vector<double>> RunStochastic(const GIS_Data::KoenigGraph& g, const std::vector<int>& topoOrder, const std::vector<int>& inputNetsG, int iterations, std::vector<std::vector<double>>& inputBits);
        static std::string QuantKey(const std::vector<double>& sig, int scale = 1000);
        static void MatchInputs(const GIS_Data::KoenigGraph& g1, const std::vector<int>& in1, const GIS_Data::KoenigGraph& g2, std::vector<int>& in2);
        static std::vector<std::vector<double>> GenerateSignals(int inputsCount, int iterations);
        static std::vector<std::pair<int, int>> MatchElems(const GIS_Data::KoenigGraph& g1, const std::vector<std::vector<double>>& S1, const GIS_Data::KoenigGraph& g2, const std::vector<std::vector<double>>& S2, int quantScale = 1000);
    public:
        static std::vector<std::pair<int, int>> Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, int iterations = 64, int quantScale = 1000);
    };
}
