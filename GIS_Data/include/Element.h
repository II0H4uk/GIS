#pragma once

#include <string>
#include <vector>

namespace GIS_Data {
    class Element {
    private:
        char type;
        std::vector<int> nets;
        std::vector<double> size;
        int pinCount;

        std::vector<int> neighDeg;
        int forwardAdjLevel;
        int backwardAdjLevel;
    public:
        Element(const std::string& type, const std::vector<int>& nets, const std::vector<double>& size, const std::vector<int>& neighDeg, const int forwardAdjLevel, const int backwardAdjLevel);

        const char GetType() const;
        const std::vector<int>& GetNets() const;
        const std::vector<double>& GetSize() const;
        const int GetPinCount() const;

        const std::vector<int>& GetNeighDeg() const;
        const int GetForwLv() const;
        const int GetBackwLv() const;
    };
}
