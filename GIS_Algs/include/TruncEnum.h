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

#include "Graph.h"
#include <vector>

namespace GIS_Algs {

	class GISALG_API TruncEnum {
	private:
		static bool CompareGraphs(const GIS_Data::Graph& g1, const GIS_Data::Graph& g2, std::vector<int>& mapping, std::vector<bool>& used, int depth = 0);
	public:
		static bool Start(const GIS_Data::Graph& g1, const GIS_Data::Graph& g2);
	};
	
}
