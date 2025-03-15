#include "pch.h"
#include "ConfigParser.h"

namespace GIS_Parser {

    GIS_Data::Config Config::Parse(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("Bad config file: " + filePath);

        std::string line;

        std::string input;
        std::string output;

        while (std::getline(file, line)) {
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if (line.empty() || line[0] == '[')
                continue;

            size_t pos = line.find("=");
            if (pos == std::string::npos)
                continue;

            std::string key = line.substr(0, pos);
            std::string val = line.substr(pos + 1);

            if (key == "Input")
                input = val;
            else if (key == "Output")
                output = val;
        }

        file.close();

        return GIS_Data::Config(input, output);
    }
}

