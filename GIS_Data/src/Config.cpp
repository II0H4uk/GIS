#include "pch.h"
#include "Config.h"

namespace GIS_Data {

    Config::Config(const std::string& inputPath, const std::string& outputPath) : inputPath(inputPath), outputPath(outputPath) {}

    std::string Config::GetInput() {
        return inputPath;
    }

    std::string Config::GetOutput() {
        return outputPath;
    }
}
