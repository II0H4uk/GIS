#include "pch.h"
#include "ConfigParser.h"
#include "GraphParser.h"
#include "BruteForce.h"
#include "Statistics.h"

int main(int argc, char* argv[]) {

    GIS_Data::Config config = GIS_Parser::Config::Parse("../config.ini");

    GIS_Data::Graph graph1 = GIS_Parser::Graph::Parse(config.GetInput1());
    GIS_Data::Graph graph2 = GIS_Parser::Graph::Parse(config.GetInput2());

    auto start = std::chrono::high_resolution_clock::now();
    bool result = GIS_Algs::BruteForce::Start(graph1,graph2);
    auto end = std::chrono::high_resolution_clock::now();
    
    //std::cout << result;
    std::chrono::duration<double> duration = end - start;

    GIS_Stats::Statistics::Save(duration.count(), result, graph1.GetNodeCount(), config.GetOutput());

    //std::cout << duration;
    return 0;
}
