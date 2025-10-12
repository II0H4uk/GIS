#include "pch.h"
#include "EnhancedMatching.h"
#include <unordered_set>
#include <MaxMatching.h>
#include <math.h>

namespace GIS_Algs {

    std::vector<std::pair<std::vector<int>, std::vector<int>>> EnhancedMatching::Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, const GIS_Data::Config& config) {

        GIS_Data::BipartGraph bGraph(g1, g2);

        std::vector<std::unordered_set<int>> chainMatch = MatchChains(g1, g2);

        CorrectBGraph(bGraph, g1, g2, chainMatch);

        MaxMatching alg;
        alg.SetBGraph(bGraph);

        return alg.Start(g1, g2, config);
    }

    void EnhancedMatching::CorrectBGraph(GIS_Data::BipartGraph& bGraph, const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2, std::vector<std::unordered_set<int>>& chainMatch) const {
        
        std::vector<std::vector<int>> bAdjList = bGraph.GetAdjList();
        
        std::vector<int> inChainsSec;
        std::vector<int> outChainsSec;

        std::vector<std::vector<int>> adjList1T1 = TranspAdjList(kGraph1.GetAdjList());
        std::vector<std::vector<int>> adjList1T2 = TranspAdjList(kGraph2.GetAdjList());

        for (int i = 0; i < kGraph1.GetNodeCount(); ++i) {
            for (int j = 0; j < bAdjList[i].size(); ++j) {

                int currNode = bAdjList[i][j] - kGraph1.GetNodeCount();

                for (int k = 0; k < adjList1T1[i].size(); ++k) {
                    if (!(ContainsAny(chainMatch[adjList1T1[i][k] - kGraph1.GetNodeCount()], adjList1T2[currNode]) &&
                        ContainsAny(chainMatch[kGraph1.GetAdjList()[i][k] - kGraph1.GetNodeCount()], kGraph2.GetAdjList()[currNode]))) {
                        bGraph.EraseElem(i, j);
                        j--;
                    }
                }
            }
        }
    }

    bool EnhancedMatching::ContainsAny(const std::unordered_set<int>& set, const std::vector<int>& vec) const {
        return std::any_of(vec.begin(), vec.end(), [&set](int x) {
            return set.count(x) > 0;
        });
    }

    std::vector<std::unordered_set<int>> EnhancedMatching::MatchChains(const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2) const {

        std::vector<std::vector<int>> chGraph1 = CreateChainGraph(kGraph1);
        std::vector<std::vector<int>> chGraph2 = CreateChainGraph(kGraph2);

        std::vector<std::vector<int>> transpAdjList1 = TranspAdjList(chGraph1);
        std::vector<std::vector<int>> transpAdjList2 = TranspAdjList(chGraph2);

        std::vector<int> adjLv1 = CalcAdjLv(chGraph1, transpAdjList1);
        std::vector<int> adjLv2 = CalcAdjLv(chGraph2, transpAdjList2);

        int max1 = *std::max_element(adjLv1.begin(), adjLv1.end());
        int max2 = *std::max_element(adjLv2.begin(), adjLv2.end());

        if (max1 == max2) {
            std::vector<std::unordered_set<int>> matching(chGraph1.size());
            for (int i = 0; i < adjLv1.size(); ++i)
                for (int j = 0; j < adjLv2.size(); ++j)
                    if (adjLv1[i] == adjLv2[j]) {
                        matching[i].insert(j + kGraph2.GetNodeCount());
                    }

            return matching;
        }

        std::vector<std::vector<double>> weights = CalcWeights(kGraph1.GetAdjList(), adjLv1, kGraph2.GetAdjList(), adjLv2);

        std::vector<int> levelMatch = MatchLevels(weights);

        std::vector<std::unordered_set<int>> chainMatch(adjLv1.size());
        for (int i = 0; i < adjLv1.size(); ++i) {
            for (int j = 0; j < adjLv2.size(); ++j) {
                if (levelMatch[adjLv1[i]] == adjLv2[j])
                    chainMatch[i].insert(j + kGraph2.GetNodeCount());
            }
        }

        return chainMatch;
    }

    std::vector<std::vector<int>> EnhancedMatching::CreateChainGraph(const GIS_Data::KoenigGraph& kGraph) const {
        int chCount = kGraph.GetHyperEdgeCount();
        int nCount = kGraph.GetNodeCount();
        std::vector<std::vector<int>> adjList = kGraph.GetAdjList();
        std::vector<std::vector<int>> adjListT = kGraph.TranspAdjList();
        std::vector<std::vector<int>> chGraph(chCount);

        std::queue<int> q;
        std::vector<bool> visited(nCount + chCount);
        q.push(nCount);
        visited[nCount] = true;

        while (!q.empty()) {
            int currNode = q.front();
            q.pop();

            if (currNode > nCount) {

                std::vector<int> parents = adjListT[currNode];
                std::unordered_set<int> chParents;
                for (int i = 0; i < parents.size(); ++i) {
                    for (int j = 0; j < adjListT[parents[i]].size(); ++j) {
                        chParents.insert(adjListT[parents[i]][j]);
                    }
                }
                for (int parent : chParents) {
                    chGraph[parent - nCount].push_back(currNode - nCount);
                }
            }

            for (int i = 0; i < adjList[currNode].size(); ++i) {
                if (visited[adjList[currNode][i]])
                    continue;

                q.push(adjList[currNode][i]);
                visited[adjList[currNode][i]] = true;
            }

        }

        return chGraph;
    }

    std::vector<int> EnhancedMatching::CalcAdjLv(std::vector<std::vector<int>>& adjList, std::vector<std::vector<int>>& adjListT) const {

        std::vector<int> startNodes = FindStart(adjListT);
        int nodeCount = adjList.size();

        std::queue<int> q;
        std::vector<int> visitCount(nodeCount);

        std::vector<int> adjLv(nodeCount, -1);
        for (int i = 0; i < startNodes.size(); ++i) {
            q.push(startNodes[i]);
            adjLv[startNodes[i]] = 0;
        }

        while (!q.empty()) {
            int currNode = q.front();
            q.pop();

            for (int i = 0; i < adjList[currNode].size(); ++i) {
                if (visitCount[adjList[currNode][i]] != adjListT[adjList[currNode][i]].size() - 1) {
                    visitCount[adjList[currNode][i]]++;
                    continue;
                }
                q.push(adjList[currNode][i]);
                adjLv[adjList[currNode][i]] = adjLv[currNode] + 1;
            }
        }

        return adjLv;
    }

    std::vector<int> EnhancedMatching::FindStart(std::vector<std::vector<int>>& adjListT) const {

        std::vector<int> startNodes;
        for (int i = 0; i < adjListT.size(); ++i)
            if (adjListT[i].size() == 0)
                startNodes.push_back(i);

        return startNodes;
    }

    std::vector<std::vector<int>> EnhancedMatching::TranspAdjList(const std::vector<std::vector<int>>& chGraph) const {
        std::vector<std::vector<int>> revList(chGraph.size());
        for (int i = 0; i < chGraph.size(); ++i) {
            for (int j = 0; j < chGraph[i].size(); ++j) {
                revList[chGraph[i][j]].push_back(i);
            }
        }

        return revList;
    }
    
    std::vector<std::vector<double>> EnhancedMatching::CalcWeights(const std::vector<std::vector<int>>& adjList1, const std::vector<int>& adjLv1, const std::vector<std::vector<int>>& adjList2, const std::vector<int>& adjLv2) const {
        
        int max1 = *std::max_element(adjLv1.begin(), adjLv1.end());
        int max2 = *std::max_element(adjLv2.begin(), adjLv2.end());

        std::vector<std::vector<int>> adjListT1 = TranspAdjList(adjList1);
        std::vector<std::vector<int>> adjListT2 = TranspAdjList(adjList2);

        std::vector<std::pair<int, int>> nodeDeg1 = CalcDeg(adjList1, adjListT1, adjLv1.size());
        std::vector<std::pair<int, int>> nodeDeg2 = CalcDeg(adjList2, adjListT2, adjLv2.size());

        std::vector<std::pair<int, int>> lvDeg1(max1 + 1);
        std::vector<std::pair<int, int>> lvDeg2(max2 + 1);

        for (int i = 0; i < adjLv1.size(); ++i) {
            lvDeg1[adjLv1[i]].first += nodeDeg1[i].first;
            lvDeg1[adjLv1[i]].second += nodeDeg1[i].second;
        }

        for (int i = 0; i < adjLv2.size(); ++i) {
            lvDeg2[adjLv2[i]].first += nodeDeg2[i].first;
            lvDeg2[adjLv2[i]].second += nodeDeg2[i].second;
        }

        std::vector<std::vector<double>> weights(lvDeg1.size(), std::vector<double>(lvDeg2.size()));

        for (int i = 0; i < weights.size(); ++i) {
            for (int j = 0; j < weights[i].size(); ++j) {
                weights[i][j] = EuclidDist(lvDeg1[i], lvDeg2[j]);
            }
        }

        return weights;
    }

    std::vector<std::pair<int, int>> EnhancedMatching::CalcDeg(const std::vector<std::vector<int>>& adjList, const std::vector<std::vector<int>>& adjListT, int chainCount) const {
        std::vector<std::pair<int, int>> deg(chainCount);
        int nodeCount = adjList.size() - chainCount;

        for (int i = 0; i < deg.size(); ++i) {
            deg[i] = { adjListT[nodeCount + i].size(), adjList[nodeCount + i].size()};
        }

        return deg;
    }

    double EnhancedMatching::EuclidDist(const std::pair<int, int>& p1, const std::pair<int, int>& p2) const {
        return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
    }

    std::vector<int> EnhancedMatching::MatchLevels(std::vector<std::vector<double>>& weights) const {

        std::vector<int> selected_columns(weights.size(), -1);
        selected_columns[0] = 0;

        int prev_j = 1;

        for (int i = 1; i < weights.size(); ++i) {

            double min_val = std::numeric_limits<double>::max();
            int best_j = -1;
            for (int j = prev_j; j < weights[i].size(); ++j) {
                if (weights[i][j] < min_val) {
                    min_val = weights[i][j];
                    best_j = j;
                }
            }

            if (best_j == -1) {
                best_j = weights[i].size() - 1;
            }

            selected_columns[i] = best_j;
            prev_j = best_j;
        }

        return selected_columns;
    }
}
