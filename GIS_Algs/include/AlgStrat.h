#pragma once

#include <Config.h>
#include <KoenigGraph.h>
#include <utility>
#include <vector>

namespace GIS_Algs {

	class AlgStrat {
	public:
		virtual ~AlgStrat() = default;
		virtual std::vector<std::pair<std::vector<int>, std::vector<int>>> Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, const GIS_Data::Config& config) = 0;
	};
}
