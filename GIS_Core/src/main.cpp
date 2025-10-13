#include "pch.h"
#include "Benchmark.h"
#include "ConfigParser.h"
#include <Subcircuit.h>
#include <SpiceParser.h>
#include <BipartGraph.h>
#include <MaxMatching.h>
#include <EnhancedMatching.h>
#include <SignalMatching.h>
#include <Statistics.h>
#include <algorithm>
#include <Utils.h>

#include <chrono>

int main(int argc, char* argv[]) {
    std::vector<std::chrono::milliseconds> time;
    std::chrono::steady_clock::time_point timerS;
    std::chrono::steady_clock::time_point timerE;

    timerS = std::chrono::high_resolution_clock::now();
    GIS_Data::Config config = GIS_Parser::Config::Parse("../config.ini");
    Circuits::Utils::SpiceParser parser;

    Circuits::Utils::Subcircuit circuit1 = parser.ParseSPICE(config.GetInput1());
    Circuits::Utils::Subcircuit circuit2 = parser.ParseSPICE(config.GetInput2());
    timerE = std::chrono::high_resolution_clock::now();
    time.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(timerE - timerS));

    timerS = std::chrono::high_resolution_clock::now();
    GIS_Data::KoenigGraph koenG1(circuit1, 2);
    GIS_Data::KoenigGraph koenG2(circuit2, 2);
    timerE = std::chrono::high_resolution_clock::now();
    time.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(timerE - timerS));

    GIS_Core::Benchmark bench;
    if (config.GetAlgorithm() == "SignalAlg") { bench.SetStrat(std::make_unique<GIS_Algs::SignalMatching>()); }
    else if (config.GetAlgorithm() == "EnhancedMatching") { bench.SetStrat(std::make_unique<GIS_Algs::EnhancedMatching>()); }
    else if (config.GetAlgorithm() == "MaxMatching") { bench.SetStrat(std::make_unique<GIS_Algs::MaxMatching>()); }
    else { bench.SetStrat(std::make_unique<GIS_Algs::SignalMatching>()); }
    bench.SetStrat(std::make_unique<GIS_Algs::SignalMatching>());

    timerS = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<std::vector<int>, std::vector<int>>> map = bench.Process(koenG1, koenG2, config);
    timerE = std::chrono::high_resolution_clock::now();
    time.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(timerE - timerS));

    GIS_Stats::Statistics::WriteStat(map, koenG1, koenG2, circuit1, circuit2, time, config);

    return 0;
}
