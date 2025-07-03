#pragma once

// Standard library includes
#include <cstddef>
#include <exception>
#include <map>
#include <stdexcept>
#include <unordered_map>
#include <vector>

/// \namespace Algo
/// \brief This namespace contains utility classes and algorithms useful for other algorithms.
namespace Circuits::Utils {
    struct Point {
        double X = 0.0;
        double Y = 0.0;
    };

    /// @brief structure describing a single component of the topology, described in the spice format
    struct TopologyComponent {
        std::string id; ///< Id of topology component.
        std::vector<std::string> chain; ///< Chain.
        std::string typeComponent; ///< Type of the component.
        double lengthComponent = 0.0; ///< Length of the component.
        double widthComponent = 0.0; ///< Width of the component.
        Point centerCoordinate; ///< Point of topology connection.
        std::map<std::string, double> parametersComponent; ///< Parameters component.
        const Point someDefaultPoint; ///< Default point.

        /// @brief Constructor by default.
        TopologyComponent() : id(""), typeComponent(""), lengthComponent(0), widthComponent(0), centerCoordinate(someDefaultPoint)
        {
        }
    };

    /// @brief Structure describing a single recognized sub-circuit from the spice format
    struct Subcircuit {
        /// @brief Default constructor.
        Subcircuit():name(""), pins(),components(){}

        /// @brief Constructor accepting parameters.
        Subcircuit(std::string name, const std::vector<std::string>& pins, const std::vector<TopologyComponent>& components) :
            name(name), pins(pins), components(components) {
            if (name.empty()) {
                throw std::invalid_argument("Subcircuit name cannot be empty.");
            }
            if(pins.size()==0){
                throw std::invalid_argument("Subcircuit pins cannot be empty.");
            }
        }

        std::string name; ///< Name of the sub-sub-circuit.
        std::vector<std::string> pins; ///< Pins.
        std::vector<TopologyComponent> components; ///< Components.
    };


    /// \class SpiceParser
    /// \brief A Spice Parser class for parse SPICE-files and extract data to struct and create output file.
    class SpiceParser{
        public:
          /// @brief pulls out a subcircuit from the file
          /// @param fileName the name of the file that stores information for reduction in the spice format (.sp, .net)
          /// @return the recognized subcircuit described in the spice format(directive .SUBCKT)
          Subcircuit ExtractSubcircuit(const std::string &fileName);
          /// @brief creates a file with a reduced element
          /// @param outputFileName the name of the file for the output file of the reduction in the spice format (.sp, .net)
          void CreateOutputFileReduction(const Subcircuit subckt, const std::string &outputFileName);

        private:
          /// @brief recognizes one component on line
          /// @param line string for parse
          /// @return one component topology
          TopologyComponent parseComponent(const std::string& line);
          /// @brief recognized subcircuit from a string starting with the SUBCKT directive
          /// @param line string for parse
          /// @return subcircuit
          Subcircuit parseSubcircuitLine(const std::string& line);
    };
};
