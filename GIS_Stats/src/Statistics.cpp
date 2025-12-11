#include "pch.h"
#include "Statistics.h"
#include "FileWriter.h"
#include <chrono>

namespace GIS_Stats {
    
    void Statistics::WriteStat(const std::vector<std::pair<std::vector<int>, std::vector<int>>>& map,
        const GIS_Data::KoenigGraph& g1,
        const GIS_Data::KoenigGraph& g2,
        const Circuits::Utils::Subcircuit& circuit1,
        const Circuits::Utils::Subcircuit& circuit2,
        const std::vector<std::chrono::milliseconds>& time,
        const GIS_Data::Config& config) {

        if (!config.GetEnableStat())
            return;

        std::string statisticsInfo = "Graph Isomorphism Comparison Statistics\n\n";
        statisticsInfo += "Used algorithm: " + config.GetAlgorithm() + "\n\n";

        if (config.GetWriteCircParams()) {
            statisticsInfo += WriteCircuitParams(g1, config.GetCircName1());
            statisticsInfo += WriteCircuitParams(g2, config.GetCircName2());
        }

        if (config.GetWriteTime())
            statisticsInfo += WriteTime(time);

        if (config.GetWriteBijection())
            statisticsInfo += WriteBijection(map, g1, g2, config);

        if (config.GetWriteUndefinedElements())
            statisticsInfo += WriteUndefinedElements(map, g1, g2, config);

        if (config.GetWriteToConsole())
            std::cout << statisticsInfo;

        GIS_Parser::FileWriter::WriteStringToFile(statisticsInfo, config.GetOutput());
    }

    std::string Statistics::WriteCircuitParams(const GIS_Data::KoenigGraph& g, const std::string& circName) {

        std::string params;

        params += circName + " parameters\n";
        
        params += "Elements count: " + std::to_string(g.getNodeCount()) + "\n";
        params += "Chains count: " + std::to_string(g.getHyperEdgeCount()) + "\n";

        params += "Elements type count:\n";
        for (auto type : g.getBlocksType())
            params += "\t" + type.first + ": " + std::to_string(type.second.size()) + "\n";

        params += "\n";

        return params;
    }

    std::string Statistics::WriteTime(const std::vector<std::chrono::milliseconds>& time) {
        std::string strTime = "Parse SPICE time: " + std::to_string(time[0].count()) + " ms\n";
        strTime += "Generate koenig graph time: " + std::to_string(time[1].count()) + " ms\n";
        strTime += "Alg time: " + std::to_string(time[2].count()) + " ms\n\n";

        return strTime;
    }

    std::string Statistics::WriteBijection(const std::vector<std::pair<std::vector<int>, std::vector<int>>>& map,
        const GIS_Data::KoenigGraph& g1,
        const GIS_Data::KoenigGraph& g2,
        const GIS_Data::Config& config) {

        std::string bijection = "Bijection:";

        for (int i = 0; i < map.size(); ++i) {
            if (map[i].first.size() != 1 || map[i].second.size() != 1 ||
                (config.GetWriteOnlyElements() && map[i].first[0] >= g1.getNodeCount()))
                continue;
            std::vector<int> elems1 = g1.getBlocks()[map[i].first[0]].getInnerBlocks();
            std::vector<int> elems2 = g2.getBlocks()[map[i].second[0]].getInnerBlocks();
            bijection += "\n{";
            for (size_t j = 0; j < elems1.size(); ++j) {
                bijection += std::to_string(elems1[j]);
                if (j != elems1.size() - 1) bijection += ", ";
            }
            bijection += "} -> {";
            for (size_t j = 0; j < elems2.size(); ++j) {
                bijection += std::to_string(elems2[j]);
                if (j != elems2.size() - 1) bijection += ", ";
            }
            bijection += "}";

            /*std::string first;        // <--- простое отображение элемент на элемент
            std::string second;

            if (map[i].first[0] >= g1.getNodeCount())
                first = g1.getNetName()[map[i].first[0] - g1.getNodeCount()];
            else
                first = g1.getBlocks()[map[i].first[0]].getType() + std::to_string(map[i].first[0]);

            if (map[i].second[0] >= g2.getNodeCount())
                second = g2.getNetName()[map[i].second[0] - g2.getNodeCount()];
            else
                second = g2.getBlocks()[map[i].second[0]].getType() + std::to_string(map[i].second[0]);

            bijection += std::format("{} -> {}", first, second) + "\n";*/
        }

        bijection += "\n";

        return bijection;
    }

    std::string Statistics::WriteUndefinedElements(const std::vector<std::pair<std::vector<int>, std::vector<int>>>& map,
        const GIS_Data::KoenigGraph& g1,
        const GIS_Data::KoenigGraph& g2,
        const GIS_Data::Config& config) {
        
        std::string undefined = "\nUndefined:\n";

        std::string undefG1, undefG2;

        for (int i = 0; i < map.size(); ++i) {
            if (map[i].first.size() > 0 && map[i].second.size() > 0 ||
                config.GetWriteOnlyElements() &&
                (map[i].first.size() > 0 && map[i].first[0] >= g1.getNodeCount() ||
                map[i].second.size() > 0 && map[i].second[0] >= g2.getNodeCount()))
                continue;

            if (map[i].first.size() == 0) {
                undefG2 += WriteUndefFromVector(g2, map[i].second);
            }

            if (map[i].second.size() == 0) {
                undefG1 += WriteUndefFromVector(g1, map[i].first);
            }
        }

        if (undefG1.size() > 0)
            undefG1.resize(undefG1.size() - 2);
        if (undefG2.size() > 0)
            undefG2.resize(undefG2.size() - 2);

        undefined += "Circuit1:\n" + undefG1 + "\n";
        undefined += "Circuit2:\n" + undefG2 + "\n\n";

        return undefined;
    }

    std::string Statistics::WriteUndefFromVector(const GIS_Data::KoenigGraph& g, const std::vector<int>& vec) {

        std::string undefined;

        for (int j = 0; j < vec.size(); ++j) {

            std::vector<int> elems1 = g.getBlocks()[vec[j]].getInnerBlocks();
            for (size_t j = 0; j < elems1.size(); ++j)
                undefined += std::to_string(elems1[j]) + ", ";

            /*if (vec[j] >= g.getNodeCount())
                undefined += g.getNetName()[vec[j] - g.getNodeCount()] + ", ";
            else
                undefined += g.getBlocks()[vec[j]].getType() + std::to_string(vec[j]) + ", ";*/
        }

        return undefined;
    }
}
