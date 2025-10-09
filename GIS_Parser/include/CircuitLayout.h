#pragma once

#include <Subcircuit.h>
#include <unordered_map>
#include <vector>

namespace GIS_Parser {
    class CircuitLayout {
    private:
        static int elCounter;

        static int FindMainCircuit(const std::vector<Circuits::Utils::Subcircuit>& circuits, std::unordered_map<std::string, int>& circuitsId);
        static void CreateSubCircuit(int index, const std::vector<int>& inputNets, std::unordered_map<std::string, int>& circuitsId, const std::vector<Circuits::Utils::Subcircuit>& circuits, Circuits::Utils::Subcircuit& mainCirc);
        static std::vector<int> GetNets(const std::vector<std::string>& chain, std::unordered_map<std::string, int>& nets, Circuits::Utils::Subcircuit& mainCirc);
    public:
        static Circuits::Utils::Subcircuit CreateMainCircuit(const std::vector<Circuits::Utils::Subcircuit>& circuits);
    };
}
