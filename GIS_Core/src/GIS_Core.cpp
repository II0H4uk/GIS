#include "pch.h"
#include "ConfigParser.h"
#include "GraphParser.h"
#include "BruteForce.h"
#include "Statistics.h"
#include "Generator.h"

int main(int argc, char* argv[]) {

    GIS_Data::Config config = GIS_Parser::Config::Parse("../config.ini");

    GIS_Data::Graph graph = GIS_Parser::Graph::Parse(config.GetInput());

    auto start = std::chrono::high_resolution_clock::now();
    bool result = GIS_Algs::BruteForce::Start(graph);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    GIS_Stats::Statistics::Save(duration.count(), result, graph.GetNodeCount());

    //std::cout << duration;

    //Проверка изморфизма графов
    //std::cout << "Check generator: ";

    GIS_Data::GraphPair pair = GIS_Generator::Generator::Generate(true);
    //p.first = 1;
    //p.second = 3.14;

    //bool isIsomorphic = true; // Измените на false для генерации не изоморфных графов
    //pair<GIS_Data::Graph, GIS_Data::Graph> graphs = GIS_Generator::Generator::Generate(isIsomorphic);
    //std::pair <GIS_Data::Graph, GIS_Data::Graph> graphs = GIS_Generator::Generator::Generate(isIsomorphic);

    return 0;
}
