#include "pch.h"
#include "ConfigParser.h"

namespace GIS_Parser {

    const GIS_Data::Config Config::Parse(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("Bad config file: " + filePath);

        std::unordered_map<std::string, std::string> config;

        std::string line;

        while (std::getline(file, line)) {
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if (line.empty() || line[0] == '[')
                continue;

            size_t pos = line.find("=");
            if (pos == std::string::npos)
                continue;

            config[line.substr(0, pos)] = line.substr(pos + 1);
        }

        file.close();

        return GIS_Data::Config(config);
    }
}

