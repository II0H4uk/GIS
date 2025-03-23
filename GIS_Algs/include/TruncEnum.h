#pragma once

#ifdef _WIN32
	#ifdef GISALGS_EXPORTS
		#define GISALG_API __declspec(dllexport)
	#else
		#define GISALG_API __declspec(dllimport)
	#endif
#else
	#define GISALG_API
#endif

#include "pch.h"
#include "Graph.h"

namespace GIS_Algs {

	class GISALG_API TruncEnum {
	private:

	public:
		static bool Start(const GIS_Data::Graph& graphF, const GIS_Data::Graph& graphS);
		static int FindStartNode(const std::vector<bool>& visitedNodes);
		static bool CheckVisitedNodes(const std::vector<bool>& visitedF, const std::vector<bool>& visitedS);
		static bool CompareGraphs(const GIS_Data::Graph& graphF, const GIS_Data::Graph& graphS, std::vector<bool>& visitedF, std::vector<bool>& visitedS,  const int& nodeF, const int& nodeS);
	};
}
