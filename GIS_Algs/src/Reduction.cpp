#include "pch.h"
#include <Reduction.h>

namespace GIS_Algs {

    Reduction::Reduction(const GIS_Data::KoenigGraph& g) : g(g) {
        reduced_elements = std::vector<bool>(g.GetNodeCount(), false);

        findPowerNets(g.GetNetName(), "vdd", vdd_net);
        findPowerNets(g.GetNetName(), "gnd", gnd_net);
    }

    // Основной метод редукции
    GIS_Data::KoenigGraph Reduction::start() {

        std::queue<int> q(std::deque<int>(g.GetInputChains().begin(), g.GetInputChains().end()));
        
        while (!q.empty()) {

            int chain = q.front(); q.pop();

            std::unordered_set<int> nextChains;

            for (int elem : g.GetAdjList()[chain]) {
                if (g.GetElements()[elem].GetType() != 'M') {
                    nextChains.insert(g.GetAdjList()[elem][0]);
                    continue;
                }

                if (reduced_elements[elem])
                    continue;

                if (findInvertors(chain, elem, nextChains))
                    continue;
                if (findNand(chain, elem, nextChains))
                    continue;
                findNor(chain, elem, nextChains);
            }

            for (int net : nextChains)
                q.push(net);
        }
        
        return GenerateGraph();
    }

