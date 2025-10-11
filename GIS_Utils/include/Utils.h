#pragma once

#include <string>
#include <vector>
#include <KoenigGraph.h>
#include <Subcircuit.h>

namespace GIS_Utils {

	class Utils {
	public:
		static std::string GetCircuitAdjList(const GIS_Data::KoenigGraph& koenG, const Circuits::Utils::Subcircuit& circuit);
		static int CountLevels(const std::vector<std::vector<int>>& adjList, const std::vector<int>& startVertices);
		static std::string ConvertGraphMapToCircuit(const std::vector<std::pair<std::vector<int>, std::vector<int>>>& map,
			const GIS_Data::KoenigGraph& koenG1, const GIS_Data::KoenigGraph& koenG2);
	};
}
