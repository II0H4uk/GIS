#include "pch.h"
#include <KoenigGraph.h>
#include <Config.h>
#include <SpiceParser.h>
#include <Subcircuit.h>

TEST(KoenigGraphTest, adjListCheck) {

    GIS_Data::Config config("../../Graph_Data/test4/netlist.sp", "../../Graph_Data/test4/netlist.sp");

    Circuits::Utils::SpiceParser parser;
    Circuits::Utils::Subcircuit circuit = parser.ParseSPICE(config.GetInput1());

    GIS_Data::KoenigGraph koenG(circuit, 2);

    std::vector<std::vector<int>> expAdjList(10, std::vector<int>());
    expAdjList[0].push_back(8);
    expAdjList[1].push_back(8);
    expAdjList[2].push_back(8);
    expAdjList[3].push_back(9);
    expAdjList[4] = { 0, 2 };
    expAdjList[5] = { 1, 3 };
    expAdjList[6] = { 0, 1 };
    expAdjList[7].push_back(3);
    expAdjList[9].push_back(2);

    ASSERT_EQ(koenG.getAdjList(), expAdjList);
}