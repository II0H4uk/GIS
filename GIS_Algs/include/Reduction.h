#pragma once

#include <vector>
#include <KoenigGraph.h>

namespace GIS_Algs {

    class Reduction {
    private:
        const GIS_Data::KoenigGraph& g;
        std::vector<bool> reduced_elements;
        std::vector<int> vdd_net, gnd_net;

        struct LogicElem {
            std::string name;
            std::vector<int> inputs;
            std::vector<int> outputs;
            std::vector<int> transistors;

            LogicElem(const std::string& name, const std::vector<int>& inputs, const std::vector<int>& outputs, const std::vector<int>& transistors);
        };

        std::vector<LogicElem> foundElems;

        void findPowerNets(const std::vector<std::string>& nets_name, const std::string& name, std::vector<int>& power_net);
        bool findInvertors(int input_net, int first_t, std::unordered_set<int>& out_nets);
        bool powerCheck(int transistor);
        bool findNand(int input_net, int first_t, std::unordered_set<int>& out_nets);
        bool findNandIn1(int input_net, int first_t, std::unordered_set<int>& out_nets);
        bool findNandIn2(int input_net, int first_t, std::unordered_set<int>& out_nets);
        bool findNor(int input_net, int first_t, std::unordered_set<int>& out_nets);

        char type(int transistor);
        GIS_Data::KoenigGraph GenerateGraph();
        
    public:
        Reduction(const GIS_Data::KoenigGraph& g);

        GIS_Data::KoenigGraph start();
    };
}
