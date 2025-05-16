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

#include "Graph.h"
#include <vector>

namespace GIS_Algs {

    class GISALG_API SubGraphIso {
    private:
        static std::vector<std::vector<double>> CalcSimMat(const GIS_Data::Graph& g1, const GIS_Data::Graph& g2);
        static std::vector<int> GreedyMatch(const std::vector<std::vector<double>>& simMat, double error = 0.3);
        static std::pair<int, int> CalcVertTags(const std::vector<std::vector<int>>& G, int v);
        static double CompareTags(const std::vector<GIS_Data::TagType>& tags1, const std::vector<GIS_Data::TagType>& tags2, int n);
    public:
        static std::vector<int> Start(const GIS_Data::Graph& g1, const GIS_Data::Graph& g2);
    };
}


