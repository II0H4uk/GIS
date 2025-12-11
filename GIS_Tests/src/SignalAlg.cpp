#include "pch.h"
#include <SignalMatching.h>
#include <SpiceParser.h>
#include <KoenigGraph.h>
#include <Subcircuit.h>
#include <Config.h>

TEST(SignalAlgTests, SimpleTest) {

    GIS_Data::Config config("../../Graph_Data/test1/netlist.sp", "../../Graph_Data/test1/netlist.sp");

    Circuits::Utils::SpiceParser parser;
    Circuits::Utils::Subcircuit circuit1 = parser.ParseSPICE(config.GetInput1());
    Circuits::Utils::Subcircuit circuit2 = parser.ParseSPICE(config.GetInput2());

    GIS_Data::KoenigGraph koenG1(circuit1, 2);
    GIS_Data::KoenigGraph koenG2(circuit2, 2);

    GIS_Algs::SignalMatching signalMatch;

    std::vector<std::pair<std::vector<int>, std::vector<int>>> matching = signalMatch.Start(koenG1, koenG2, config);
    std::vector<std::pair<std::vector<int>, std::vector<int>>> expected{
        {{0}, {0}},
        {{1}, {1}},
        {{2}, {2}},
        {{3}, {3}},
        {{8}, {8}},
        {{4, 5}, {4, 5}},
        {{7}, {7}},
        {{6}, {6}}
    };

    ASSERT_EQ(matching, expected);
}

TEST(SignalAlgTests, ComplexTest) {

    GIS_Data::Config config("../../Graph_Data/test2_1/netlist.sp", "../../Graph_Data/test2_2/netlist.sp");

    Circuits::Utils::SpiceParser parser;
    Circuits::Utils::Subcircuit circuit1 = parser.ParseSPICE(config.GetInput1());
    Circuits::Utils::Subcircuit circuit2 = parser.ParseSPICE(config.GetInput2());

    GIS_Data::KoenigGraph g1(circuit1, 2);
    GIS_Data::KoenigGraph g2(circuit2, 2);

    GIS_Algs::SignalMatching signalMatch;

    std::vector<std::pair<std::vector<int>, std::vector<int>>> map = signalMatch.Start(g1, g2, config);

    std::vector<int> undefined;

    for (int i = 0; i < map.size(); ++i) {
        if (map[i].first.size() > 0 && map[i].second.size() > 0)
            continue;
        if (map[i].first.size() > 0 && map[i].first[0] >= g1.getNodeCount() ||
            map[i].second.size() > 0 && map[i].second[0] >= g2.getNodeCount())
            continue;
        if (map[i].first.size() == 0) {
            undefined.push_back(map[i].second[0]);
        }

        if (map[i].second.size() == 0) {
            undefined.push_back(map[i].first[0]);
        }
    }

    std::vector<int> expectedUndef({10, 9, 8, 7});

    ASSERT_EQ(undefined, expectedUndef);
}
