#include "pch.h"
#include "Statistics.h"
#include "FileWriter.h"

namespace GIS_Stats {

    void Statistics::Save(const double& time, const bool& result, const int& nodeCount, const std::string& filePath)
    {
        std::string statisticsInfo = std::string("Graph Isomorphism Comparison Statistics") + "\n\n" + 
                                "Number of nodes: " + std::to_string(nodeCount) + "\n" +
                                "Isomorphism Result: " + (result ? "True" : "False") + "\n" +
                                "Work time: " + std::to_string(time) + "\n\n";

        std::cout << statisticsInfo;

        GIS_Parser::FileWriter::WriteStringToFile(statisticsInfo, filePath);
    }
}
