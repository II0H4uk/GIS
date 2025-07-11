#include "pch.h"
#include "Benchmark.h"
#include "ConfigParser.h"
#include <Subcircuit.h>
#include <SpiceParser.h>
#include <BipartGraph.h>
#include <MaxMatching.h>

int main(int argc, char* argv[]) {

    GIS_Data::Config config = GIS_Parser::Config::Parse("../config.ini");
    Circuits::Utils::SpiceParser parser;

    Circuits::Utils::Subcircuit circuit1 = parser.ParseSPICE(config.GetInput1());
    Circuits::Utils::Subcircuit circuit2 = parser.ParseSPICE(config.GetInput2());

    GIS_Data::KoenigGraph koenG1(circuit1, 2);
    GIS_Data::KoenigGraph koenG2(circuit2, 2);
    GIS_Data::GraphPair pair(koenG1, koenG2, {});

    GIS_Core::Benchmark::NormalizeGraphs(pair.GetGraph1(), pair.GetGraph2());

    GIS_Data::BipartGraph bGraph(pair);
    std::vector<std::pair<int, int>> matching = GIS_Algs::MaxMatching::Start(bGraph, 100);

    return 0;
}
