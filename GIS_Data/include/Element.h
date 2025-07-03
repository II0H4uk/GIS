#pragma once

#include <string>
#include <vector>

namespace GIS_Data {

    class Element {
    private:
        std::string type;
        int pinCount;
        std::vector<int> connectedNets;
        std::vector<int> size;

        std::vector<int> neighDeg;
        int forwardAdjLevel;
        int backwardAdjLevel;
    public:
        Element(const std::string& type, int pinCount, const std::vector<int>& connectedNets, const std::vector<int>& size);

        void CalcAdjLevels(const std::vector<std::vector<int>>& adjList);
        void CalcNeighDeg(const std::vector<Element>& elements);

        const std::string GetType() const;
        const int GetConCount() const;
        const std::vector<int>& GetconNets() const;
        const std::vector<int>& GetSize() const;
    };
}

