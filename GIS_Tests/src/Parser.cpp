#include "pch.h"
#include <Config.h>
#include <Subcircuit.h>
#include <SpiceParser.h>

TEST(Parser, readingTest) {

    GIS_Data::Config config("../../Graph_Data/parsingTest1/netlist.sp", "../../Graph_Data/parsingTest1/netlist.sp");

    Circuits::Utils::SpiceParser parser;
    Circuits::Utils::Subcircuit circuit = parser.ParseSPICE(config.GetInput1());

    Circuits::Utils::Subcircuit expectedCirc;
    expectedCirc.name = "circuit";
    expectedCirc.pins = std::vector<std::string>({"4", "5", "vdd!", "gnd!"});
    expectedCirc.components = std::vector<Circuits::Utils::TopologyComponent>(7);
    expectedCirc.components[0].id = "D0";
    expectedCirc.components[1].id = "D1";
    expectedCirc.components[2].id = "M2";
    expectedCirc.components[3].id = "M3";
    expectedCirc.components[4].id = "M4";
    expectedCirc.components[5].id = "M5";
    expectedCirc.components[6].id = "M6";
    expectedCirc.netsCount = 8;

    ASSERT_EQ(circuit.name, expectedCirc.name);
    ASSERT_EQ(circuit.pins, expectedCirc.pins);
    for (int i = 0; i < expectedCirc.components.size(); ++i) {
        ASSERT_EQ(circuit.components[i].id, expectedCirc.components[i].id);
    }

    ASSERT_EQ(circuit.netsCount, expectedCirc.netsCount);
}

TEST(Parser, recursionÑheck) {

    GIS_Data::Config config("../../Graph_Data/test1/netlist.sp", "../../Graph_Data/parsingTest1/netlist.sp");

    Circuits::Utils::SpiceParser parser;
    Circuits::Utils::Subcircuit circuit = parser.ParseSPICE(config.GetInput1());

    Circuits::Utils::Subcircuit expectedCirc;
    expectedCirc.name = "NotNot";
    expectedCirc.pins = std::vector<std::string>({ "x1", "y1", "vdd!", "gnd!" });
    expectedCirc.components = std::vector<Circuits::Utils::TopologyComponent>(4);
    expectedCirc.components[0].id = "M0";
    expectedCirc.components[1].id = "M1";
    expectedCirc.components[2].id = "M2";
    expectedCirc.components[3].id = "M3";
    expectedCirc.netsCount = 5;

    ASSERT_EQ(circuit.name, expectedCirc.name);
    ASSERT_EQ(circuit.pins, expectedCirc.pins);
    for (int i = 0; i < expectedCirc.components.size(); ++i) {
        ASSERT_EQ(circuit.components[i].id, expectedCirc.components[i].id);
    }

    ASSERT_EQ(circuit.netsCount, expectedCirc.netsCount);
}