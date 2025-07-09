#include "pch.h"
#include <SpiceParser.h>
#include <CircuitLayout.h>
#include <cctype>

Circuits::Utils::Subcircuit Circuits::Utils::SpiceParser::ParseSPICE(const std::string& fileName) {
    std::ifstream file(fileName);
    std::string line;
    Subcircuit circuit;
    std::vector<Subcircuit> subcircuits;

    if (!file.is_open()) {
        std::cerr << "SpiceParser: Unable to open file for extract data reduction." << std::endl;
        return circuit;
    }

    while (getline(file, line)) {

        // Delete comments and empty rows.
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        if (line.empty() || line[0] == '*') continue;
        if (line.substr(0, 7) == ".SUBCKT")
            subcircuits.push_back(Circuits::Utils::SpiceParser::ExtractSubcircuit(file, line));
    }

    file.close();

    return GIS_Parser::CircuitLayout::CreateMainCircuit(subcircuits);
}

//=================================================================================================
//returns the recognized sub-circuit described in the spice format
Circuits::Utils::Subcircuit Circuits::Utils::SpiceParser::ExtractSubcircuit(std::ifstream& file, std::string& currLine) {

    Subcircuit subcircuit(Circuits::Utils::SpiceParser::parseSubcircuitLine(currLine, file));
    std::string line;
    
    while (getline(file, line)) {
        // Delete comments and empty rows.
        line.erase(0, line.find_first_not_of(" \t\r\n"));

        if (line.empty() || line[0] == '*') continue;
        if (line == ".ENDS") break;

        // Parse components.
        try {
            TopologyComponent comp = Circuits::Utils::SpiceParser::parseComponent(line);
            subcircuit.components.push_back(comp);

        } catch (const std::exception& e) {
            std::cerr << "SpiceParser: Error parsing line: " << line << std::endl;
        }
    }
    
    return subcircuit;
}

//=================================================================================================
// Recognizes and writes a sub-circuit from a string starting with the SUBCKT directive
Circuits::Utils::Subcircuit Circuits::Utils::SpiceParser::parseSubcircuitLine(std::string& line, std::ifstream& file) {
    Subcircuit subcircuit;
    std::stringstream ss(line.c_str());
    std::string token;

    // Miss ".SUBCKT"
    getline(ss, token, ' ');


    // Extract name of sub-circuit.
    getline(ss, subcircuit.name, ' ');

    // Extract pins (pins).
    do {
        while (getline(ss, token, ' ')) {
            subcircuit.pins.push_back(token);
        }
        
        if (file.peek() == '+') {
            getline(file, line);
            ss.clear();
            ss.str(line.c_str());
        }
    } while (getline(ss, token, ' '));
    
    return subcircuit;
}

//=================================================================================================
// Recognizes one component on line.
Circuits::Utils::TopologyComponent Circuits::Utils::SpiceParser::parseComponent(const std::string& line)
{
    TopologyComponent parsedComponent;
    std::stringstream ss(line);
    ss >> parsedComponent.id;
    std::map<std::string, double> allParams;

    // Iterate over each token of the string, and select the chains with the element type.
    std::string item;
    while (ss >> item) {
        size_t eqPos = item.find('=');
        if (eqPos != std::string::npos) {
            std::string key;
            std::string valueStr;

            if (item.starts_with("$T="))
                for (int i = 0; i < 4; ++i)
                    (ss >> item);

            // Check dollar sign
            if (item[0] == '$') {
                key = item.substr(1, eqPos - 1); // Delete '$' sign
                valueStr = item.substr(eqPos + 1);
            } else {
                key = item.substr(0, eqPos);
                valueStr = item.substr(eqPos + 1);
            }
            char* endptr;
            double value;
            try {
                value = std::strtod(valueStr.c_str(), &endptr);
                if (*endptr != '\0') {
                    throw std::invalid_argument("Invalid value parametr: " + valueStr);
                }

                if (key == "l" || key == "w")
                    key = toupper(key[0]);

                allParams[key] = value;
            } catch (const std::invalid_argument& e) {
                std::cerr << "SpiceParser: Error parse component parametrs: " << e.what() << std::endl;
            }
        } else {
            parsedComponent.chain.push_back(item);
        }
    }

    // Extracting the geometric parameters by name
    parsedComponent.lengthComponent = allParams.count("L") ? allParams.at("L") : 0.0;
    parsedComponent.widthComponent = allParams.count("W")? allParams.at("W") : 0.0;
    parsedComponent.centerCoordinate.X = allParams.count("X")  ? allParams.at("X") : 0.0;
    parsedComponent.centerCoordinate.Y = allParams.count("Y")  ? allParams.at("Y") : 0.0;

    for (const auto& pair : allParams) {
        if ( pair.first != "L" && pair.first != "W"  && pair.first != "X"  && pair.first != "Y" ){
            parsedComponent.parametersComponent[pair.first]=pair.second;
        }
    }
    // The element type is what is left after the ID and pins. If there is no type and pins, set "unknown"
    if (!parsedComponent.chain.empty()) {
        //TO DO add a check of all available element types, in case the type is not specified in the presence of chains
        parsedComponent.typeComponent = parsedComponent.chain.back();
        parsedComponent.chain.pop_back();
    } else {
        parsedComponent.typeComponent = "unknown";
    }

    return parsedComponent;
};

//=================================================================================================
/*Example output file
* Netlisted on:  Oct 23 16:54:34 2024
************************************************************************
SUBCKT reduce8h b1 d1 g1 s1
*.PININFO b1:B d1:B g1:B s1:B
MM0 d1 g1 s1 b1 pmos_h W=1u L=350n M=8
.ENDS
*/
//creates a file with a reduced element
void Circuits::Utils::SpiceParser::CreateOutputFileReduction(const Subcircuit subckt,
                                                             const std::string& outputFileName) {
    // TO DO to discuss the conditions for the formation of the output file
    std::ofstream outputFile(outputFileName, std::ios::out | std::ios::trunc);

    std::time_t now = std::time(0);
    std::tm* localtm = std::localtime(&now);

    if (outputFile.is_open() && subckt.components.size()>0) {
        outputFile << "* Netlisted on: "<<std::put_time(localtm, "%m %d %H:%M:%S %Y")<< "\n"
                       "************************************************************************\n"
                       "SUBCKT "<<subckt.name<<" b1 d1 g1 s1\n"
                       << subckt.components[0].id <<" d1 g1 s1 b1 "<< subckt.components[0].typeComponent<<" W=1u L=350n M=8\n"
                       ".ENDS\n";
        outputFile.close();
    } else {
        std::cerr << "SpiceParser: Error when opening a file for recovery data or components is empty" << outputFileName << std::endl;
    }
};
