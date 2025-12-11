#pragma once

#include <vector>
#include "Subcircuit.h"
#include "LogicBlock.h"
#include <unordered_set>

namespace GIS_Data {

    class KoenigGraph {
    private:
        int node_count;
        int hyper_edge_count;

        std::vector<std::vector<int>> adj_list;
        std::vector<std::vector<int>> adj_list_t;

        std::vector<int> input_chains;
        std::vector<std::string> net_name;
        std::unordered_map<std::string, std::vector<int>> blocks_type;
        std::vector<LogicBlock> blocks;

        std::vector<int> findStart();
        std::vector<int> findEnd();
        void initBlocks(const Circuits::Utils::Subcircuit& circuit);
        void addEdge(int start, int end);
    public:
        KoenigGraph(const Circuits::Utils::Subcircuit& circuit);
        KoenigGraph(const std::vector<GIS_Data::LogicBlock>& blocks, std::vector<int> input_chains);

        const int getNodeCount() const { return node_count; }
        const int getHyperEdgeCount() const { return hyper_edge_count; }

        const std::vector<std::vector<int>>& getAdjList() const { return adj_list; }
        const std::vector<std::vector<int>>& getAdjListT() const { return adj_list_t; }

        const std::vector<int>& getInputChains() const { return input_chains; }
        const std::vector<std::string>& getNetName() const { return net_name; }
        const std::unordered_map<std::string, std::vector<int>>& getBlocksType() const { return blocks_type; }
        const std::vector<LogicBlock>& getBlocks() const { return blocks; }
    };
}
