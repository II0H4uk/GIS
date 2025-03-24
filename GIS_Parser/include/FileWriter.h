#pragma once

#ifdef _WIN32
    #ifdef GISPARSER_EXPORTS
        #define GISPARSER_API __declspec(dllexport)
    #else
        #define GISPARSER_API __declspec(dllimport)
    #endif
#else
    #define GISPARSER_API
#endif

#include "pch.h"

using namespace std;

namespace GIS_Parser {

    class GISPARSER_API FileWriter {
    private:

    public:
        static void WriteStringToFile(const string& str, const string& filePath);
    };
}