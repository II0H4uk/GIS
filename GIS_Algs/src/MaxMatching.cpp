#include "pch.h"
#include "MaxMatching.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <chrono>

namespace GIS_Algs {
    std::vector<std::pair<int, int>> MaxMatching::Start(const GIS_Data::BipartGraph& bipartGraph, int n) {

        const auto& adjList = bipartGraph.GetAdjList();

        std::vector<std::pair<int, int>> bestMatching;
        int bestSize = 0;

        //��������� ��������� �����
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed);

        for (int iteration = 0; iteration < n; ++iteration) {
            std::vector<std::pair<int, int>> currentMatching;
            std::vector<bool> usedRight(adjList.size(), false); // ��� ������� �������������� ������ ������

            //�������� �� ���� ����� �������� � ��������� �������
            std::vector<int> leftVertices(adjList.size());
            for (int i = 0; i < leftVertices.size(); ++i) {
                leftVertices[i] = i;
            }
            std::shuffle(leftVertices.begin(), leftVertices.end(), gen);

            //���������� ���������� �������������
            for (int left : leftVertices) {
                //�������� ������ ������� ������ ������
                const auto& neighbors = adjList[left];

                //������������ ������� ��� ���������� ������
                std::vector<int> shuffledNeighbors = neighbors;
                std::shuffle(shuffledNeighbors.begin(), shuffledNeighbors.end(), gen);

                //���� ������ ��������� ������ �������
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
}