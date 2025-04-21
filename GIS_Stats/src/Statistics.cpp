#include "pch.h"
#include "Statistics.h"
#include "FileWriter.h"

namespace GIS_Stats {

    void Statistics::Save(const double& time, const std::vector<int>& result, const int& nodeCount, const std::string& filePath) {

        std::string bijection;

        for (int i = 0; i < result.size(); ++i) {
            if (result[i] == 0 && i != 0)
                continue;
            bijection += std::format("{}, {}", i, result[i]);
        }

        std::string statisticsInfo = std::string("Graph Isomorphism Comparison Statistics") + "\n\n" + 
                                "Number of nodes: " + std::to_string(nodeCount) + "\n" +
                                "Work time: " + std::to_string(time) + "\n" +
                                "Isomorphism Result: " + bijection + "\n";

        std::cout << statisticsInfo;

        GIS_Parser::FileWriter::WriteStringToFile(statisticsInfo, filePath);
    }
}
