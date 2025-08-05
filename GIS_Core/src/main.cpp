#include "pch.h"
#include "Benchmark.h"
#include "ConfigParser.h"
#include <Subcircuit.h>
#include <SpiceParser.h>
#include <BipartGraph.h>
#include <MaxMatching.h>
#include <EnhancedMatching.h>
#include <algorithm>

int main(int argc, char* argv[]) {

    GIS_Data::Config config = GIS_Parser::Config::Parse("../config.ini");
    Circuits::Utils::SpiceParser parser;

    Circuits::Utils::Subcircuit circuit1 = parser.ParseSPICE(config.GetInput1());
    Circuits::Utils::Subcircuit circuit2 = parser.ParseSPICE(config.GetInput2());

    GIS_Data::KoenigGraph koenG1(circuit1, 2);
    GIS_Data::KoenigGraph koenG2(circuit2, 2);
    GIS_Data::GraphPair pair(koenG1, koenG2, {});

    GIS_Data::BipartGraph bGraph = GIS_Data::BipartGraph(pair);

    //отображение двудольного графа
    /*for (int i = 0; i < bGraph.GetAdjList().size(); ++i) {
        std::cout << i << ": ";
        for (int j = 0; j < bGraph.GetAdjList()[i].size(); ++j) {
            std::cout << bGraph.GetAdjList()[i][j] << ", ";
        }
        std::cout << "\n";
    }*/

    std::vector<std::pair<int, int>> result = GIS_Algs::EnhancedMatching::Start(koenG1, koenG2, bGraph);
    std::sort(result.begin(), result.end());

    for (int i = 0; i < result.size(); ++i) {
        if (result[i].first >= koenG1.GetNodeCount())
            break;
        std::cout << result[i].first << " -> " << result[i].second - koenG1.GetNodeCount() << "\n";
    }

    return 0;
}
