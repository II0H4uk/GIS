#include "pch.h"
#include "Benchmark.h"
#include "SubGraphIso.h"
#include "Statistics.h"
#include "HyperGtaphToGraph.h"
#include "Generator.h"
#include "GraphParser.h"
#include "KoenigGraph.h"
#include "BipartGraph.h"
#include "MaxMatching.h"

namespace GIS_Core {

    void Benchmark::Init(const GIS_Data::Config config) {

        //auto [pair, fixedNodes1, fixedNodes2] = ReadHyperGraphs(config.GetInput1(), config.GetInput2());
        //GIS_Data::GraphPair pair = GenGraphs(10000, 7000, 20);

        GIS_Data::GraphPair pair = ReadHyperGraphs(config.GetInput1(), config.GetInput2(), 2);
        NormalizeGraphs(pair.GetGraph1(), pair.GetGraph2());
        
        GIS_Data::BipartGraph bipartGraph(pair.GetGraph1().GetTags(), pair.GetGraph2().GetTags());
        std::vector<int> matching = GIS_Algs::MaxMatching::Start(bipartGraph);

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
        int g1Nodes = g1.GetNodeCount();
        int g2Nodes = g2.GetNodeCount();
        int g1Edges = g1.GetHyperEdgeCount();
        int g2Edges = g2.GetHyperEdgeCount();

        Normalize(g1, g2, g1Nodes, g2Nodes, g2Nodes, g1Nodes, true);
        Normalize(g1, g2, g1Edges, g2Edges, g2Nodes + g2Edges, g1Nodes + g1Edges, false);
    }

    void Benchmark::Normalize(GIS_Data::KoenigGraph& g1, GIS_Data::KoenigGraph& g2, int g1Nodes, int g2Nodes, int offset1, int offset2, bool isNode) {
        if (g1Nodes > g2Nodes)
            g2.NormalizeGraph(g1Nodes - g2Nodes, offset1, isNode);
        else
            g1.NormalizeGraph(g2Nodes - g1Nodes, offset2, isNode);
    }

    GIS_Data::GraphPair Benchmark::ReadHyperGraphs(const std::string& input1, const std::string& input2, int tagsLevel) {

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
    }

    GIS_Data::GraphPair Benchmark::GenGraphs(int nodeCount, int numCliques, int maxClSize) {

        GIS_Generator::Generator generator;
        return generator.GenerateGraphPair(nodeCount, numCliques, maxClSize);
    }
}
