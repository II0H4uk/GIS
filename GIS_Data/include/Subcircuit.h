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
        Point someDefaultPoint; ///< Default point.
        std::vector<int> chainInt;  ///< Nets int.

        /// @brief Constructor by default.
        TopologyComponent() : id(""), typeComponent(""), lengthComponent(0), widthComponent(0), centerCoordinate(someDefaultPoint)
        {
        }
    };

    /// @brief Structure describing a single recognized sub-circuit from the spice format
    struct Subcircuit {
        /// @brief Default constructor.
        Subcircuit():name(""), pins(),components(),netsCount(0){}

        /// @brief Constructor accepting parameters.
        Subcircuit(std::string name, const std::vector<std::string>& pins, const std::vector<TopologyComponent>& components) :
            name(name), pins(pins), components(components), netsCount(0) {
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
        int netsCount; ///< Nets counter
    };
};
