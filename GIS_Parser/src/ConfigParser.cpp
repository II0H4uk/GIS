#include "pch.h"
#include "ConfigParser.h"

namespace GIS_Parser {

    const GIS_Data::Config Config::Parse(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("Bad config file: " + filePath);

        std::string line;

        std::string input1;
        std::string input2;
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

            if (key == "Input1")
                input1 = val;
            else if (key == "Input2")
                input2 = val;
            else if (key == "Output")
                output = val;
        }

        file.close();

        return GIS_Data::Config(input1,input2, output);
    }
}

