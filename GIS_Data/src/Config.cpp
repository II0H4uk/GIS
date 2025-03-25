#include "pch.h"
#include "Config.h"

namespace GIS_Data {

    Config::Config(const std::string& inputPath1,const std::string& inputPath2, const std::string& outputPath) : inputPath1(inputPath1),inputPath2(inputPath2), outputPath(outputPath) {}

    std::string Config::GetInput1() {
        return inputPath1;
    }
    std::string Config::GetInput2() {
        return inputPath2;
    }

    std::string Config::GetOutput() {
        return outputPath;
    }
}
