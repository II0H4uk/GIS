#pragma once

#ifdef _WIN32
    #ifdef GISSTATS_EXPORTS
        #define GISSTATS_API __declspec(dllexport)
    #else
        #define GISSTATS_API __declspec(dllimport)
    #endif
#else
    #define GISSTATS_API
#endif

#include <string>

namespace GIS_Stats {

    class GISSTATS_API Statistics {
    private:

    public:
        static void Save(const double& time, const bool& result, const int& nodeCount, const std::string& filePath);
    };
}
