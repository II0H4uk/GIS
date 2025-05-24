#include "pch.h"
#include "Benchmark.h"
#include "SubGraphIso.h"
#include "Statistics.h"
#include "HyperGtaphToGraph.h"
#include "Generator.h"
#include "GraphParser.h"

namespace GIS_Core {

    void Benchmark::Init(const GIS_Data::Config config) {

        //auto [pair, fixedNodes1, fixedNodes2] = ReadHyperGraphs(config.GetInput1(), config.GetInput2());
        GIS_Data::GraphPair pair = GenGraphs(10000, 7000, 20);
        NormalizeGraphs(pair.GetGraph1(), pair.GetGraph2());

        std::vector<int> matching = GIS_Algs::SubGraphIso::Start(pair.GetGraph1(), pair.GetGraph2());

        int correctCount = 0;

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

        std::cout << "Accuracy = " << (double)correctCount / matching.size() << "\n";
    }

    GIS_Data::GraphPair Benchmark::ReadGraphs(const std::string& input1, const std::string& input2) {

        GIS_Data::Graph graph1 = GIS_Parser::Graph::Parse(input1);
        GIS_Data::Graph graph2 = GIS_Parser::Graph::Parse(input2);
        return GIS_Data::GraphPair(graph1, graph2, std::vector<int>());
    }

    void Benchmark::NormalizeGraphs(GIS_Data::Graph& g1, GIS_Data::Graph& g2) {
        int g1Size = g1.GetAdjList().size();
        int g2Size = g2.GetAdjList().size();

        (g1Size > g2Size ? g2 : g1).NormalizeGraph(std::abs(g1Size - g2Size));
    }

    std::tuple<GIS_Data::GraphPair, std::vector<int>, std::vector<int>> Benchmark::ReadHyperGraphs(const std::string& input1, const std::string& input2) {

        auto [graph1, fixNodes1] = GIS_Parser::HyperGraphToGraph::Convert(input1);
        auto [graph2, fixNodes2] = GIS_Parser::HyperGraphToGraph::Convert(input2);
        return { GIS_Data::GraphPair(graph1, graph2, std::vector<int>()), fixNodes1, fixNodes2 };
    }

    GIS_Data::GraphPair Benchmark::GenGraphs(int nodeCount, int numCliques, int maxClSize) {

        GIS_Generator::Generator generator;
        return generator.GenerateGraphPair(nodeCount, numCliques, maxClSize);
    }
}
