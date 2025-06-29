#pragma once

#ifdef _WIN32
    #ifdef GISALGS_EXPORTS
        #define GISALG_API __declspec(dllexport)
    #else
        #define GISALG_API __declspec(dllimport)
    #endif
#else
    #define GISALG_API
#endif

#include "BipartGraph.h"

namespace GIS_Algs {

    class GISALG_API MaxMatching {
    private:

    public:
        static std::vector<std::pair<int, int>> Start(const GIS_Data::BipartGraph& bipartGraph, int n);
    };
}
