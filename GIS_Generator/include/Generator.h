#pragma once

#ifdef _WIN32
    #ifdef GISGENERATOR_EXPORTS
        #define GISGENERATOR_API __declspec(dllexport)
    #else
        #define GISGENERATOR_API __declspec(dllimport)
    #endif
#else
    #define GISGENERATOR_API
#endif

#include "pch.h"
#include "Graph.h"

namespace GIS_Generator {

    class GISGENERATOR_API Generator {
    private:

    public:
        static GIS_Data::GraphPair Generate(bool isIsomorphic);
        //static GIS_Data::GraphPair Generate(bool isIsomorphic);
        //void Generate(bool isIsomorphic);
    };
}
