#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <sstream>

namespace GIS_Generator {

    class SpiceGenerator {
    private:
        struct Component {
            std::string name;
            std::string type; // "NAND", "NOT", "DIODE", "NOTNOT"
            std::vector<std::string> nodes;
        };

        static std::string generateComponentLine(const Component& comp, int& instanceNum);

        static std::string generateRandomNetName(int& netCounter);

        static Component generateRandomComponent(int& netCounter);

    public:
        static std::string generateNandSubcircuit(bool withError = false);

        static std::string generateNotSubcircuit();

        static std::string generateNotNotSubcircuit();

        static std::pair<std::string, std::string> generateIsomorphicCircuits(int numComponents, int seed = 42);
    };
}
