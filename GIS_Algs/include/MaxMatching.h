#pragma once

#include <AlgStrat.h>
#include <BipartGraph.h>
#include <Config.h>
#include <utility>
#include <vector>

namespace GIS_Algs {

    class MaxMatching : public GIS_Algs::AlgStrat {
    private:
        GIS_Data::BipartGraph bGraph_;
        bool isInit;

        std::vector<std::pair<int, int>> AlgStart(int n) const;
    public:
        MaxMatching();
        std::vector<std::pair<std::vector<int>, std::vector<int>>> Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, const GIS_Data::Config& config) override;
        void SetBGraph(const GIS_Data::BipartGraph& bGraph);
    };
}
