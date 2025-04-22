#include "pch.h"
#include "SubGraphIso.h"

namespace GIS_Algs {
    const std::vector<int> GIS_Algs::SubGraphIso::Start(const GIS_Data::Graph& graph1, const GIS_Data::Graph& graph2, int fixNodeCount) {
        
        std::vector<int> bijection = InitBijection(fixNodeCount, graph1.GetNodeCount());



        return bijection;
    }

    const std::vector<int> SubGraphIso::InitBijection(int fixNodeCount, int nodeCount) {

        std::vector<int> bijection(nodeCount, -1);
        for (int i = 0; i < fixNodeCount; ++i) {
            bijection[i] = i;
        }
        return bijection;
    }

    void SubGraphIso::MatchNodes(std::vector<int>& bijection, const std::vector<int>& subGraph1, const std::vector<int>& subGraph2, const GIS_Data::Graph& graph1, const GIS_Data::Graph& graph2) {
        
        int startPoint = FindStartPoint(bijection, subGraph1, subGraph2, graph1, graph2);

        std::queue<int> queue;
        queue.push(startPoint);

        std::vector<bool> visited(graph1.GetAdjList().size());
        visited[startPoint] = true;

        while (queue.size() > 0) {
            int currNode = queue.front();
            queue.pop();

            std::vector<int> currNeigh1 = graph1.GetAdjList()[currNode];
            std::vector<int> currNeigh2 = graph2.GetAdjList()[bijection[currNode]];

            for (int i = 0; i < currNeigh1.size(); ++i) {
                if (visited[currNeigh1[i]])
                    continue;
                if (std::find(subGraph1.begin(), subGraph1.end(), currNeigh1[i]) != subGraph1.end()) {
                    queue.push(currNeigh1[i]);
                    visited[currNeigh1[i]] = true;
                }

                if (bijection[currNeigh1[i]] > -1)
                    continue;

                for (int j = 0; j < currNeigh2.size(); ++j) {
                    if (graph1.GetTag()[currNeigh1[i]] == graph2.GetTag()[currNeigh2[j]] && std::find(bijection.begin(), bijection.end(), currNeigh2[j]) == bijection.end()) {
                        bijection[currNeigh1[i]] = currNeigh2[j];
                        break;
                    }
                }
            }
        }
    }

    int SubGraphIso::FindStartPoint(const std::vector<int>& bijection, const std::vector<int>& subGraph1, const std::vector<int>& subGraph2, const GIS_Data::Graph& graph1, const GIS_Data::Graph& graph2) {
        
        for (int i = 0; i < subGraph1.size(); ++i) {
            if (bijection[subGraph1[i]] > -1 && std::find(subGraph2.begin(), subGraph2.end(), bijection[subGraph1[i]]) != subGraph2.end())
                return subGraph1[i];
        }

        return -1;
    }
}
