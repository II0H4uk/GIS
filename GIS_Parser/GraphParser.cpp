#include "pch.h"
#include "GraphParser.h"

namespace GIS_Parser {

    GIS_Data::Graph Graph::Parse(const std::string& filePath) {
        std::vector<std::vector<int>> adjList;
        std::ifstream file(filePath);

        if (!file.is_open()) {
            throw std::runtime_error("Bad config file: " + filePath);
        }

        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> adjNodes;
            std::stringstream nodes(line);
            std::string node;

            while (std::getline(nodes, node, ',')) {
                node.erase(0, node.find_first_not_of(" \t"));
                node.erase(node.find_last_not_of(" \t") + 1);

                if (!node.empty())
                    adjNodes.push_back(std::stoi(node));
            }

            adjList.push_back(adjNodes);
        }

        file.close();

        return GIS_Data::Graph(adjList, adjList.size());
    }
}
