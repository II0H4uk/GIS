#include "pch.h"
#include "ValidateMatch.h"

namespace GIS_Core {
    void ValidateMatch::Start(GIS_Data::GraphPair& pair, std::vector<std::pair<int, int>>& matching) {
		std::vector<std::vector<int>> g1 = pair.GetGraph1().GetAdjList();
		std::vector<std::vector<int>> g2 = pair.GetGraph2().GetAdjList();
		auto it = std::begin(matching);
		while (it!=std::end(matching)){
			if(g1[(*it).first].size()==0||g2[(*it).second].size()==0){
				it=matching.erase(it);
			} else {
				++it;
			}
			
		}
    }
}
