#include "pch.h"
#include "BipartGraph.h"

namespace GIS_Data {

    BipartGraph::BipartGraph() {
        adjList = std::vector<std::vector<int>>();
    }

    BipartGraph::BipartGraph(const GIS_Data::KoenigGraph& kGraph1, const GIS_Data::KoenigGraph& kGraph2) {

        std::vector<Element> elems1 = kGraph1.GetElements();
        std::vector<Element> elems2 = kGraph2.GetElements();
        adjList = std::vector<std::vector<int>>(elems1.size() + elems2.size());

        for (size_t i = 0; i < elems1.size(); ++i) {
            for (size_t j = 0; j < elems2.size(); ++j) {
                if (AreSimilar(elems1[i], elems2[j])) {

                    adjList[i].push_back(elems1.size() + j);
                    adjList[elems1.size() + j].push_back(i);
                }
            }
        }
    }

    BipartGraph::BipartGraph(const std::vector<std::vector<int>>& adjacencyList) : adjList(adjacencyList) { }

    void BipartGraph::ChangeEdge(int i, int j, int edgeStatus) {
        adjList[i][j] = edgeStatus;
        adjList[j][i] = edgeStatus;
    }

    void BipartGraph::EraseElem(int i, int j) {
        int secondNode = adjList[i][j];
        adjList[i].erase(adjList[i].begin() + j);

        auto it = std::find(adjList[secondNode].begin(), adjList[secondNode].end(), i);
        if (it != adjList[secondNode].end()) {
            adjList[secondNode].erase(it);
        }
    }

    bool BipartGraph::AreSimilar(const Element& a, const Element& b) {

        if (std::tolower(a.GetType()) != std::tolower(b.GetType()))
            return false;

        if (a.GetPinCount() != b.GetPinCount())
            return false;

        if (a.GetSize().size() != b.GetSize().size())
            return false;

        for (size_t i = 0; i < a.GetSize().size(); ++i)
            if (std::abs(a.GetSize()[i] - b.GetSize()[i]) > 0)
                return false;

        if (a.GetNeighDeg().size() != b.GetNeighDeg().size())
            return false;

        for (size_t i = 0; i < a.GetNeighDeg().size(); ++i)
            if (std::abs(a.GetNeighDeg()[i] - b.GetNeighDeg()[i]) > 1)
                return false;

        if (std::abs(a.GetForwLv() - b.GetForwLv()) > 1)
            return false;

        if (std::abs(a.GetBackwLv() - b.GetBackwLv()) > 1)
            return false;

        return true;
    }
}
