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
    GIS_Data::GraphPair pair = genertor.GenerateGraphPair(10, true);

    /*GIS_Data::Graph graph1 = GIS_Parser::Graph::Parse(config.GetInput1());
    GIS_Data::Graph graph2 = GIS_Parser::Graph::Parse(config.GetInput2());*/

    auto start = std::chrono::high_resolution_clock::now();
    //bool result = GIS_Algs::TruncEnum::Start(pair.GetGraph1(), pair.GetGraph2());
    bool result = GIS_Algs::BruteForce::Start(pair.GetGraph1(), pair.GetGraph2());
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = end - start;

    GIS_Stats::Statistics::Save(duration.count(), result, pair.GetGraph1().GetNodeCount(), config.GetOutput());
    std::cout << duration;

    
    

    return 0;
}
