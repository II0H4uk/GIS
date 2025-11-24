#include "pch.h"
#include <TopologyFilter.h>

namespace GIS_Algs {
    MapSet TopologyFilter::Start(const GIS_Data::KoenigGraph& g, const MapSet& map) {

        MapSet filtMap;

        for (int i = 0; i < map.size(); ++i) {

            if (map[i].first.size() == 1 && map[i].second.size() == 1) {
                filtMap.push_back(map[i]);
                continue;
            }

            Tensor3 nodeSignsFirst;
            Tensor3 nodeSignsSecond;

            for (int j = 0; j < map[i].first.size(); ++j)
                nodeSignsFirst.push_back(BFS(g.GetAdjList(), map[i].first[j], map, 1, true));

            for (int j = 0; j < map[i].second.size(); ++j)
                nodeSignsSecond.push_back(BFS(g.GetAdjList(), map[i].second[j], map, 1, false));

            ResolveSets(nodeSignsFirst, nodeSignsSecond, map[i], filtMap);
        }

        return filtMap;
    }

    std::vector<std::vector<int>> TopologyFilter::BFS(const std::vector<std::vector<int>>& adjList, int node, const MapSet& map, int maxDepth, bool firstSide) {

        std::vector<std::vector<int>> sign(maxDepth + 1);
        std::queue<std::pair<int, int>> q;
        q.push({node, 0});

        while (!q.empty()) {
            auto currNode = q.front(); q.pop();

            sign[currNode.second].push_back(FindMapping(currNode.first, map, firstSide));

            if (currNode.second + 1 <= maxDepth) {
                for(int nextNode : adjList[currNode.first]) {
                    q.push({ nextNode, currNode.second + 1});
                }
            }
        }

        return sign;
    }

    int TopologyFilter::FindMapping(int currNode, const MapSet& mapSet, bool firstSide) {
        
        for (int i = 0; i < mapSet.size(); ++i) {
            if ((firstSide && std::find(mapSet[i].first.begin(), mapSet[i].first.end(), currNode) != mapSet[i].first.end()) ||
                (!firstSide && std::find(mapSet[i].second.begin(), mapSet[i].second.end(), currNode) != mapSet[i].second.end()))
                return i;
        }

        return -1;
    }

    void TopologyFilter::ResolveSets(const Tensor3& set1, const Tensor3& set2, const std::pair<std::vector<int>, std::vector<int>>& localMap, MapSet& filtMap) {

        std::vector<bool> used(set2.size(), false);

        for (int i = 0; i < set1.size(); ++i) {
            for (int j = 0; j < set2.size(); ++j) {
                if (used[j] || !AreSimilar(set1[i], set2[j]))
                    continue;
                filtMap.push_back({ { localMap.first[i] }, { localMap.second[j] } });
                used[j] = true;
                break;
            }
        }
    }

    bool TopologyFilter::AreSimilar(const std::vector<std::vector<int>>& sign1, const std::vector<std::vector<int>>& sign2) {

        if (sign1.size() != sign2.size())
            return false;

        for (int i = 0; i < sign1.size(); ++i) {
            if (sign1[i].size() != sign2[i].size())
                return false;

            for (int j = 0; j < sign1[i].size(); ++j) {
                if (sign1[i][j] != sign2[i][j])
                    return false;
            }
        }

        return true;
    }
}
