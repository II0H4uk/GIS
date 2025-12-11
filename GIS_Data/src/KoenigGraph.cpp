#include "pch.h"
#include "KoenigGraph.h"
#include <Subcircuit.h>

namespace GIS_Data {
    KoenigGraph::KoenigGraph(const Circuits::Utils::Subcircuit& circuit) :
        node_count(circuit.components.size()),
        hyper_edge_count(circuit.netsCount),
        adj_list(node_count + hyper_edge_count),
        adj_list_t(node_count + hyper_edge_count),
        net_name(hyper_edge_count) {

        for (int i = 0; i < circuit.components.size(); ++i) {
            blocks_type[std::string{ circuit.components[i].id[0] }].push_back(i);
        }

        for (auto net : circuit.netsToInt) {
            for (int i = 0; i < net.second.size(); ++i) {
                net_name[net.second[i]] = net.first;
            }
        }

        for (int i = 0; i < node_count; ++i) {
            for (int j = 0; j < circuit.components[i].chainInt.size(); ++j) {
                int currNet = circuit.components[i].chainInt[j] + node_count;
                if (circuit.components[i].id[0] == 'M' || circuit.components[i].id[0] == 'C') {
                    if (j == 0)
                        addEdge(i, currNet);
                    else
                        addEdge(currNet, i);
                    continue;
                }
                if (j == 0)
                    addEdge(i, currNet);
                else
                    addEdge(currNet, i);
            }
        }

        for (int i = 0; i < hyper_edge_count; ++i) {
            blocks_type["Net"].push_back(node_count + i);
        }

        for (int i = 0; i < adj_list_t.size(); ++i)
            if (adj_list_t[i].size() == 0)
                input_chains.push_back(i);

        initBlocks(circuit);
    }

    KoenigGraph::KoenigGraph(const std::vector<GIS_Data::LogicBlock>& blocks,
        std::vector<int> input_chains) :
        node_count(blocks.size()),
        hyper_edge_count(0),
        input_chains(input_chains),
        net_name(net_name),
        blocks(blocks) {

        std::unordered_map<int, int> net_map;

        for (int i = 0; i < blocks.size(); ++i) {
            for (int net : blocks[i].getInputs())
                if (net_map.find(net) == net_map.end())
                    net_map[net] = node_count + hyper_edge_count++;
            for (int net : blocks[i].getOutputs())
                if (net_map.find(net) == net_map.end())
                    net_map[net] = node_count + hyper_edge_count++;
        }

        adj_list = std::vector<std::vector<int>>(node_count + hyper_edge_count);
        adj_list_t = std::vector<std::vector<int>>(node_count + hyper_edge_count);

        for (int i = 0; i < blocks.size(); ++i) {
            for (int net : blocks[i].getInputs()) {
                adj_list[net_map[net]].push_back(i);
                adj_list_t[i].push_back(net_map[net]);
            }
            for (int net : blocks[i].getOutputs()) {
                adj_list[i].push_back(net_map[net]);
                adj_list_t[net_map[net]].push_back(i);
            }
        }

        for (int i = 0; i < blocks.size(); ++i)
            blocks_type[blocks[i].getType()].push_back(i);
    }

    void KoenigGraph::addEdge(int start, int end) {
        adj_list[start].push_back(end);
        adj_list_t[end].push_back(start);
    }

    void KoenigGraph::initBlocks(const Circuits::Utils::Subcircuit& circuit) {

        for (int i = 0; i < node_count; ++i) {
            std::string type = circuit.components[i].id;
            std::string tr_t = circuit.components[i].channelType;
            
            if (type[0] == 'M') {
                std::string mos_type = std::string{ type[0] };
                if (tr_t[0] == 'n')
                    blocks.push_back(LogicBlock(mos_type, tr_t, adj_list_t[i], adj_list[i], { i },
                        [](const std::vector<int>& inputs) -> std::vector<int> {
                            if (inputs[0] == 1) return { inputs[1] };
                            return { -1 };
                        }));
                if (tr_t[0] == 'p')
                    blocks.push_back(LogicBlock(mos_type, tr_t, adj_list_t[i], adj_list[i], { i },
                        [](const std::vector<int>& inputs) -> std::vector<int> {
                            if (inputs[0] == 0) return { inputs[1] };
                            return { -1 };
                        }));
                continue;
            }
            if (type[0] == 'C') {
                std::string cap_type = std::string{ type[0] };
                blocks.push_back(LogicBlock(cap_type, tr_t, adj_list_t[i], adj_list[i], { i },
                    [](const std::vector<int>& inputs) -> std::vector<int> {
                        if (inputs[0] == 1) return { inputs[1] };
                        return { -1 };
                    }));
                continue;
            }
            if (type[0] == 'D') {
                std::string dio_type = std::string{ type[0] };
                blocks.push_back(LogicBlock(dio_type, tr_t, adj_list_t[i], adj_list[i], { i },
                    [](const std::vector<int>& inputs) -> std::vector<int> {
                        return { inputs[0] };
                    }));
                continue;
            }
            blocks.push_back(LogicBlock(type, tr_t, adj_list_t[i], adj_list[i], { i },
                [](const std::vector<int>& inputs) -> std::vector<int> {
                    return { inputs[0] };
                }));
        }
    }

    std::vector<int> KoenigGraph::findStart() {
        std::vector<int> startNodes;

        std::vector<bool> isUsed(hyper_edge_count);
        for (int i = 0; i < node_count; ++i) {
            for (int j = 0; j < adj_list[i].size(); ++j) {
                isUsed[adj_list[i][j] - node_count] = true;
            }
        }

        for (int i = 0; i < isUsed.size(); ++i) {
            if (!isUsed[i])
                startNodes.push_back(node_count + i);
        }

        return startNodes;
    }

    std::vector<int> KoenigGraph::findEnd() {
        std::vector<int> endNodes;

        for (int i = 0; i < hyper_edge_count; ++i) {
            int netNode = node_count + i;

            if (adj_list[netNode].size() == 0)
                endNodes.push_back(netNode);
        }

        return endNodes;
    }
}
