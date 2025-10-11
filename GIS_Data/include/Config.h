#pragma once

#include <string>
#include <unordered_map>

namespace GIS_Data {

    class Config {
    private:
        std::string inputPath1_;
        std::string inputPath2_;
        std::string outputPath_;

        int iterations_;
        int quantScale_;

        const std::string FindVal(const std::unordered_map<std::string, std::string>& config, const std::string& key) const;

        const std::string ParseStr(const std::unordered_map<std::string, std::string>& config, const std::string& str, std::string def) const;
        const int ParseInt(const std::unordered_map<std::string, std::string>& config, const std::string& str, int def) const;
        const double ParseDouble(const std::unordered_map<std::string, std::string>& config, const std::string& str, double def) const;
        const bool ParseBool(const std::unordered_map<std::string, std::string>& config, const std::string& str, bool def) const;

    public:
        Config(const std::unordered_map<std::string, std::string>& config);

        const std::string& GetInput1() const;
        const std::string& GetInput2() const;
        const std::string& GetOutput() const;
        const int GetIterations() const;
        const int GetQuantScale() const;
    };
}
