#include "pch.h"
#include "Element.h"

namespace GIS_Data {

    GIS_Data::Element::Element(const std::string& type, int pinCount, const std::vector<int>& connectedNets, const std::vector<int>& size) :
        type(type), pinCount(pinCount), connectedNets(connectedNets), size(size) {}

    void Element::CalcAdjLevels(const std::vector<std::vector<int>>& adjList) {

    }

    void Element::CalcNeighDeg(const std::vector<Element>& elements) {

    }

    const std::string Element::GetType() const {
        return type;
    }

    const int Element::GetConCount() const {
        return pinCount;
    }

    const std::vector<int>& Element::GetconNets() const {
        return connectedNets;
    }

    const std::vector<int>& Element::GetSize() const {
        return size;
    }
}
