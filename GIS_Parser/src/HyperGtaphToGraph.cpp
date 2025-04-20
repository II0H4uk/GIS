#include "pch.h"
#include "HyperGtaphToGraph.h"
#include "GraphParser.h"

std::tuple<GIS_Data::Graph, int> GIS_Parser::HyperGraphToGraph::Convert(const std::string& filePath)
{
    std::vector<std::vector<int>> netList = GIS_Parser::Graph::ReadData(filePath);

    std::vector<std::vector<int>> adjList(netList[0][1]);

    for (int i = 1; i < netList.size(); ++i)
    {
        for (int j = 0; j < netList[i].size(); ++j) {
            int currNet = netList[i][j];
            for (int k = 1; k < netList.size(); ++k) {
                if (k == i)
                    continue;
                if (std::find(netList[k].begin(), netList[k].end(), currNet) != netList[k].end() && std::find(adjList[i - 1].begin(), adjList[i - 1].end(), k - 1) == adjList[i - 1].end()) {
                    adjList[i - 1].push_back(k - 1);
                }
            }
        }
    }

    for (int i = 0; i < adjList.size(); ++i)
        std::sort(adjList[i].begin(), adjList[i].end());

    return {GIS_Data::Graph(adjList, adjList.size()) , netList[0][0]};
}
