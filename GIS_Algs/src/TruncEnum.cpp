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


            const auto& tags1 = g1.GetTag()[depth];
            const auto& tags2 = g2.GetTag()[i];

            if (tags1.size() != tags2.size()) continue;
            bool tagsEqual = true;
            for (size_t j = 0; j < tags1.size(); ++j) {
                if (!GIS_Data::CompareTags(tags1[j], tags2[j])) {
                    tagsEqual = false;
                    break;
                }
            }
            if (!tagsEqual) continue;

            mapping[depth] = i;
            used[i] = true;

            if (CompareGraphs(g1, g2, mapping, used, depth + 1)) return true;

            used[i] = false;
        }
        return false;
    }
}
