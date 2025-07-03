#pragma once

#include "Graph.h"
#include <string>

namespace GIS_Parser {

    class Graph {
    private:

    public:
        static GIS_Data::Graph Parse(const std::string& filePath);
        static std::vector<std::vector<int>> ReadData(const std::string& filePath);
    };
}
