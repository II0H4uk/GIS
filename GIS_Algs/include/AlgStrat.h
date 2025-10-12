#pragma once

#include <KoenigGraph.h>
#include <Config.h>
#include <vector>

namespace GIS_Algs {

	class AlgStrat {
	public:
		virtual ~AlgStrat() = default;
		virtual std::vector<std::pair<std::vector<int>, std::vector<int>>> Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, const GIS_Data::Config& config) = 0;
	};
}
