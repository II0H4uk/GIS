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

#include <vector>
#include "Graph.h"

namespace GIS_Data {

    class GISDATA_API KoenigGraph {
    private:
        int nodeCount;
        int hyperEdgeCount;
        int tagsLevel;
        std::vector<std::vector<int>> adjList;
        std::vector<std::vector<TagType>> tag;
        void CalcTags();

    public:
        KoenigGraph(const std::vector<std::vector<int>>& hyperGraph, int tagsLevel);

        std::vector<std::vector<int>>& GetAdjList();
        std::vector<std::vector<TagType>> GetTags();
        int  GetNodeCount();
        int GetHyperEdgeCount();

        void NormalizeGraph(int diff, int offset, bool isNode);
    };
}
