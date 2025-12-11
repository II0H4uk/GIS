#include "pch.h"
#include "Generator.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <sstream>
#include <fstream>
#include <algorithm>

namespace GIS_Generator {

    std::string SpiceGenerator::generateComponentLine(const Component& comp, int& instanceNum) {
        std::stringstream ss;

        if (comp.type == "NAND") {
            ss << "X" << instanceNum++ << " " << comp.nodes[0] << " " << comp.nodes[1]
                << " " << comp.nodes[2] << " vdd! gnd! NAND";
        }
        else if (comp.type == "NOT") {
            ss << "X" << instanceNum++ << " " << comp.nodes[0]
                << " " << comp.nodes[1] << " vdd! gnd! NOT";
        }
        else if (comp.type == "DIODE") {
            ss << "D" << instanceNum++ << " " << comp.nodes[0]
                << " " << comp.nodes[1] << " dn";
        }
        else if (comp.type == "NOTNOT") {
            ss << "X" << instanceNum++ << " " << comp.nodes[0]
                << " " << comp.nodes[1] << " vdd! gnd! NotNot";
        }

        return ss.str();
    }

    std::string SpiceGenerator::generateRandomNetName(int& netCounter) {
        return std::to_string(netCounter++);
    }

    SpiceGenerator::Component SpiceGenerator::generateRandomComponent(int& netCounter) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> typeDist(0, 2);

        Component comp;
        int type = typeDist(gen);

        switch (type) {
        case 0: // NAND
            comp.type = "NAND";
            comp.nodes = { generateRandomNetName(netCounter),
                         generateRandomNetName(netCounter),
                         generateRandomNetName(netCounter) };
            break;
        case 1: // NOT
            comp.type = "NOT";
            comp.nodes = { generateRandomNetName(netCounter),
                         generateRandomNetName(netCounter) };
            break;
        case 2: // DIODE
            comp.type = "DIODE";
            comp.nodes = { generateRandomNetName(netCounter),
                         generateRandomNetName(netCounter) };
            break;
        }

        return comp;
    }

    std::string SpiceGenerator::generateNandSubcircuit(bool withError) {
        std::stringstream ss;
        ss << ".SUBCKT NAND x1 x2 y vdd! gnd!\n"
            << "** N=4 EP=4 IP=32 FDC=8\n"
            << "M0 y x1 vdd! vdd! pmos_h\n"
            << "M1 y x2 vdd! vdd! pmos_h\n"
            << "M2 y x1 1 1 nmos_h\n"
            << "M3 1 x2 gnd! gnd!" << (withError ? "" : " nmos_h") << "\n"
            << ".ENDS\n"
            << "***************************************\n";
        return ss.str();
    }

    std::string SpiceGenerator::generateNotSubcircuit() {
        return ".SUBCKT NOT x1 y1 vdd! gnd!\n"
            "** N=4 EP=0 IP=0 FDC=0\n"
            "M0 y1 x1 vdd! vdd! pmos_h\n"
            "M1 y1 x1 gnd! gnd! nmos_h\n"
            ".ENDS\n"
            "***************************************\n";
    }

    std::string SpiceGenerator::generateNotNotSubcircuit() {
        return ".SUBCKT NotNot x1 y1 vdd! gnd!\n"
            "** N=4 EP=4 IP=32 FDC=8\n"
            "X0 x1 1 vdd! gnd! NOT\n"
            "X1 1 y1 vdd! gnd! NOT\n"
            ".ENDS\n"
            "***************************************\n";
    }

    std::pair<std::string, std::string> SpiceGenerator::generateIsomorphicCircuits(
        int numComponents,
        int seed
    ) {
        std::mt19937 gen(seed);
        std::uniform_int_distribution<> compDist(0, numComponents - 1);

        // Генерируем исходную схему
        std::vector<Component> components;
        int netCounter = 1;

        // Генерируем случайные компоненты
        for (int i = 0; i < numComponents; i++) {
            components.push_back(generateRandomComponent(netCounter));
        }

        // Создаем выходной узел
        std::string outputNet = generateRandomNetName(netCounter);

        // Генерируем первую схему
        std::stringstream circuitA;
        circuitA << "* SPICE NETLIST\n"
            << "***************************************\n"
            << ".SUBCKT BigCircuit x1 x2 x3 x4 y1 vdd! gnd!\n"
            << "** N=4 EP=4 IP=32 FDC=8\n";

        int instanceNum = 0;
        for (const auto& comp : components) {
            circuitA << generateComponentLine(comp, instanceNum) << "\n";
        }

        // Подключаем выход
        if (!components.empty()) {
            circuitA << "X" << instanceNum++ << " "
                << components.back().nodes.back() << " " << outputNet
                << " y1 vdd! gnd! NAND\n";
        }

        circuitA << ".ENDS\n"
            << "***************************************\n"
            << generateNandSubcircuit(false)
            << generateNotSubcircuit();

        // Генерируем вторую схему с добавлением NotNot
        std::stringstream circuitB;
        circuitB << "* SPICE NETLIST\n"
            << "***************************************\n"
            << ".SUBCKT BigCircuit x1 x2 x3 x4 y1 vdd! gnd!\n"
            << "** N=4 EP=4 IP=32 FDC=8\n";

        // Выбираем случайное место для вставки NotNot
        int insertPos = compDist(gen);
        instanceNum = 0;

        // Копируем компоненты до точки вставки
        for (int i = 0; i < insertPos && i < numComponents; i++) {
            circuitB << generateComponentLine(components[i], instanceNum) << "\n";
        }

        // Вставляем NotNot
        if (insertPos < numComponents) {
            std::string originalNet = components[insertPos].nodes[0];
            std::string newNet1 = generateRandomNetName(netCounter);
            std::string newNet2 = generateRandomNetName(netCounter);

            // Модифицируем следующий компонент, чтобы он использовал выход NotNot
            if (insertPos < numComponents - 1) {
                components[insertPos + 1].nodes[0] = newNet2;
            }

            // Добавляем NotNot
            circuitB << "X" << instanceNum++ << " " << originalNet << " "
                << newNet1 << " vdd! gnd! NOT\n";
            circuitB << "X" << instanceNum++ << " " << newNet1 << " "
                << newNet2 << " vdd! gnd! NOT\n";
        }

        // Копируем остальные компоненты
        for (int i = insertPos; i < numComponents; i++) {
            circuitB << generateComponentLine(components[i], instanceNum) << "\n";
        }

        // Подключаем выход
        if (!components.empty()) {
            circuitB << "X" << instanceNum++ << " "
                << components.back().nodes.back() << " " << outputNet
                << " y1 vdd! gnd! NAND\n";
        }

        circuitB << ".ENDS\n"
            << "***************************************\n"
            << generateNandSubcircuit(true)  // С ошибкой
            << generateNotNotSubcircuit()
            << generateNotSubcircuit();

        return { circuitA.str(), circuitB.str() };
    }
}