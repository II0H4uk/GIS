#include "pch.h"
#include "Benchmark.h"
#include "ConfigParser.h"
#include <Subcircuit.h>
#include <SpiceParser.h>
#include <BipartGraph.h>
#include <MaxMatching.h>
#include <EnhancedMatching.h>
#include <algorithm>

#include <chrono>

int main(int argc, char* argv[]) {
    using namespace std::chrono;

    auto parseS = high_resolution_clock::now();
    GIS_Data::Config config = GIS_Parser::Config::Parse("../config.ini");
    Circuits::Utils::SpiceParser parser;

    Circuits::Utils::Subcircuit circuit1 = parser.ParseSPICE(config.GetInput1());
    Circuits::Utils::Subcircuit circuit2 = parser.ParseSPICE(config.GetInput2());
    auto parseE = high_resolution_clock::now();
    auto parseT = std::chrono::duration_cast<milliseconds>(parseE - parseS);

    auto kGraphS = high_resolution_clock::now();
    GIS_Data::KoenigGraph koenG1(circuit1, 2);
    GIS_Data::KoenigGraph koenG2(circuit2, 2);
    auto kGraphE = high_resolution_clock::now();
    auto kGraphT = std::chrono::duration_cast<milliseconds>(kGraphE - kGraphS);

    //GIS_Core::Benchmark::MaxMatching(koenG1, koenG2);

    auto algS = high_resolution_clock::now();
    GIS_Core::Benchmark::SignalMatching(koenG1, koenG2);
    auto algE = high_resolution_clock::now();
    auto algT = std::chrono::duration_cast<milliseconds>(algE - algS);

    std::cout << "\nRead time: " << parseT;
    std::cout << "\nkGraph time: " << kGraphT;
    std::cout << "\nAlg time: " << algT;

    return 0;
}
