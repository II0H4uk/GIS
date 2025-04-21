#include "pch.h"
#include "SubGraphIso.h"

namespace GIS_Algs {
    const std::vector<int> GIS_Algs::SubGraphIso::Start(const GIS_Data::Graph& graph1, const GIS_Data::Graph& graph2, int fixNodeCount) {
        
        std::vector<int> bijection = InitBijection(fixNodeCount, graph1.GetNodeCount());



        return bijection;
    }

    const std::vector<int> SubGraphIso::InitBijection(int fixNodeCount, int nodeCount) {

        std::vector<int> bijection(nodeCount);
        for (int i = 0; i < fixNodeCount; ++i) {
            bijection[i] = i;
        }
        return bijection;
    }

    void SubGraphIso::MatchNodes(std::vector<int>& bijection, const std::vector<int>& subGraph1, const std::vector<int>& subGraph2, const GIS_Data::Graph& graph1, const GIS_Data::Graph& graph2) {

    }
}
