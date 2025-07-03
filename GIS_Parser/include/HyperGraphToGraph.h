#pragma once

#include "Graph.h"
#include <tuple>

namespace GIS_Parser {

    class HyperGraphToKoenig {
    private:

    public:
        static std::tuple<GIS_Data::Graph, std::vector<int>> Convert(const std::string& filePath);
    };
}