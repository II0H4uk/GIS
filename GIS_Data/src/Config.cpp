#include "pch.h"
#include "Config.h"

namespace GIS_Data {

    Config::Config(const std::unordered_map<std::string, std::string>& config) :
        inputPath1_(ParseStr(config, "Input1", "")),
        inputPath2_(ParseStr(config, "Input2", "")),
        outputPath_(ParseStr(config, "Output", "")),
        algorithm_(ParseStr(config, "Algorithm", "")),

        maxMatchIterations_(ParseInt(config, "MaxMatchIterations", 0)),

        signalIterations_(ParseInt(config, "SignalIterations", 0)),
        quantScale_(ParseInt(config, "QuantScale", 0)),

        enableStat_(ParseBool(config, "EnableStat", false)),
        writeCircParams_(ParseBool(config, "WriteCircuitParams", false)),
        writeTime_(ParseBool(config, "WriteTime", false)),
        writeMapping_(ParseBool(config, "WriteMaping", false)),
        writeOnlyBijection_(ParseBool(config, "WriteOnlyBijection", false)) { }

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

    const std::string& Config::GetAlgorithm() const {
        return algorithm_;
    }

    const int Config::GetMaxMatchIterations() const {
        return maxMatchIterations_;
    }

    const int Config::GetSignalIterations() const {
        return signalIterations_;
    }

    const int Config::GetQuantScale() const {
        return quantScale_;
    }

    const bool Config::GetEnableStat() const {
        return enableStat_;
    }

    const bool Config::GetWriteCircParams() const {
        return writeCircParams_;
    }

    const bool Config::GetWriteTime() const {
        return writeTime_;
    }

    const bool Config::GetWriteMapping() const {
        return writeMapping_;
    }

    const bool Config::GetWriteOnlyBijection() const {
        return writeOnlyBijection_;
    }
}
