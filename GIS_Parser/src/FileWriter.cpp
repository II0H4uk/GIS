#include "pch.h"
#include "FileWriter.h"

namespace GIS_Parser {

    void FileWriter::WriteStringToFile(const std::string& str, const std::string& filePath)
    {
        try {
            std::ofstream outfile(filePath);

            if (!outfile.is_open()) {
                throw std::ios_base::failure("File opening error");
            }

            outfile << str << std::endl;
            outfile.close();
        }
        catch (const std::ios_base::failure& e) {
            std::cerr << "Error when writing to a file: " << e.what() << std::endl;
        }
    }
}