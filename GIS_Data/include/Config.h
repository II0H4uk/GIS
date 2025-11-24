#pragma once

#include <string>
#include <unordered_map>

namespace GIS_Data {

    class Config {
    private:
        //CircuitsName
        std::string circName1_;
        std::string circName2_;

        //[ProgramSettings]
        std::string inputPath1_;
        std::string inputPath2_;
        std::string outputPath_;
        std::string algorithm_;

        //[MaxMatching]
        int maxMatchIterations_;

        //[SignalAlg]
        int signalIterations_;
        std::string signalsType_;
        int quantScale_;

        //[Statistics]
        bool enableStat_;
        bool writeCircParams_;
        bool writeTime_;
        bool writeBijection_;
        bool writeOnlyElements_;
        bool writeUndefinedElements_;
        bool writeToConsole_;

        const std::string FindVal(const std::unordered_map<std::string, std::string>& config, const std::string& key) const;

        const std::string ParseStr(const std::unordered_map<std::string, std::string>& config, const std::string& str, std::string def) const;
        const int ParseInt(const std::unordered_map<std::string, std::string>& config, const std::string& str, int def) const;
        const double ParseDouble(const std::unordered_map<std::string, std::string>& config, const std::string& str, double def) const;
        const bool ParseBool(const std::unordered_map<std::string, std::string>& config, const std::string& str, bool def) const;

    public:
        Config(const std::unordered_map<std::string, std::string>& config);
        Config(const std::string& input1, const std::string& input2);

        const std::string& GetCircName1() const;
        const std::string& GetCircName2() const;

        const std::string& GetInput1() const;
        const std::string& GetInput2() const;
        const std::string& GetOutput() const;
        const std::string& GetAlgorithm() const;

        const int GetMaxMatchIterations() const;

        const int GetSignalIterations() const;
        const std::string& GetSignalsType() const;
        const int GetQuantScale() const;

        const bool GetEnableStat() const;
        const bool GetWriteCircParams() const;
        const bool GetWriteTime() const;
        const bool GetWriteBijection() const;
        const bool GetWriteOnlyElements() const;
        const bool GetWriteUndefinedElements() const;
        const bool GetWriteToConsole() const;
    };
}