    // Поиск инверторов
    bool Reduction::findInvertors(int input_net, int first_t, std::unordered_set<int>& out_nets) {

        if (!powerCheck(first_t))
            return false;

        int first_t_drain = g.GetAdjList()[first_t][0];
        
        for (int second_t : g.GetAdjList()[input_net]) {
            if (g.GetElements()[second_t].GetChType() == g.GetElements()[first_t].GetChType() || !powerCheck(second_t))
                continue;

            int second_t_drain = g.GetAdjList()[second_t][0];

            if (first_t_drain == second_t_drain) {
                reduced_elements[first_t] = true;
                reduced_elements[second_t] = true;

                out_nets.insert(second_t_drain);

                foundElems.push_back(LogicElem("invertor", { input_net }, { second_t_drain }, { first_t, second_t }));
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

        int first_t_drain = g.GetAdjList()[first_t][0];

        for (int second_t : g.GetAdjList()[input_net]) {
            int second_t_drain = g.GetAdjList()[second_t][0];
            if (type(second_t) == 'p' || first_t_drain != second_t_drain)
                continue;

            int second_t_source = g.GetAdjListT()[second_t][1];
            int third_t = g.GetAdjListT()[second_t_source][0];
            if (!powerCheck(third_t) || type(third_t) == 'p')
                continue;

            int third_t_gate = g.GetAdjListT()[third_t][0];
            for (int fourth_t : g.GetAdjList()[third_t_gate]) {
                int fourth_t_drain = g.GetAdjList()[fourth_t][0];
                if (!powerCheck(fourth_t) || type(fourth_t) == 'n' || first_t_drain != fourth_t_drain)
                    continue;

                reduced_elements[first_t] = true;
                reduced_elements[second_t] = true;
                reduced_elements[third_t] = true;
                reduced_elements[fourth_t] = true;

                out_nets.insert(first_t_drain);

                foundElems.push_back(LogicElem("nand", { input_net, third_t_gate }, { first_t_drain }, { first_t, second_t, third_t, fourth_t }));
                return true;
            }
        }

        return false;
    }

    bool Reduction::findNandIn2(int input_net, int first_t, std::unordered_set<int>& out_nets) {

        if (type(first_t) == 'n' || !powerCheck(first_t))
            return false;

        int first_t_drain = g.GetAdjList()[first_t][0];

        for (int second_t : g.GetAdjList()[input_net]) {
            int second_t_drain = g.GetAdjList()[second_t][0];
            if (type(second_t) == 'p' ||
                !powerCheck(second_t) ||
                g.GetAdjList()[second_t_drain].size() != 1)
                continue;

            int third_t = g.GetAdjList()[second_t_drain][0];
            int third_t_drain = g.GetAdjList()[third_t][0];
            if (third_t_drain != first_t_drain || type(third_t) == 'p')
                continue;

            int third_t_gate = g.GetAdjListT()[third_t][0];
            for (int fourth_t : g.GetAdjList()[third_t_gate]) {
                int fourth_t_drain = g.GetAdjList()[fourth_t][0];
                if (!powerCheck(fourth_t) || type(fourth_t) == 'n' || first_t_drain != fourth_t_drain)
                    continue;

                reduced_elements[first_t] = true;
                reduced_elements[second_t] = true;
                reduced_elements[third_t] = true;
                reduced_elements[fourth_t] = true;

                out_nets.insert(first_t_drain);

                foundElems.push_back(LogicElem("nand", { input_net, third_t_gate }, { first_t_drain }, { first_t, second_t, third_t, fourth_t }));
                return true;
            }

        }

        return false;
    }

    bool Reduction::powerCheck(int transistor) {

        int source_net = g.GetAdjListT()[transistor][1];

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
                power_net.push_back(i + g.GetNodeCount());
        }
    }

    // Поиск NOR2
    bool Reduction::findNor(int input_net, int first_t, std::unordered_set<int>& out_nets) {
        return false;
    }

    char Reduction::type(int transistor) {
        return g.GetElements()[transistor].GetChType();
    }

    GIS_Data::KoenigGraph Reduction::GenerateGraph() {
        int node_count = foundElems.size();
        for (bool reduced_el : reduced_elements)
            if (!reduced_el) node_count++;

        std::unordered_map<int, int> net_map;
        int net_count = 0;

        for (int i = 0; i < foundElems.size(); ++i) {
            for (int net : foundElems[i].inputs)
                if (net_map.find(net) == net_map.end())
                    net_map[net] = node_count + net_count++;
            for (int net : foundElems[i].outputs)
                if (net_map.find(net) == net_map.end())
                    net_map[net] = node_count + net_count++;
        }

        for (int i = 0; i < reduced_elements.size(); ++i) {
            if (reduced_elements[i]) continue;

            for (int net : g.GetAdjList()[i])
                if (net_map.find(net) == net_map.end())
                    net_map[net] = node_count + net_count++;
            for (int net : g.GetAdjListT()[i])
                if (net_map.find(net) == net_map.end())
                    net_map[net] = node_count + net_count++;
        }

        std::vector<std::vector<int>> adj_list(node_count + net_count);
        std::vector<std::vector<int>> adj_listT(node_count + net_count);
        int el_count = 0;

        for (int i = 0; i < foundElems.size(); ++i) {
            int curr_el = el_count++;
            for (int net : foundElems[i].inputs) {
                adj_list[net_map[net]].push_back(curr_el);
                adj_listT[curr_el].push_back(net_map[net]);
            }
            for (int net : foundElems[i].outputs) {
                adj_list[curr_el].push_back(net_map[net]);
                adj_listT[net_map[net]].push_back(curr_el);
            }
        }

        for (int i = 0; i < reduced_elements.size(); ++i) {
            if (reduced_elements[i]) continue;
            int curr_el = el_count++;
            for (int net : g.GetAdjList()[i]) {
                adj_list[curr_el].push_back(net_map[net]);
                adj_listT[net_map[net]].push_back(curr_el);
            }
            for (int net : g.GetAdjListT()[i]) {
                adj_list[net_map[net]].push_back(curr_el);
                adj_listT[curr_el].push_back(net_map[net]);
            }
        }

        return GIS_Data::KoenigGraph();
    }

    Reduction::LogicElem::LogicElem(const std::string& name, const std::vector<int>& inputs, const std::vector<int>& outputs, const std::vector<int>& transistors) :
        name(name),
        inputs(inputs),
        outputs(outputs),
        transistors(transistors){}
}
