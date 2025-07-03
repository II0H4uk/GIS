#pragma once

#include "Config.h"
#include <string>

namespace GIS_Parser {

    class Config {
    private:

    public:
        static const GIS_Data::Config Parse(const std::string& filePath);
    };
}
