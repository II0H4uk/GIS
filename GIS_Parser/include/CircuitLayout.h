#pragma once

#include <Subcircuit.h>
#include <unordered_map>
#include <vector>

namespace GIS_Parser {
    class CircuitLayout {
    private:
        inline static int netsCount = 0;
        inline static std::unordered_map<std::string, int> globNets;
        inline static std::unordered_map<std::string, int> circuitsId;
        inline static std::vector<Circuits::Utils::Subcircuit> circuits;
        inline static Circuits::Utils::Subcircuit mainCirc;

        static void Init(const std::vector<Circuits::Utils::Subcircuit>& circuits);
        static int FindMainCircuit(const std::vector<Circuits::Utils::Subcircuit>& circuits);
        static void CreateSubCircuit(int index, const std::vector<int>& inputNets);
        static std::vector<int> GetNets(const std::vector<std::string>& chain, std::unordered_map<std::string, int>& nets);
    public:
        static Circuits::Utils::Subcircuit CreateMainCircuit(const std::vector<Circuits::Utils::Subcircuit>& circuits);
    };
}