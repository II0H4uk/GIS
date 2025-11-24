#pragma once

#include <vector>
#include <KoenigGraph.h>

namespace GIS_Algs {

    using MapSet = std::vector<std::pair<std::vector<int>, std::vector<int>>>;
    using Tensor3 = std::vector<std::vector<std::vector<int>>>;

    class TopologyFilter {
    private:
        static std::vector<std::vector<int>> BFS(const std::vector<std::vector<int>>& adjList, int node, const MapSet& map, int maxDepth, bool firstSide);
        static int FindMapping(int currNode, const MapSet& map, bool firstSide);
        static void ResolveSets(const Tensor3& set1, const Tensor3& set2, const std::pair<std::vector<int>, std::vector<int>>& map, MapSet& filtMap);
        static bool AreSimilar(const std::vector<std::vector<int>>& sign1, const std::vector<std::vector<int>>& sign2);
    public:
        static MapSet Start(const GIS_Data::KoenigGraph& g, const MapSet& map);
    };
}
