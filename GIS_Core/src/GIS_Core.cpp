#include "pch.h"
#include "Benchmark.h"
#include "ConfigParser.h"
#include "MaxMatching.h"
#include "BipartGraph.h"
#include <iostream>
#include <cassert>

int main(int argc, char* argv[]) {

    GIS_Core::Benchmark::Init(GIS_Parser::Config::Parse("../config.ini"));

    return 0;
}
