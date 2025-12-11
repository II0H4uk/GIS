#include "pch.h"
#include "Utils.h"

#include <KoenigGraph.h>
#include <Subcircuit.h>

namespace GIS_Utils {
    std::string Utils::GetCircuitAdjList(const GIS_Data::KoenigGraph& koenG, const Circuits::Utils::Subcircuit& circuit) {

        std::string adjList = "";

        for (int i = 0; i < koenG.getAdjList().size(); ++i) {
            if (i < circuit.components.size())
                adjList += circuit.components[i].id + ": ";
            else
                adjList += "N" + std::to_string(i - circuit.components.size()) + ": ";

            for (int j = 0; j < koenG.getAdjList()[i].size(); ++j) {
                if (koenG.getAdjList()[i][j] < circuit.components.size())
                    adjList += circuit.components[koenG.getAdjList()[i][j]].id + ", ";
                else
                    adjList += "N" + std::to_string(koenG.getAdjList()[i][j] - circuit.components.size()) + ", ";
            }
            adjList += "\n";
        }

        return adjList;
    }

    std::string Utils::GetAdjList(const GIS_Data::KoenigGraph& koenG) {

        std::string adjList;

        for (int i = 0; i < koenG.getAdjList().size(); ++i) {
            adjList += std::to_string(i) + ": ";
            for (int j = 0; j < koenG.getAdjList()[i].size(); ++j) {
                adjList += std::to_string(koenG.getAdjList()[i][j]) + ", ";
            }
            adjList += "\n";
        }

        return adjList;
    }

    int Utils::CountLevels(const std::vector<std::vector<int>>& adjList, const std::vector<int>& startVertices) {
        int n = (int)adjList.size();
        std::vector<char> visited(n, 0);
        std::queue<int> q;

        for (int s : startVertices) {
            if (!visited[s]) {
                visited[s] = 1;
                q.push(s);
            }
        }

        int levels = 0;
        while (!q.empty()) {
            int sz = (int)q.size();
            for (int i = 0; i < sz; ++i) {
                int u = q.front(); q.pop();
                for (int v : adjList[u]) {
                    if (!visited[v]) {
                        visited[v] = 1;
                        q.push(v);
                    }
                }
            }
            ++levels;
        }

        return levels;
    }

    std::string Utils::ConvertGraphMapToCircuit(const std::vector<std::pair<std::vector<int>, std::vector<int>>>& map,
        const GIS_Data::KoenigGraph& koenG1, const GIS_Data::KoenigGraph& koenG2) {

        /*std::string circuitMap = "";

        for (int i = 0; i < map.size(); ++i) {
            if (map[i].first >= kGraph1.GetNodeCount())
                break;
            circuitMap += map[i].first + " -> " + map[i].second << "\n";
        }*/
        return std::string();
    }
}
