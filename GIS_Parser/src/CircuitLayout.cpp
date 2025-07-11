#include "pch.h"
#include <CircuitLayout.h>
#include <unordered_map>

namespace GIS_Parser {
    Circuits::Utils::Subcircuit CircuitLayout::CreateMainCircuit(const std::vector<Circuits::Utils::Subcircuit>& circuits) {
        Init(circuits);

        int mainCircInd = FindMainCircuit(circuits);

        mainCirc.name = circuits[mainCircInd].name;
        mainCirc.pins = circuits[mainCircInd].pins;

        std::unordered_map<std::string, int> nets;
        std::vector<int> values = GetNets(mainCirc.pins, nets);

        CreateSubCircuit(mainCircInd, values);

        mainCirc.netsCount = netsCount;

        return mainCirc;
    }

    void CircuitLayout::CreateSubCircuit(int index, const std::vector<int>& inputNets) {
        Circuits::Utils::Subcircuit currCirc = circuits[index];
        std::unordered_map<std::string, int> nets;

        for (int i = 0; i < currCirc.pins.size(); ++i)
            nets[currCirc.pins[i]] = inputNets[i];

        for (int i = 0; i < currCirc.components.size(); ++i) {
            std::vector<int> intVals = GetNets(currCirc.components[i].chain, nets);

            if (!currCirc.components[i].id.starts_with("X")) {
                mainCirc.components.push_back(currCirc.components[i]);

                mainCirc.components.back().chainInt = intVals;
                continue;
            }

            CreateSubCircuit(circuitsId[currCirc.components[i].typeComponent], intVals);
        }
    }

    std::vector<int> CircuitLayout::GetNets(const std::vector<std::string>& chain, std::unordered_map<std::string, int>& nets) {
        std::vector<int> vals;
        vals.reserve(chain.size());

        for (int i = 0; i < chain.size(); ++i) {
            if (nets.find(chain[i]) == nets.end())
                nets[chain[i]] = netsCount++;
            vals.push_back(nets[chain[i]]);
        }
        return vals;
    }

    int CircuitLayout::FindMainCircuit(const std::vector<Circuits::Utils::Subcircuit>& circuits) {
        std::vector<bool> used(circuits.size());
        for (int i = 0; i < circuits.size(); ++i)
            if (circuits[i].components.size() == 0)
                used[i] = true;

        for (int i = 0; i < circuits.size(); ++i) {
            for (int j = 0; j < circuits[i].components.size(); ++j) {
                if (!circuits[i].components[j].id.starts_with('X'))
                    continue;

                used[circuitsId[circuits[i].components[j].typeComponent]] = true;
            }
        }
        for (int i = 0; i < used.size(); ++i)
            if (!used[i])
                return i;
        return -1;
    }

    void CircuitLayout::Init(const std::vector<Circuits::Utils::Subcircuit>& circuits) {
        netsCount = 0;
        globNets.clear();
        CircuitLayout::circuits = circuits;

        for (int i = 0; i < circuits.size(); ++i)
            circuitsId[circuits[i].name] = i;
    }
}
