#pragma once

// Standard library includes

#include <Subcircuit.h>

/// \namespace Algo
/// \brief This namespace contains utility classes and algorithms useful for other algorithms.
namespace Circuits::Utils {
    /// \class SpiceParser
    /// \brief A Spice Parser class for parse SPICE-files and extract data to struct and create output file.
    class SpiceParser {
    public:
        /// <summary>
        /// SPICE format parser
        /// </summary>
        /// <param name="fileName">path to SPICE format file</param>
        /// <returns>Circuit</returns>
        Subcircuit ParseSPICE(const std::string& fileName);
        /// @brief creates a file with a reduced element
        /// @param outputFileName the name of the file for the output file of the reduction in the spice format (.sp, .net)
        void CreateOutputFileReduction(const Subcircuit subckt, const std::string& outputFileName);

    private:
        /// @brief pulls out a subcircuit from the file
        /// @param fileName the name of the file that stores information for reduction in the spice format (.sp, .net)
        /// @return the recognized subcircuit described in the spice format(directive .SUBCKT)
        Subcircuit ExtractSubcircuit(std::ifstream& file, std::string& currLine);
        /// @brief recognizes one component on line
        /// @param line string for parse
        /// @return one component topology
        TopologyComponent parseComponent(const std::string& line);
        /// @brief recognized subcircuit from a string starting with the SUBCKT directive
        /// @param line string for parse
        /// @return subcircuit
        Subcircuit parseSubcircuitLine(std::string& line, std::ifstream& file);
    };
};
