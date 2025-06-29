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

namespace GIS_Parser {

    class GISPARSER_API SpiceParser {
    private:

    public:
        static void Start();
    };
}
