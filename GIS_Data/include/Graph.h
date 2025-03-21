#pragma once

#ifdef GISDATA_EXPORTS
    #define GISDATA_API __declspec(dllexport)
#else
    #define GISDATA_API __declspec(dllimport)
#endif // GISDATA_EXPORTS

#include "pch.h"

namespace GIS_Data {

    class GISDATA_API Graph {
    private:
        int nodeCount;
        std::vector<std::vector<int>> adjList;
        std::vector<std::variant<int, std::string>> tag;

    public:
        Graph(const std::vector<std::vector<int>>& adjList, int nodeCount);

        std::vector<std::vector<int>> GetAdjList() const;
        int GetNodeCount() const;
    };
}
