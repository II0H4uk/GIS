#pragma once

#ifdef GISPARSER_EXPORTS
    #define GISPARSER_API __declspec(dllexport)
#else
    #define GISPARSER_API __declspec(dllimport)
#endif // GISPARSER_EXPORTS

#include "pch.h"
#include "Config.h"

namespace GIS_Parser {

    class GISPARSER_API Config {
    private:

    public:
        static GIS_Data::Config Parse(const std::string& filePath);
    };
}
