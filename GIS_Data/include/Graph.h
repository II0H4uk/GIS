#pragma once

#include <variant>
#include <vector>
#include <string>

namespace GIS_Data {

    using TagType = std::variant <int,
        double,
        std::vector<int>,
        std::vector<double>,
        std::string >;

    bool CompareTags(const TagType& first, const TagType& second);

    class Graph {
    private:
        int nodeCount;
        int neighDegLv;
        std::vector<std::vector<int>> adjList;
        std::vector<std::vector<TagType>> tag;

        std::vector<std::vector<TagType>> CalcNodesDeg(const std::vector<std::vector<int>>& adjList, int maxDepth);
        void AddToTagInt(TagType& tag, int value);
    public:
        Graph(const std::vector<std::vector<int>>& adjList, int nodeCount, int neighDegLv = 0);

        const std::vector<std::vector<int>>& GetAdjList() const;
        const std::vector<std::vector<TagType>>& GetTag() const;
        int GetNodeCount() const;
        int GetNeighDegLv() const;
    };
}
