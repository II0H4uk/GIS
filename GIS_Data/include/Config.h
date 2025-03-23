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

#include "pch.h"

namespace GIS_Data {

    class GISDATA_API Config {
    private:
        std::string inputPath;
        std::string outputPath;
    public:
        Config(const std::string& inputPath, const std::string& outputPath);

        std::string GetInput();
        std::string GetOutput();
    };
}
