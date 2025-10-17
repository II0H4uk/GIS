#include "pch.h"
#include "BipartGraph.h"
#include "MaxMatching.h"
#include "SpiceParser.h"

TEST(MaxMatchTests, SimpleTest) {

    GIS_Data::Config config("../../Graph_Data/test1/netlist.sp", "../../Graph_Data/test1/netlist.sp");

    Circuits::Utils::SpiceParser parser;
    Circuits::Utils::Subcircuit circuit1 = parser.ParseSPICE(config.GetInput1());
    Circuits::Utils::Subcircuit circuit2 = parser.ParseSPICE(config.GetInput2());

    GIS_Data::KoenigGraph koenG1(circuit1, 2);
    GIS_Data::KoenigGraph koenG2(circuit2, 2);

    GIS_Algs::MaxMatching maxMatch;

    std::vector<std::pair<std::vector<int>, std::vector<int>>> matching = maxMatch.Start(koenG1, koenG2, config);

    assert(matching.size() == 8);
}

TEST(MaxMatchTests, ComplexTest) {

    std::unordered_map<std::string, std::string> configString;
    configString["Input1"] = "../../Graph_Data/test2_1/netlist.sp";
    configString["Input2"] = "../../Graph_Data/test2_2/netlist.sp";
    configString["Output"] = "../Graph_Data/output.stats";
    configString["Algorithm"] = "SignalAlg";
    configString["MaxMatchIterations"] = "10";
    configString["SignalIterations"] = "32";
    configString["QuantScale"] = "1";
    configString["EnableStat"] = "false";
    configString["WriteCircuitParams"] = "false";
    configString["WriteTime"] = "false";
    configString["WriteBijection"] = "false";
    configString["WriteOnlyElements"] = "false";
    configString["WriteUndefinedElements"] = "false";
    configString["WriteToConsole"] = "false";
    GIS_Data::Config config(configString);

    Circuits::Utils::SpiceParser parser;
    Circuits::Utils::Subcircuit circuit1 = parser.ParseSPICE(config.GetInput1());
    Circuits::Utils::Subcircuit circuit2 = parser.ParseSPICE(config.GetInput2());

    GIS_Data::KoenigGraph koenG1(circuit1, 2);
    GIS_Data::KoenigGraph koenG2(circuit2, 2);

    GIS_Algs::MaxMatching maxMatch;

    std::vector<std::pair<std::vector<int>, std::vector<int>>> matching = maxMatch.Start(koenG1, koenG2, config);

    assert(matching.size() == 14);
}
