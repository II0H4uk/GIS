#include "pch.h"
#include "Config.h"

namespace GIS_Data {

    Config::Config(const std::string& inputPath1,const std::string& inputPath2, const std::string& outputPath) : inputPath1(inputPath1),inputPath2(inputPath2), outputPath(outputPath) {}

    const std::string& Config::GetInput1() const {
        return inputPath1;
    }
    const std::string& Config::GetInput2() const {
        return inputPath2;
    }

    const std::string& Config::GetOutput() const {
        return outputPath;
    }
}
