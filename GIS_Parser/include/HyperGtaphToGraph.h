#pragma once

#ifdef _WIN32
    #ifdef GISPARSER_EXPORTS
        #define GISPARSER_API __declspec(dllexport)
    #else
        #define GISPARSER_API __declspec(dllimport)
    #endif
#else
    #define GISPARSER_API
#endif

#include "Graph.h"
#include <tuple>

namespace GIS_Parser {

    class GISPARSER_API HyperGraphToGraph {
    private:

    public:
        static std::tuple<GIS_Data::Graph, std::vector<int>> Convert(const std::string& filePath);
    };
}