#include "pch.h"
#include "BipartGraph.h"
#include "MaxMatching.h"

TEST(MaxMatchTests, SimpleTest) {
    std::vector<std::vector<int>> adjList = {
            {0, 1},    // ������� 0 ����� ���� ��������� � 0 � 1 ������
            {1, 2},     // ������� 1 ����� ���� ��������� � 1 � 2 ������
            {2}         // ������� 2 ����� ���� ��������� ������ � 2 ������
    };

    GIS_Data::BipartGraph graph(adjList);
    auto matching = GIS_Algs::MaxMatching::Start(graph, 100);

    std::cout << "Test 1: Simple graph\n";
    std::cout << "Matching size: " << matching.size() << "\n";
    for (const auto& pair : matching) {
        std::cout << pair.first << " - " << pair.second << "\n";
    }

    assert(matching.size() == 3);
}

TEST(MaxMatchTests, PartialMatching) {
    std::vector<std::vector<int>> adjList = {
            {0},        // 0 - 0
            {0},        // 1 - 0
            {1}         // 2 - 1
    };

    GIS_Data::BipartGraph graph(adjList);
    auto matching = GIS_Algs::MaxMatching::Start(graph, 100);

    std::cout << "\nTest 2: Graph without perfect matching\n";
    std::cout << "Matching size: " << matching.size() << "\n";
    for (const auto& pair : matching) {
        std::cout << pair.first << " - " << pair.second << "\n";
    }

    assert(matching.size() == 2); // ������������ ���������
}

TEST(MaxMatchTests, ComplexTest) {
    std::vector<std::vector<int>> adjList = {
            {0, 1, 2},
            {1, 2, 3},
            {0, 3},
            {2, 4},
            {3, 4}
    };

    GIS_Data::BipartGraph graph(adjList);
    auto matching = GIS_Algs::MaxMatching::Start(graph, 1000);

    std::cout << "\nTest 3: Larger graph\n";
    std::cout << "Matching size: " << matching.size() << "\n";
    for (const auto& pair : matching) {
        std::cout << pair.first << " - " << pair.second << "\n";
    }

    assert(matching.size() >= 4); // ������ ����� ������� �������������
}
