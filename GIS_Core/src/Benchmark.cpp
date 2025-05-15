#include "pch.h"
#include "Benchmark.h"
#include "SubGraphIso.h"
#include "Statistics.h"
#include "HyperGtaphToGraph.h"
#include "Generator.h"
#include "GraphParser.h"

namespace GIS_Core {

    void Benchmark::Init(const GIS_Data::Config config) {

        auto [pair, fixedNodes1, fixedNodes2] = ReadHyperGraphs(config.GetInput1(), config.GetInput2(), true);
        //CorrectGraphsNodes(pair.GetGraph1(), pair.GetGraph2());

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> result = GIS_Algs::SubGraphIso::Start(pair.GetGraph1(), pair.GetGraph2(), fixedNodes);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        GIS_Stats::Statistics::Save(duration.count(), result, pair.GetGraph1().GetNodeCount(), config.GetOutput());
    }

    void Benchmark::CorrectGraphsNodes(GIS_Data::Graph& graph1, GIS_Data::Graph& graph2) {
        int nodeCount1 = graph1.GetNodeCount();
        int nodeCount2 = graph2.GetNodeCount();

        if (nodeCount1 == nodeCount2)
            return;

        if (nodeCount1 > nodeCount2)
            graph2.AddEmptyNodes(nodeCount1 - nodeCount2);
        else
            graph1.AddEmptyNodes(nodeCount2 - nodeCount1);
    }

    GIS_Data::GraphPair Benchmark::ReadGraphs(const std::string& input1, const std::string& input2, bool isomorph) {

        GIS_Data::Graph graph1 = GIS_Parser::Graph::Parse(input1);
        GIS_Data::Graph graph2 = GIS_Parser::Graph::Parse(input2);
        return GIS_Data::GraphPair(graph1, graph2, isomorph);
    }

    std::tuple<GIS_Data::GraphPair, std::vector<int>, std::vector<int>> Benchmark::ReadHyperGraphs(const std::string& input1, const std::string& input2, bool isomorph) {

        auto [graph1, fixNodes1] = GIS_Parser::HyperGraphToGraph::Convert(input1);
        auto [graph2, fixNodes2] = GIS_Parser::HyperGraphToGraph::Convert(input2);
        return { GIS_Data::GraphPair(graph1, graph2, isomorph), fixNodes1, fixNodes2 };
    }

    GIS_Data::GraphPair Benchmark::GenGraphs(int nodeCount, bool isomorph) {

        GIS_Generator::Generator generator;
        return generator.GenerateGraphPair(nodeCount, isomorph);
    }
}
