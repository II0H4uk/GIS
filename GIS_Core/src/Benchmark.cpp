#include "pch.h"
#include "Benchmark.h"
#include "Statistics.h"
#include "Generator.h"
#include "KoenigGraph.h"
#include "BipartGraph.h"
#include "MaxMatching.h"
#include "ValidateMatch.h"
#include <EnhancedMatching.h>
#include <SignalMatching.h>
#include <queue>

namespace GIS_Core {

    int CountLevels(const std::vector<std::vector<int>>& adjList,
        const std::vector<int>& startVertices) {
        int n = (int)adjList.size();
        std::vector<char> visited(n, 0);
        std::queue<int> q;

        // ��������� ��������� �������
        for (int s : startVertices) {
            if (!visited[s]) {
                visited[s] = 1;
                q.push(s);
            }
        }

        int levels = 0;
        while (!q.empty()) {
            int sz = (int)q.size();
            // ������������ ���� �������
            for (int i = 0; i < sz; ++i) {
                int u = q.front(); q.pop();
                for (int v : adjList[u]) {
                    if (!visited[v]) {
                        visited[v] = 1;
                        q.push(v);
                    }
                }
            }
            ++levels;
        }

        return levels;
    }

    void Benchmark::SignalMatching(const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2) {/*
        int a = 0;
        int b = 0;
        int c = 0;
        for (int i = 0; i < kGraph1.GetNodeCount(); ++i) {
            if (kGraph1.GetAdjListT()[i].size() == 1)
                a++;
            if (kGraph1.GetAdjListT()[i].size() == 2)
                b++;
            if (kGraph1.GetAdjListT()[i].size() == 3)
                c++;
        }*/

        int levels = CountLevels(kGraph1.GetAdjList(), kGraph1.GetInputChains());

        std::vector<std::pair<std::vector<int>, std::vector<int>>> clusters = GIS_Algs::SignalMatching::Start(kGraph1, kGraph2, 64, 1000);

        auto [mapping, reliableCount] = GIS_Algs::SignalMatching::MatchFromClusters(clusters);
        //проверка здесь



        /*for (int i = 0; i < result.size(); ++i) {
            if (result[i].first >= kGraph1.GetNodeCount())
                break;
            std::cout << result[i].first << " -> " << result[i].second << "\n";
        }*/

        int count = 0;
        for (int i = 0; i < clusters.size(); ++i) if (clusters[i].first == clusters[i].second) count++;

        std::cout << "Node count:" << kGraph1.GetNodeCount();
        std::cout << "\nChain count:" << kGraph1.GetHyperEdgeCount();
        std::cout << "\nSame numers match count:" << count;
        std::cout << "\nResult size:" << clusters.size() << "\n";
    }

    void Benchmark::MaxMatching(const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2) {

        GIS_Data::BipartGraph bGraph = GIS_Data::BipartGraph(kGraph1, kGraph2);

        //����������� ����������� �����
        /*for (int i = 0; i < bGraph.GetAdjList().size(); ++i) {
            std::cout << i << ": ";
            for (int j = 0; j < bGraph.GetAdjList()[i].size(); ++j) {
                std::cout << bGraph.GetAdjList()[i][j] << ", ";
            }
            std::cout << "\n";
        }*/

        std::vector<std::pair<int, int>> result = GIS_Algs::EnhancedMatching::Start(kGraph1, kGraph2, bGraph);
        std::sort(result.begin(), result.end());

        for (int i = 0; i < result.size(); ++i) {
            if (result[i].first >= kGraph1.GetNodeCount())
                break;
            std::cout << result[i].first << " -> " << result[i].second - kGraph1.GetNodeCount() << "\n";
        }



        //auto [pair, fixedNodes1, fixedNodes2] = ReadHyperGraphs(config.GetInput1(), config.GetInput2());
        //GIS_Data::GraphPair pair = GenGraphs(10000, 7000, 20);

        /*GIS_Data::GraphPair pair = ReadHyperGraphs(config.GetInput1(), config.GetInput2(), 2);    ---
        NormalizeGraphs(pair.GetGraph1(), pair.GetGraph2());
        
        GIS_Data::BipartGraph bipartGraph(pair.GetGraph1().GetElements(), pair.GetGraph1().GetElements());
        std::vector<std::pair<int, int>> matching = GIS_Algs::MaxMatching::Start(bipartGraph, 100);

        ValidateMatch::Start(pair, matching);*/ //---
        /*int correctCount = 0;

        std::cout << "Bijection (G1 -> G2):\n";
        for (int i = 0; i < matching.size(); ++i) {
            std::cout << "G1[" << i << "] - G2[" << matching[i] << "]\n";
            if (pair.GetBijection().size() > 0 && matching[i] == pair.GetBijection()[i])
                correctCount++;
        }

        std::cout << "\n\nOriginal bijection (G1 -> G2):\n";
        for (int i = 0; i < pair.GetBijection().size(); ++i) {
            std::cout << "G1[" << i << "] - G2[" << pair.GetBijection()[i] << "]\n";
        }

        std::cout << "Accuracy = " << (double)correctCount / matching.size() << "\n";*/
    }

