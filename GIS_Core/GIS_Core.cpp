#include "pch.h"
#include "ConfigParser.h"
#include "GraphParser.h"
#include "BruteForce.h"

int main(int argc, char* argv[]) {

    GIS_Data::Config config = GIS_Parser::Config::Parse("../config.ini");

    GIS_Data::Graph graph = GIS_Parser::Graph::Parse(config.GetInput());

    std::cout << GIS_Algs::BruteForce::Start(graph);
    return 0;
}
