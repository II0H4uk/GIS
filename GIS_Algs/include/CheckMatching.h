#pragma once

#include <KoenigGraph.h>

namespace GIS_Algs {
    class CheckMatching {
    private:
        /// @brief Рекурсивная проверка достоверности назначения
        /// @param node1 
        /// @param node2 
        /// @param g1 
        /// @param g2 
        /// @param mapping 
        /// @param reliableStatus 
        /// @param visited 
        /// @return 
        static bool IsMappingReliable(
            int node1, int node2,
            const GIS_Data::KoenigGraph& g1,
            const GIS_Data::KoenigGraph& g2,
            const std::vector<std::pair<int, int>>& mapping,
            std::vector<bool>& reliableStatus,
            std::unordered_set<int>& visited
        );
    
        /// @brief Получает смежные цепи для вершины
        /// @param node 
        /// @param graph 
        /// @return 
        static std::vector<int> GetAdjacentNets(int node, const GIS_Data::KoenigGraph& graph);
    public:
        /// @brief 
        /// @param mapping 
        /// @param reliableCount 
        /// @param g1 
        /// @param g2 
        /// @return 
        static std::vector<bool> ValidateMappings(
            const std::vector<std::pair<int, int>>& mapping, 
            int reliableCount, 
            const GIS_Data::KoenigGraph& g1, 
            const GIS_Data::KoenigGraph& g2
        );
    };
}