#include "pch.h"
#include "SubGraphIso.h"

namespace GIS_Algs {

    std::vector<int> SubGraphIso::Start(const GIS_Data::Graph& g1, const GIS_Data::Graph& g2) {

        auto simMat = GIS_Algs::SubGraphIso::CalcSimMat(g1, g2);
        auto approx = GIS_Algs::SubGraphIso::GreedyMatch(simMat);

        return approx;
    }

    std::pair<int, int> SubGraphIso::CalcVertTags(const std::vector<std::vector<int>>& G, int v) {
        int degree = G[v].size();
        int neighbor_sum = 0;
        for (int u : G[v]) {
            neighbor_sum += G[u].size();
        }
        return { degree, neighbor_sum };
    }

    std::vector<std::vector<double>> SubGraphIso::CalcSimMat(const GIS_Data::Graph& g1, const GIS_Data::Graph& g2) {

        std::vector<std::vector<double>> sim(g1.GetNodeCount(), std::vector<double>(g2.GetNodeCount()));

        for (int i = 0; i < g1.GetNodeCount(); ++i) {
            //auto [d1, s1] = CalcVertTags(g1.GetAdjList(), i);  //заменить на переменные в классе
            for (int j = 0; j < g2.GetNodeCount(); ++j) {
                //auto [d2, s2] = CalcVertTags(g2.GetAdjList(), j); //заменить на переменные в классе
                //double diff = sqrt(pow(d1 - d2, 2) + pow(s1 - s2, 2));
                //sim[i][j] = 1.0 / (1.0 + diff);
                sim[i][j] = CompareTags(g1.GetTag()[i], g2.GetTag()[j], g1.GetNeighDegLv());
            }
        }
        return sim;
    }

    double SubGraphIso::CompareTags(const std::vector<GIS_Data::TagType>& tags1, const std::vector<GIS_Data::TagType>& tags2, int n)
    {
        double sumSquares = 0.0;

        for (int i = 0; i < n; ++i) {
            if (std::holds_alternative<int>(tags1[i]) &&
                std::holds_alternative<int>(tags2[i])) {

                double diff = static_cast<double>(std::get<int>(tags1[i]) - std::get<int>(tags2[i]));
                sumSquares += diff * diff;
            }
        }

        return 1.0 / (1.0 + std::sqrt(sumSquares));
    }

    std::vector<int> SubGraphIso::GreedyMatch(const std::vector<std::vector<double>>& simMat, double error) {

        std::vector<bool> used(simMat[0].size(), false);
        std::vector<int> matching(simMat.size(), -1);

        for (int i = 0; i < simMat.size(); ++i) {

            double maxVal = -1;
            int maxId = -1;

            for (int j = 0; j < simMat[0].size(); ++j) {
                if (!used[j] && simMat[i][j] > maxVal) {
                    maxVal = simMat[i][j];
                    maxId = j;
                }
            }

            if (maxVal >= error) {
                matching[i] = maxId;
                used[maxId] = true;
            }
        }
        return matching;
    }
}
