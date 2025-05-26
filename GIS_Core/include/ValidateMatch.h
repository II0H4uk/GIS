#pragma once

#ifdef _WIN32
    #ifdef GISCORE_EXPORTS
        #define GISCORE_API __declspec(dllexport)
    #else
        #define GISCORE_API __declspec(dllimport)
    #endif
#else
    #define GISCORE_API
#endif

#include "GraphPair.h"

namespace GIS_Core {

    class GISCORE_API ValidateMatch {
    private:

    public:
        static void Start(const GIS_Data::GraphPair& pair, std::vector<std::pair<int, int>>& matching);
    };
}
