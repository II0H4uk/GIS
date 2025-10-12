#pragma once

#include <string>
#include <unordered_map>

namespace GIS_Data {

    class Config {
    private:
        //[ProgramSettings]
        std::string inputPath1_;
        std::string inputPath2_;
        std::string outputPath_;
        std::string algorithm_;

        //[MaxMatching]
        int maxMatchIterations_;

        //[SignalAlg]
        int signalIterations_;
        int quantScale_;

        //[Statistics]
        bool enableStat_;
        bool writeCircParams_;
        bool writeTime_;
        bool writeMapping_;
        bool writeOnlyBijection_;

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
        const std::string& GetAlgorithm() const;

        const int GetMaxMatchIterations() const;

        const int GetSignalIterations() const;
        const int GetQuantScale() const;

        const bool GetEnableStat() const;
        const bool GetWriteCircParams() const;
        const bool GetWriteTime() const;
        const bool GetWriteMapping() const;
        const bool GetWriteOnlyBijection() const;
    };
}
