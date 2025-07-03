#pragma once

#include "GraphPair.h"

namespace GIS_Core {

    class ValidateMatch {
    private:

    public:
        static void Start(GIS_Data::GraphPair& pair, std::vector<std::pair<int, int>>& matching);
    };
}
