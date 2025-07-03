#pragma once

#include <string>
#include <vector>

namespace GIS_Stats {

    class Statistics {
    private:

    public:
        static void Save(const double& time, const std::vector<int>& result, const int& nodeCount, const std::string& filePath);
    };
}
