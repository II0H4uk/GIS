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
#include <string>

namespace GIS_Parser {

    class GISPARSER_API Graph {
    private:

    public:
        static GIS_Data::Graph Parse(const std::string& filePath);
    };
}
