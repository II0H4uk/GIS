#pragma once

#include <Config.h>
#include <Subcircuit.h>
#include <KoenigGraph.h>
#include <string>
#include <vector>
#include <chrono>

namespace GIS_Stats {

    class Statistics {
    private:
        static std::string WriteCircuitParams(const GIS_Data::KoenigGraph& g, const std::string& circName);
        static std::string WriteTime(const std::vector<std::chrono::milliseconds>& time);
        static std::string WriteBijection(const std::vector<std::pair<std::vector<int>, std::vector<int>>>& map,
            const GIS_Data::KoenigGraph& g1,
            const GIS_Data::KoenigGraph& g2,
            const GIS_Data::Config& config);
        static std::string WriteUndefinedElements(const std::vector<std::pair<std::vector<int>, std::vector<int>>>& map,
            const GIS_Data::KoenigGraph& g1,
            const GIS_Data::KoenigGraph& g2,
            const GIS_Data::Config& config);
        static std::string WriteUndefFromVector(const GIS_Data::KoenigGraph& g, const std::vector<int>& vec);
    public:
        static void WriteStat(const std::vector<std::pair<std::vector<int>, std::vector<int>>>& map,
            const GIS_Data::KoenigGraph& g1,
            const GIS_Data::KoenigGraph& g2,
            const Circuits::Utils::Subcircuit& circuit1,
            const Circuits::Utils::Subcircuit& circuit2,
            const std::vector<std::chrono::milliseconds>& time,
            const GIS_Data::Config& config);
    };
}
