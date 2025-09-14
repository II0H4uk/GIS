#include "pch.h"

#include <CheckMatching.h>

namespace GIS_Algs {

    std::vector<int> CheckMatching::GetAdjacentNets(int node, const GIS_Data::KoenigGraph& graph) {
    // Предполагаем, что adjList содержит цепи для вершин
    if (node < graph.GetAdjList().size()) {
        return graph.GetAdjList()[node];
    }
    return {};
    }

    /// @brief проверяет сопоставление
    /// @param mapping сопоставление элементов
    /// @param n количесвто проверенных вершн
    /// @param g1 граф 1
    /// @param g2 граф 2
    /// @return для каждой пары корректное ли сопоставление
    std::vector<bool> CheckMatching::ValidateMappings(const std::vector<std::pair<int, int>>& mapping, int reliableCount, const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2){
        
        std::vector<bool> reliableStatus(mapping.size(), false);
        //std::unordered_set<int> visited;
    
        // Сначала помечаем однозначные назначения как достоверные
        for (size_t i = 0; i < reliableCount; ++i) {
            reliableStatus[i] = true; // считаем достоверными
        }
        
        // Затем выполняем углубленную проверку для всех назначений
        for (size_t i = 0; i < mapping.size(); ++i) {
            const auto& pair = mapping[i];
            std::unordered_set<int> visited;
            
            reliableStatus[i] = IsMappingReliable(
                pair.first, pair.second, g1, g2, mapping, reliableStatus, visited
            );
        }
        
        return reliableStatus;
    }

    bool CheckMatching::IsMappingReliable(
    int node1, int node2,
    const GIS_Data::KoenigGraph& g1,
    const GIS_Data::KoenigGraph& g2,
    const std::vector<std::pair<int, int>>& mapping,
    std::vector<bool>& reliableStatus,
    std::unordered_set<int>& visited
    ) {
        // Проверяем, не посещали ли мы уже эту пару (для предотвращения циклов)
        int pairId = node1 * 1000000 + node2; // Уникальный ID для пары
        if (visited.find(pairId) != visited.end()) {
            return false; // Обнаружен цикл - недостаточно достоверных данных
        }
        visited.insert(pairId);

        // Получаем смежные цепи для обеих вершин
        auto nets1 = GetAdjacentNets(node1, g1);
        auto nets2 = GetAdjacentNets(node2, g2);

        // Если разное количество цепей - не достоверно
        //if (nets1.size() != nets2.size()) {
        //    return false;
        //}

        // Для каждой цепи вершины 1 ищем соответствующую цепь вершины 2
        for (int net1 : nets1) {
            bool netMatched = false;
            
            // Ищем вершины, подключенные к этой цепи в первом графе
            auto connectedNodes1 = g1.GetNetList()[net1];
            
            // Ищем соответствующие вершины во втором графе
            for (int net2 : nets2) {
                auto connectedNodes2 = g2.GetNetList()[net2];
                
                if (connectedNodes1.size() != connectedNodes2.size()) {
                    continue;
                }
                
                // Проверяем, что все соответствующие вершины сопоставлены правильно
                bool allNodesMatch = true;
                for (size_t i = 0; i < connectedNodes1.size(); ++i) {
                    int connectedNode1 = connectedNodes1[i];
                    
                    // Ищем сопоставление для этой вершины
                    bool foundMapping = false;
                    for (const auto& mapPair : mapping) {
                        if (mapPair.first == connectedNode1) {
                            int mappedNode2 = mapPair.second;
                            // Проверяем, есть ли эта вершина во второй цепи
                            if (std::find(connectedNodes2.begin(), connectedNodes2.end(), mappedNode2) == connectedNodes2.end()) {
                                allNodesMatch = false;
                                break;
                            }
                            foundMapping = true;
                            break;
                        }
                    }
                    
                    if (!foundMapping || !allNodesMatch) {
                        allNodesMatch = false;
                        break;
                    }
                }
                
                if (allNodesMatch) {
                    netMatched = true;
                    break;
                }
            }
            
            if (!netMatched) {
                return false;
            }
        }
        
        return true;
    }
}