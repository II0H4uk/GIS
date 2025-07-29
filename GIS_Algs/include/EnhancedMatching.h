#pragma once

#include <BipartGraph.h>

namespace GIS_Algs {

    class EnhancedMatching {
    private:
        static std::vector<std::vector<int>> CreateChainGraph(const GIS_Data::KoenigGraph& kGraph);
        static std::vector<int> CalcAdjLv(std::vector<std::vector<int>>& adjList, std::vector<std::vector<int>>& adjListT);
        static std::vector<int> FindStart(std::vector<std::vector<int>>& adjListT);
        static std::vector<std::vector<int>> TranspAdjList(const std::vector<std::vector<int>>& chGraph);
        static std::vector<std::vector<double>> CalcWeights(const std::vector<std::vector<int>>& adjList1, const std::vector<int>& adjLv1, const std::vector<std::vector<int>>& adjList2, const std::vector<int>& adjLv2);
        static std::vector<std::pair<int, int>> CalcDeg(const std::vector<std::vector<int>>& adjList, const std::vector<std::vector<int>>& adjListT, int chainCount);
        static double EuclidDist(const std::pair<int, int>& p1, const std::pair<int, int>& p2);
        static std::vector<int> MatchLevels(std::vector<std::vector<double>>& weights);
        static std::vector<std::pair<int, std::vector<int>>> MatchChains(const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2);
        static void CorrectBGraph(GIS_Data::BipartGraph& bGraph, const std::vector<std::vector<int>>& adjList1, const std::vector<std::vector<int>>& adjList2, std::vector<std::pair<int, std::vector<int>>>& chainMatch);
    public:
        static std::vector<std::pair<int, int>> Start(const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2, GIS_Data::BipartGraph& bGraph);
    };
}
