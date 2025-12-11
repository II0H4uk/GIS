#include "pch.h"
#include <Reduction.h>

namespace GIS_Algs {

    Reduction::Reduction(const GIS_Data::KoenigGraph& g) : g(g) {
        reduced_elements = std::vector<bool>(g.getNodeCount(), false);

        findPowerNets(g.getNetName(), "vdd", vdd_net);
        findPowerNets(g.getNetName(), "gnd", gnd_net);
    }

    // Основной метод редукции
    GIS_Data::KoenigGraph Reduction::start() {

        std::queue<int> q(std::deque<int>(g.getInputChains().begin(), g.getInputChains().end()));
        
        while (!q.empty()) {

            int chain = q.front(); q.pop();

            std::unordered_set<int> next_nets;

            for (int elem : g.getAdjList()[chain]) {
                if (g.getBlocks()[elem].getType() != "M") {
                    next_nets.insert(g.getAdjList()[elem][0]);
                    continue;
                }

                if (reduced_elements[elem])
                    continue;

                if (findInvertors(chain, elem, next_nets))
                    continue;
                if (findNand(chain, elem, next_nets))
                    continue;
                findNor(chain, elem, next_nets);
            }

            for (int net : next_nets)
                q.push(net);
        }

        for (int i = 0; i < reduced_elements.size(); ++i)
            if (!reduced_elements[i])
                found_blocks.push_back(GIS_Data::LogicBlock(
                    g.getBlocks()[i].getType(),
                    "",
                    g.getAdjListT()[i],
                    g.getAdjList()[i],
                    g.getBlocks()[i].getInnerBlocks(),
                    g.getBlocks()[i].getFunc()));
        
        return GIS_Data::KoenigGraph(found_blocks, g.getInputChains());
    }

    // Поиск инверторов
    bool Reduction::findInvertors(int input_net, int first_t, std::unordered_set<int>& out_nets) {

        if (!powerCheck(first_t))
            return false;

        int first_t_drain = g.getAdjList()[first_t][0];
        
        for (int second_t : g.getAdjList()[input_net]) {
            if (g.getBlocks()[second_t].getTransistorType() == g.getBlocks()[first_t].getTransistorType() || !powerCheck(second_t))
                continue;

            int second_t_drain = g.getAdjList()[second_t][0];

            if (first_t_drain == second_t_drain) {
                reduced_elements[first_t] = true;
                reduced_elements[second_t] = true;

                out_nets.insert(second_t_drain);

                found_blocks.push_back(GIS_Data::LogicBlock("invertor", "", { input_net }, {second_t_drain}, {first_t, second_t},
                    [](const std::vector<int>& inputs) -> std::vector<int> {
                        return { (inputs[0] == 0) ? 1 : 0 };
                    }));
                return true;
            }
        }

        return false;
    }

    // Поиск NAND2
    bool Reduction::findNand(int input_net, int first_t, std::unordered_set<int>& out_nets) {

        if (findNandIn1(input_net, first_t, out_nets))
            return true;

        if (findNandIn2(input_net, first_t, out_nets))
            return true;
        return false;
    }

    bool Reduction::findNandIn1(int input_net, int first_t, std::unordered_set<int>& out_nets) {

        if (type(first_t) == 'n' || !powerCheck(first_t))
            return false;

        int first_t_drain = g.getAdjList()[first_t][0];

        for (int second_t : g.getAdjList()[input_net]) {
            int second_t_drain = g.getAdjList()[second_t][0];
            if (type(second_t) == 'p' || first_t_drain != second_t_drain)
                continue;

            int second_t_source = g.getAdjListT()[second_t][1];
            int third_t = g.getAdjListT()[second_t_source][0];
            if (!powerCheck(third_t) || type(third_t) == 'p')
                continue;

            int third_t_gate = g.getAdjListT()[third_t][0];
            for (int fourth_t : g.getAdjList()[third_t_gate]) {
                int fourth_t_drain = g.getAdjList()[fourth_t][0];
                if (!powerCheck(fourth_t) || type(fourth_t) == 'n' || first_t_drain != fourth_t_drain)
                    continue;

                reduced_elements[first_t] = true;
                reduced_elements[second_t] = true;
                reduced_elements[third_t] = true;
                reduced_elements[fourth_t] = true;

                out_nets.insert(first_t_drain);

                found_blocks.push_back(GIS_Data::LogicBlock("nand", "", { input_net, third_t_gate }, {first_t_drain}, {first_t, second_t, third_t, fourth_t},
                    [](const std::vector<int>& inputs) -> std::vector<int> {
                        return { (inputs[0] == 1 && inputs[1] == 1) ? 0 : 1 };
                    }));
                return true;
            }
        }

        return false;
    }

    bool Reduction::findNandIn2(int input_net, int first_t, std::unordered_set<int>& out_nets) {

        if (type(first_t) == 'n' || !powerCheck(first_t))
            return false;

        int first_t_drain = g.getAdjList()[first_t][0];

        for (int second_t : g.getAdjList()[input_net]) {
            int second_t_drain = g.getAdjList()[second_t][0];
            if (type(second_t) == 'p' ||
                !powerCheck(second_t) ||
                g.getAdjList()[second_t_drain].size() != 1)
                continue;

            int third_t = g.getAdjList()[second_t_drain][0];
            int third_t_drain = g.getAdjList()[third_t][0];
            if (third_t_drain != first_t_drain || type(third_t) == 'p')
                continue;

            int third_t_gate = g.getAdjListT()[third_t][0];
            for (int fourth_t : g.getAdjList()[third_t_gate]) {
                int fourth_t_drain = g.getAdjList()[fourth_t][0];
                if (!powerCheck(fourth_t) || type(fourth_t) == 'n' || first_t_drain != fourth_t_drain)
                    continue;

                reduced_elements[first_t] = true;
                reduced_elements[second_t] = true;
                reduced_elements[third_t] = true;
                reduced_elements[fourth_t] = true;

                out_nets.insert(first_t_drain);

                found_blocks.push_back(GIS_Data::LogicBlock("nand", "", { input_net, third_t_gate }, {first_t_drain}, {first_t, second_t, third_t, fourth_t},
                    [](const std::vector<int>& inputs) -> std::vector<int> {
                        return { (inputs[0] == 1 && inputs[1] == 1) ? 0 : 1 };
                    }));
                return true;
            }

        }

        return false;
    }

    bool Reduction::powerCheck(int transistor) {

        int source_net = g.getAdjListT()[transistor][1];

        if (type(transistor) == 'n')
            return std::find(gnd_net.begin(), gnd_net.end(), source_net) != gnd_net.end();

        if (type(transistor) == 'p')
            return std::find(vdd_net.begin(), vdd_net.end(), source_net) != vdd_net.end();
    }

    void Reduction::findPowerNets(const std::vector<std::string>& nets_name, const std::string& name, std::vector<int>& power_net) {
        
        for (int i = 0; i < nets_name.size(); ++i) {

            std::string net_lower = nets_name[i];
            std::transform(net_lower.begin(), net_lower.end(), net_lower.begin(),
                [](unsigned char c) { return std::tolower(c); });

            if (net_lower.find(name) != std::string::npos)
                power_net.push_back(i + g.getNodeCount());
        }
    }

    // Поиск NOR2
    bool Reduction::findNor(int input_net, int first_t, std::unordered_set<int>& out_nets) {
        return false;
    }

    char Reduction::type(int transistor) {
        return g.getBlocks()[transistor].getTransistorType();
    }
}
