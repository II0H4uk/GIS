#include "pch.h"
#include "Benchmark.h"
#include "ConfigParser.h"
#include <Subcircuit.h>
#include <SpiceParser.h>
#include <SignalMatching.h>
#include <Reduction.h>
#include <Statistics.h>
#include <algorithm>
#include <Utils.h>

#include <chrono>
#include <Generator.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, char* argv[]) {

    /*int numComponents = 20; // Количество подсхем в основной схеме
    int seed = 12345;      // Seed для воспроизводимости

    auto [circuitA, circuitB] = GIS_Generator::SpiceGenerator::generateIsomorphicCircuits(numComponents, seed);

    // Сохраняем в файлы
    std::ofstream fileA("circuit_A.sp");
    std::ofstream fileB("circuit_B.sp");

    fileA << circuitA;
    fileB << circuitB;

    fileA.close();
    fileB.close();

    return 0;*/

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
    GIS_Data::KoenigGraph koenG1(circuit1);
    GIS_Data::KoenigGraph koenG2(circuit2);
    timerE = std::chrono::high_resolution_clock::now();
    time.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(timerE - timerS));

    GIS_Core::Benchmark bench;
    if (config.GetAlgorithm() == "SignalAlg") { bench.SetStrat(std::make_unique<GIS_Algs::SignalMatching>()); }
    else { bench.SetStrat(std::make_unique<GIS_Algs::SignalMatching>()); }

    GIS_Algs::Reduction reducer_g1(koenG1);
    GIS_Data::KoenigGraph g1_reduced = reducer_g1.start();
    GIS_Algs::Reduction reducer_g2(koenG2);
    GIS_Data::KoenigGraph g2_reduced = reducer_g2.start();

    timerS = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<std::vector<int>, std::vector<int>>> map = bench.Process(g1_reduced, g2_reduced, config);
    timerE = std::chrono::high_resolution_clock::now();
    time.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(timerE - timerS));

    GIS_Stats::Statistics::WriteStat(map, g1_reduced, g2_reduced, circuit1, circuit2, time, config);

    return 0;
}
 