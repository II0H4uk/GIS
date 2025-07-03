#pragma once

#include <string>

namespace GIS_Parser {

    class FileWriter {
    private:

    public:
        static void WriteStringToFile(const std::string& str, const std::string& filePath);
    };
}