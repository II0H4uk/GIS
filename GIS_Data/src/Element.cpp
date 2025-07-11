#include "pch.h"
#include "Element.h"

namespace GIS_Data {

    GIS_Data::Element::Element(const std::string& type, const std::vector<int>& nets, const std::vector<double>& size, const std::vector<int>& neighDeg, const int forwardAdjLevel, const int backwardAdjLevel) :
        type(type[0]),
        pinCount(nets.size()),
        nets(nets),
        size(size),
        neighDeg(neighDeg),
        forwardAdjLevel(forwardAdjLevel),
        backwardAdjLevel(backwardAdjLevel) { }

    const char Element::GetType() const {
        return type;
    }

    const int Element::GetPinCount() const {
        return pinCount;
    }

    const std::vector<int>& Element::GetNets() const {
        return nets;
    }

    const std::vector<double>& Element::GetSize() const {
        return size;
    }

    const std::vector<int>& Element::GetNeighDeg() const {
        return neighDeg;
    }

    const int Element::GetForwLv() const {
        return forwardAdjLevel;
    }

    const int Element::GetBackwLv() const {
        return backwardAdjLevel;
    }
}
