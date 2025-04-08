#include "pch.h"
#include "ConfigParser.h"
#include "GraphParser.h"
#include "BruteForce.h"
#include "TruncEnum.h"
#include "Statistics.h"
#include "Generator.h"

int main(int argc, char* argv[]) {

    GIS_Data::Config config = GIS_Parser::Config::Parse("../config.ini");

    GIS_Generator::Generator genertor;
    GIS_Data::GraphPair pair = genertor.GenerateGraphPair(8, true);

    /*GIS_Data::Graph graph1 = GIS_Parser::Graph::Parse(config.GetInput1());
    GIS_Data::Graph graph2 = GIS_Parser::Graph::Parse(config.GetInput2());*/

    auto start1 = std::chrono::high_resolution_clock::now();
    bool result1 = GIS_Algs::BruteForce::Start(pair.GetGraph1(), pair.GetGraph2());
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;

    std::cout << "Brute force end" << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    bool result2 = GIS_Algs::TruncEnum::Start(pair.GetGraph1(), pair.GetGraph2());
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;

    GIS_Stats::Statistics::Save(duration1.count(), result1, pair.GetGraph1().GetNodeCount(), config.GetOutput());
    GIS_Stats::Statistics::Save(duration2.count(), result2, pair.GetGraph1().GetNodeCount(), config.GetOutput());

    return 0;
}
