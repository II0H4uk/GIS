#pragma once

#ifdef _WIN32
    #ifdef GISDATA_EXPORTS
        #define GISDATA_API __declspec(dllexport)
    #else
        #define GISDATA_API __declspec(dllimport)
    #endif
#else
    #define GISDATA_API
#endif

namespace GIS_Data {

    class GISDATA_API Element {
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

