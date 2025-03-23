#include "pch.h"
#include "TruncEnum.h"

namespace GIS_Algs {

    bool TruncEnum::Start(const GIS_Data::Graph& graphF, const GIS_Data::Graph& graphS) {

        if (graphF.GetNodeCount() != graphS.GetNodeCount())
            return false;

        std::vector<bool> visitedF(graphF.GetNodeCount());
        std::vector<bool> visitedS(graphS.GetNodeCount());

        while (CheckVisitedNodes(visitedF, visitedS)) {

            int currF = FindStartNode(visitedF);
            int currS = FindStartNode(visitedS);

            for (int i = 0; i < graphF.GetNodeCount(); ++i) {
                if (visitedS[i])
                    continue;

                if (CompareGraphs(graphF, graphS, visitedF, visitedS, currF, i))
                    return true;

            }
        }

        

        return false;
    }

    int TruncEnum::FindStartNode(const std::vector<bool>& visitedNodes) {

        for (int i = 0; i < visitedNodes.size(); ++i)
            if (!visitedNodes[i])
                return i;
        return -1;
    }

    bool TruncEnum::CheckVisitedNodes(const std::vector<bool>& visitedF, const std::vector<bool>& visitedS)
    {
        for (int i = 0; i < visitedF.size(); ++i) {
            //if (!visitedF[i] || !visitedS[i])
        }
        return false;
    }

    bool TruncEnum::CompareGraphs(const GIS_Data::Graph& graphF, const GIS_Data::Graph& graphS, std::vector<bool>& visitedF, std::vector<bool>& visitedS, const int& nodeF, const int& nodeS) {

        std::queue<int> queueF;
        std::queue<int> queueS;

        queueF.push(nodeF);
        queueS.push(nodeS);

        visitedF[nodeF] = true;
        visitedS[nodeS] = true;

        while (queueF.size() > 0) {

            int currF = queueF.front();
            int currS = queueS.front();

            queueF.pop();
            queueS.pop();

            if (graphF.GetTag()[currF] != graphS.GetTag()[currS])
                return false;

            for (int i = 0; i < graphF.GetAdjList()[currF].size(); ++i) {
                queueF.push(graphF.GetAdjList()[currF][i]);
                queueS.push(graphS.GetAdjList()[currS][i]);
            }
        }

        return true;
    }
}
