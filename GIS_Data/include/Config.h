#pragma once

#ifdef _WIN32
    #ifdef GISDATA_EXPORTS
        #define GISDATA_API __declspec(dllexport)
    #else
        #define GISDATA_API __declspec(dllimport)
    #endif
#else
    #define GISDATA_API
#endif

#include <string>

namespace GIS_Data {

    class GISDATA_API Config {
    private:
        std::string inputPath1;
        std::string inputPath2;
        std::string outputPath;
    public:
        Config(const std::string& inputPath1,const std::string& inputPath2, const std::string& outputPath);

        std::string GetInput1();
        std::string GetInput2();
        std::string GetOutput();
    };
}