    /*GIS_Data::GraphPair Benchmark::ReadGraphs(const std::string& input1, const std::string& input2) {

        GIS_Data::Graph graph1 = GIS_Parser::Graph::Parse(input1);
        GIS_Data::Graph graph2 = GIS_Parser::Graph::Parse(input2);
        return GIS_Data::GraphPair(graph1, graph2, std::vector<int>());
    }*/

    void Benchmark::NormalizeGraphs(GIS_Data::KoenigGraph& g1, GIS_Data::KoenigGraph& g2) {
        if (g1.GetNodeCount() != g2.GetNodeCount())
            Normalize(g1, g2, g1.GetNodeCount(), g2.GetNodeCount(), g2.GetNodeCount(), g1.GetNodeCount(), true);
        if (g1.GetHyperEdgeCount() != g2.GetHyperEdgeCount())
            Normalize(g1, g2, g1.GetHyperEdgeCount(), g2.GetHyperEdgeCount(), g2.GetNodeCount() + g2.GetHyperEdgeCount(), g1.GetNodeCount() + g1.GetHyperEdgeCount(), false);
    }

    void Benchmark::Normalize(GIS_Data::KoenigGraph& g1, GIS_Data::KoenigGraph& g2, int g1Nodes, int g2Nodes, int offset1, int offset2, bool isNode) {
        if (g1Nodes > g2Nodes)
            g2.NormalizeGraph(g1Nodes - g2Nodes, offset1, isNode);
        else
            g1.NormalizeGraph(g2Nodes - g1Nodes, offset2, isNode);
    }

    /*GIS_Data::GraphPair Benchmark::ReadHyperGraphs(const std::string& input1, const std::string& input2, int tagsLevel) {

        std::vector<std::vector<int>> netList1 = GIS_Parser::Graph::ReadData(input1);
        std::vector<std::vector<int>> netList2 = GIS_Parser::Graph::ReadData(input2);

        if (netList1[1].size() != netList2[1].size())
            std::cout << "error: incorrect data" << std::endl;

        std::vector<std::pair<int, int>> fixNodes(netList1[1].size());
        for (int i = 0; i < fixNodes.size(); ++i)
            fixNodes[i] = std::pair(netList1[1][i], netList2[1][i]);

        netList1.erase(netList1.begin(), netList1.begin() + 2);
        netList2.erase(netList2.begin(), netList2.begin() + 2);

        return GIS_Data::GraphPair(GIS_Data::KoenigGraph(netList1, tagsLevel), GIS_Data::KoenigGraph(netList2, tagsLevel), fixNodes);
    }*/

    /*GIS_Data::GraphPair Benchmark::GenGraphs(int nodeCount, int numCliques, int maxClSize) {

        GIS_Generator::Generator generator;
        return generator.GenerateGraphPair(nodeCount, numCliques, maxClSize);
    }*/
}
