#pragma once

#ifdef GISPARSER_EXPORTS
#define GISGISPARSER_API __declspec(dllexport)
#else
#define GISGISPARSER_API __declspec(dllimport)
#endif // GISPARSER_EXPORTS

#include "pch.h"
#include "Graph.h"

namespace GIS_Parser {

    class GISGISPARSER_API Graph {
    private:

    public:
        static GIS_Data::Graph Parse(const std::string& filePath);
    };
}
