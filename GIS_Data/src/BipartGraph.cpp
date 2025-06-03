#include "pch.h"
#include "BipartGraph.h"

namespace GIS_Data {
    BipartGraph::BipartGraph(std::vector<std::vector<TagType>> tags1, std::vector<std::vector<TagType>> tags2) {

    }

    BipartGraph::BipartGraph(const std::vector<std::vector<int>>& adjacencyList)
        : adjList(adjacencyList) {
    }
}
