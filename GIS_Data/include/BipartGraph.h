#pragma once

#ifdef _WIN32
    #ifdef GISDATA_EXPORTS
        #define GISDATA_API __declspec(dllexport)
    #else
        #define GISDATA_API __declspec(dllimport)
    #endif
#else
    #define GISDATA_API
#endif

#include "Graph.h"

namespace GIS_Data {

    class GISDATA_API BipartGraph {
    private:
        std::vector<std::vector<int>> adjList;

    public:
        BipartGraph(std::vector<std::vector<TagType>> tags1, std::vector<std::vector<TagType>> tags2);
    };
}
