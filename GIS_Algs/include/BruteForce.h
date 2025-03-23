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

#include "pch.h"
#include "Graph.h"

namespace GIS_Algs {

    class GISALG_API BruteForce {
    private:

    public:
        static bool Start(const GIS_Data::Graph& graph);
    };
}
