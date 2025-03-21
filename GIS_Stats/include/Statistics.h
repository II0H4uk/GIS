#pragma once

#ifdef GISSTATS_EXPORTS
    #define GISSTATS_API __declspec(dllexport)
#else
    #define GISSTATS_API __declspec(dllimport)
#endif // GISSTATS_EXPORTS

#include "pch.h"

namespace GIS_Stats {

    class GISSTATS_API Statistics {
    private:

    public:
        static void Save(const double& time, const bool& result, const int& nodeCount);
    };
}
