#pragma once

#include "Graph.h"
#include <vector>

namespace GIS_Algs {

	class TruncEnum {
	private:
		static bool CompareGraphs(const GIS_Data::Graph& g1, const GIS_Data::Graph& g2, std::vector<int>& mapping, std::vector<bool>& used, int depth = 0);
		static bool TryToMatchNodes(std::vector<int>& mapping, int depth, int i, std::vector<bool>& used, const GIS_Data::Graph& g1, const GIS_Data::Graph& g2, bool& retFlag);
		static void CompareTags(const GIS_Data::Graph& g1, int depth, const GIS_Data::Graph& g2, int i, int& retFlag);
	public:
		static bool Start(const GIS_Data::Graph& g1, const GIS_Data::Graph& g2);
	};
	
}
