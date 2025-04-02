#include "pch.h"
#include "FileWriter.h"

namespace GIS_Parser {

    void FileWriter::WriteStringToFile(const string& str, const string& filePath)
    {
        try {
            ofstream outfile(filePath);

            if (!outfile.is_open()) {
                throw ios_base::failure("File opening error");
            }

            outfile << str << endl;
            outfile.close();
        }
        catch (const ios_base::failure& e) {
            cerr << "Error when writing to a file: " << e.what() << endl;
        }
    }
}