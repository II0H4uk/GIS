#pragma once

#include <BipartGraph.h>
#include <Config.h>
#include <AlgStrat.h>
#include <unordered_set>

namespace GIS_Algs {

    class EnhancedMatching : public AlgStrat {
    private:
        std::vector<std::vector<int>> CreateChainGraph(const GIS_Data::KoenigGraph& kGraph) const;
        std::vector<int> CalcAdjLv(std::vector<std::vector<int>>& adjList, std::vector<std::vector<int>>& adjListT) const;
        std::vector<int> FindStart(std::vector<std::vector<int>>& adjListT) const;
        std::vector<std::vector<int>> TranspAdjList(const std::vector<std::vector<int>>& chGraph) const;
        std::vector<std::vector<double>> CalcWeights(const std::vector<std::vector<int>>& adjList1, const std::vector<int>& adjLv1, const std::vector<std::vector<int>>& adjList2, const std::vector<int>& adjLv2) const;
        std::vector<std::pair<int, int>> CalcDeg(const std::vector<std::vector<int>>& adjList, const std::vector<std::vector<int>>& adjListT, int chainCount) const;
        double EuclidDist(const std::pair<int, int>& p1, const std::pair<int, int>& p2) const;
        std::vector<int> MatchLevels(std::vector<std::vector<double>>& weights) const;
        std::vector<std::unordered_set<int>> MatchChains(const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2) const;
        void CorrectBGraph(GIS_Data::BipartGraph& bGraph, const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2, std::vector<std::unordered_set<int>>& chainMatch) const;
        std::vector<int> GetAllNodes(int offset, const std::vector<int>& adjNodes1, const std::vector<int>& adjNodes2, const std::vector<std::unordered_set<int>>& chainMatch) const;
        bool ContainsAny(const std::unordered_set<int>& set, const std::vector<int>& vec) const;
    public:
        std::vector<std::pair<std::vector<int>, std::vector<int>>> Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, const GIS_Data::Config& config) override;
    };
}
