#include "pch.h"
#include <algorithm>
#include <BipartGraph.h>
#include <chrono>
#include <Config.h>
#include <KoenigGraph.h>
#include <MaxMatching.h>
#include <random>
#include <utility>
#include <vector>

namespace GIS_Algs {
    std::vector<std::pair<int, int>> MaxMatching::AlgStart(int n) const {

        const auto& adjList = bGraph_.GetAdjList();

        std::vector<std::pair<int, int>> bestMatching;
        int bestSize = 0;

        //Генератор случайных чисел
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed);

        for (int iteration = 0; iteration < n; ++iteration) {
            std::vector<std::pair<int, int>> currentMatching;
            std::vector<bool> usedRight(adjList.size(), false); // Для отметки использованных правых вершин

            //Проходим по всем левым вершинам в случайном порядке
            std::vector<int> leftVertices(adjList.size());
            for (int i = 0; i < leftVertices.size(); ++i) {
                leftVertices[i] = i;
            }
            std::shuffle(leftVertices.begin(), leftVertices.end(), gen);

            //Построение случайного паросочетания
            for (int left : leftVertices) {
                //Получаем список смежных правых вершин
                const auto& neighbors = adjList[left];

                //Перемешиваем соседей для случайного выбора
                std::vector<int> shuffledNeighbors = neighbors;
                std::shuffle(shuffledNeighbors.begin(), shuffledNeighbors.end(), gen);

                //Ищем первую свободную правую вершину
                for (int right : shuffledNeighbors) {
                    if (!usedRight[right]) {
                        currentMatching.emplace_back(left, right);
                        usedRight[right] = true;
                        break;
                    }
                }
            }

            if (currentMatching.size() > bestSize) {
                bestSize = currentMatching.size();
                bestMatching = std::move(currentMatching);
            }
        }

        return bestMatching;
    }

    MaxMatching::MaxMatching() : bGraph_{ GIS_Data::BipartGraph{} }, isInit(false) {}

    std::vector<std::pair<std::vector<int>, std::vector<int>>> MaxMatching::Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, const GIS_Data::Config& config) {

        if (!isInit) {
            SetBGraph(GIS_Data::BipartGraph(g1, g2));
            isInit = true;
        }

        std::vector<std::pair<int, int>> bufMap = AlgStart(config.GetMaxMatchIterations());

        std::vector<std::pair<std::vector<int>, std::vector<int>>> map;
        
        for (int i = 0; i < bufMap.size(); ++i) {
            map.push_back(std::pair<std::vector<int>, std::vector<int>>({bufMap[i].first}, {bufMap[i].second}));
        }

        return map;
    }

    void MaxMatching::SetBGraph(const GIS_Data::BipartGraph& bGraph) {
        bGraph_ = bGraph;
        isInit = true;
    }
}