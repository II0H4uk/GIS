#include "pch.h"
#include "Statistics.h"
#include "FileWriter.h"

namespace GIS_Stats {

    void Statistics::Save(const double& time, const bool& result, const int& nodeCount, const string& filePath)
    {
        string statisticsInfo = string("Graph Isomorphism Comparison Statistics") + "\n\n" + 
                                "Number of nodes: " + to_string(nodeCount) + "\n" +
                                "Isomorphism Result: " + (result ? "True" : "False") + "\n" +
                                "Work time: " + to_string(time) + "\n\n";

        cout << statisticsInfo;

        GIS_Parser::FileWriter::WriteStringToFile(statisticsInfo, filePath);
    }
}
