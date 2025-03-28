#include "pch.h"
#include "Generator.h"

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <numeric>

using namespace std;

namespace GIS_Generator {

    // Функция для генерации графов
    GIS_Data::GraphPair Generator::Generate(bool isIsomorphic) {
        //GIS_Data::GraphPair Generate(bool& isIsomorphic) {
        const int totalVertices = 5; // Количество вершин
        vector<vector<int>> adjList1(totalVertices);
        vector<vector<int>> adjList2(totalVertices);

        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<> dis(0, totalVertices - 1);

        if (isIsomorphic) {
            // Генерация первого графа
            for (int i = 0; i < totalVertices; ++i) {
                for (int j = i + 1; j < totalVertices; ++j) {
                    if (dis(gen) % 2) {
                        adjList1[i].push_back(j);
                        adjList1[j].push_back(i); // Без направленного графа
                    }
                }
            }

            // Создание второго графа как копии первого с перенумеровкой
            vector<int> permutation(totalVertices);
            iota(permutation.begin(), permutation.end(), 0); // Заполнение последовательностью от 0 до totalVertices - 1
            shuffle(permutation.begin(), permutation.end(), gen);

            for (int i = 0; i < totalVertices; ++i) {
                for (auto neighbor : adjList1[i]) {
                    adjList2[permutation[i]].push_back(permutation[neighbor]);
                }
            }
        }
        else {
            // Генерация двух разных графов
            for (int i = 0; i < totalVertices; ++i) {
                for (int j = i + 1; j < totalVertices; ++j) {
                    if (dis(gen) % 2) {
                        adjList1[i].push_back(j);
                        adjList1[j].push_back(i);
                    }
                }
            }

            for (int i = 0; i < totalVertices; ++i) {
                for (int j = i + 1; j < totalVertices; ++j) {
                    if (dis(gen) % 2 && (i != j)) {
                        adjList2[i].push_back(j);
                        adjList2[j].push_back(i);
                    }
                }
            }
        }

        GIS_Data::Graph g1(adjList1, totalVertices);
        GIS_Data::Graph g2(adjList2, totalVertices);

        //return GIS_Data::Graph(adjList2, totalVertices);

        return GIS_Data::GraphPair(g1, g2, true);
    }
}