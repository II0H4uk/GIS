#pragma once

#ifdef GISGENERATOR_EXPORTS
    #define GISGENERATOR_API __declspec(dllexport)
#else
    #define GISGENERATOR_API __declspec(dllimport)
#endif // GISGENERATOR_EXPORTS

#include "pch.h"

namespace GIS_Generator {

    class GISGENERATOR_API Generator {
    private:

    public:

    };
}
