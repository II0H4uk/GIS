#include "pch.h"
#include "ConfigParser.h"
#include "GraphParser.h"
#include "BruteForce.h"
#include "Statistics.h"

int main(int argc, char* argv[]) {

    GIS_Data::Config config = GIS_Parser::Config::Parse("../config.ini");

    GIS_Data::Graph graph = GIS_Parser::Graph::Parse(config.GetInput());

    auto start = std::chrono::high_resolution_clock::now();
    bool result = GIS_Algs::BruteForce::Start(graph);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    GIS_Stats::Statistics::Save(duration.count(), result, graph.GetNodeCount());

    //std::cout << duration;
    return 0;
}
