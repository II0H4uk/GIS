#include "pch.h"
#include "Config.h"

namespace GIS_Data {

    Config::Config(const std::unordered_map<std::string, std::string>& config) :
        inputPath1_(ParseStr(config, "Input1", "")),
        inputPath2_(ParseStr(config, "Input2", "")),
        outputPath_(ParseStr(config, "Output", "")),
        iterations_(ParseInt(config, "Iterations", 0)),
        quantScale_(ParseInt(config, "QuantScale", 0)) { }

    const std::string Config::FindVal(const std::unordered_map<std::string, std::string>& config, const std::string& key) const {
        auto it = config.find(key);
        if (it == config.end())
            return "";
        return it->second;
    }

    const std::string Config::ParseStr(const std::unordered_map<std::string, std::string>& config, const std::string& key, std::string def) const {
        std::string val = FindVal(config, key);
        if (val == "")
            return def;
        return val;
    }

    const int Config::ParseInt(const std::unordered_map<std::string, std::string>& config, const std::string& key, int def) const {
        try {
            return std::stoi(FindVal(config, key));
        }
        catch (...) {
            return def;
        }
    }

    const double Config::ParseDouble(const std::unordered_map<std::string, std::string>& config, const std::string& key, double def) const {
        try {
            return std::stod(FindVal(config, key));
        }
        catch (...) {
            return def;
        }
    }

    const bool Config::ParseBool(const std::unordered_map<std::string, std::string>& config, const std::string& key, bool def) const {
        return (FindVal(config, key) == "true");
    }

    const std::string& Config::GetInput1() const {
        return inputPath1_;
    }

    const std::string& Config::GetInput2() const {
        return inputPath2_;
    }

    const std::string& Config::GetOutput() const {
        return outputPath_;
    }

    const int Config::GetIterations() const {
        return iterations_;
    }

    const int Config::GetQuantScale() const {
        return quantScale_;
    }
}
