#include "pch.h"
#include "Benchmark.h"
#include "ConfigParser.h"

int main(int argc, char* argv[]) {

    GIS_Core::Benchmark::Init(GIS_Parser::Config::Parse("../config.ini"));
    std::cout << "yay :D" << std::endl;
    return 0;
}
