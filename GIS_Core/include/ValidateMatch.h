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

namespace GIS_Core {

    class GISCORE_API ValidateMatch {


    };
}
