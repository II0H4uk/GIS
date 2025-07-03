#pragma once

#include <string>

namespace GIS_Data {

    class Config {
    private:
        std::string inputPath1;
        std::string inputPath2;
        std::string outputPath;
    public:
        Config(const std::string& inputPath1,const std::string& inputPath2, const std::string& outputPath);

        const std::string& GetInput1() const;
        const std::string& GetInput2() const;
        const std::string& GetOutput() const;
    };
}
