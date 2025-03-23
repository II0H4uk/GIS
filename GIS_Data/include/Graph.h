#pragma once

#ifdef GISDATA_EXPORTS
    #define GISDATA_API __declspec(dllexport)
#else
    #define GISDATA_API __declspec(dllimport)
#endif // GISDATA_EXPORTS

#include "pch.h"

namespace GIS_Data {

    using TagType = std::variant <int,
        double,
        std::vector<int>,
        std::vector<double>,
        std::string >;

    bool CompareTags(const TagType& first, const TagType& second);

    class GISDATA_API Graph {
    private:
        int nodeCount;
        std::vector<std::vector<int>> adjList;
        std::vector<std::vector<TagType>> tag;
        
    public:
        Graph(const std::vector<std::vector<int>>& adjList, int nodeCount);

        const std::vector<std::vector<int>>& GetAdjList() const;
        const std::vector<std::vector<TagType>>& GetTag() const;
        int GetNodeCount() const;
    };
}
