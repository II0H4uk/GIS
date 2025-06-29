#include "pch.h"
#include "TruncEnum.h"

namespace GIS_Algs {

    bool TruncEnum::Start(const GIS_Data::Graph& g1, const GIS_Data::Graph& g2) {
        if (g1.GetNodeCount() != g2.GetNodeCount()) return false;

        std::vector<int> mapping(g1.GetNodeCount(), -1);
        std::vector<bool> used(g2.GetNodeCount(), false);

        return CompareGraphs(g1, g2, mapping, used, 0);
    }

    bool TruncEnum::CompareGraphs(const GIS_Data::Graph& g1, const GIS_Data::Graph& g2, std::vector<int>& mapping, std::vector<bool>& used, int depth) {
        if (depth == g1.GetNodeCount()) {

            for (int i = 0; i < g1.GetNodeCount(); ++i) {
                std::vector<int> mappedNeighbors;
                for (int neighbor : g1.GetAdjList()[i]) {
                    mappedNeighbors.push_back(mapping[neighbor]);
                }
                std::sort(mappedNeighbors.begin(), mappedNeighbors.end());

                std::vector<int> neighbors2 = g2.GetAdjList()[mapping[i]];
                std::sort(neighbors2.begin(), neighbors2.end());

                if (mappedNeighbors != neighbors2) return false;
            }
            return true;
        }

        for (int i = 0; i < g2.GetNodeCount(); ++i) {
            if (used[i]) continue;

            if (g1.GetAdjList()[depth].size() != g2.GetAdjList()[i].size()) continue;

            int retFlag;
            CompareTags(g1, depth, g2, i, retFlag);
            if (retFlag == 3) continue;

            bool boolFlag;
            bool retVal = TryToMatchNodes(mapping, depth, i, used, g1, g2, boolFlag);
            if (boolFlag) return retVal;
        }
        return false;
    }

    bool TruncEnum::TryToMatchNodes(std::vector<int>& mapping, int depth, int i, std::vector<bool>& used, const GIS_Data::Graph& g1, const GIS_Data::Graph& g2, bool& retFlag)
    {
        retFlag = true;
        mapping[depth] = i;
        used[i] = true;

        if (CompareGraphs(g1, g2, mapping, used, depth + 1)) return true;

        used[i] = false;
        retFlag = false;
        return {};
    }

    void TruncEnum::CompareTags(const GIS_Data::Graph& g1, int depth, const GIS_Data::Graph& g2, int i, int& retFlag)
    {
        retFlag = 1;
        const auto& tags1 = g1.GetTag()[depth];
        const auto& tags2 = g2.GetTag()[i];

        if (tags1.size() != tags2.size()) { retFlag = 3; return; };
        bool tagsEqual = true;
        for (size_t j = 0; j < tags1.size(); ++j) {
            if (!GIS_Data::CompareTags(tags1[j], tags2[j])) {
                tagsEqual = false;
                break;
            }
        }
        if (!tagsEqual) { retFlag = 3; return; };
    }
}
