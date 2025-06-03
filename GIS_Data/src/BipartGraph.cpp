#include "pch.h"
#include "BipartGraph.h"

namespace GIS_Data {

    std::vector<double> BipartGraph::TagToVector(const std::vector<TagType>& tag)
    {
        std::vector<double> result;
        for (const auto& t : tag) {
            if (std::holds_alternative<int>(t)) {
                result.push_back(static_cast<double>(std::get<int>(t)));
            }
            else if (std::holds_alternative<double>(t)) {
                result.push_back(std::get<double>(t));
            }
            else if (std::holds_alternative<std::vector<int>>(t)) {
                const auto& vec = std::get<std::vector<int>>(t);
                for (int val : vec) {
                    result.push_back(static_cast<double>(val));
                }
            }
            else if (std::holds_alternative<std::vector<double>>(t)) {
                const auto& vec = std::get<std::vector<double>>(t);
                result.insert(result.end(), vec.begin(), vec.end());
            }
        }
        return result;
    }

    double BipartGraph::EuclideanDistance(const std::vector<double>& vec1, const std::vector<double>& vec2)
    {
        if (vec1.empty() || vec2.empty() || vec1.size() != vec2.size()) {
            return std::numeric_limits<double>::max();
        }
        double sum = 0.0;
        for (size_t i = 0; i < vec1.size(); ++i) {
            double diff = vec1[i] - vec2[i];
            sum += diff * diff;
        }
        return std::sqrt(sum);
    }

    std::vector<int> BipartGraph::FindClosest(const std::vector<double>& target, const std::vector<std::vector<double>>& points, double threshold, size_t k)
    {
        std::priority_queue<std::pair<double, int>> heap;

        for (int i = 0; i < points.size(); ++i) {
            double dist = EuclideanDistance(target, points[i]);
            if (dist < threshold) {
                if (heap.size() < k || dist < heap.top().first) {
                    heap.push({ dist, i });
                    if (heap.size() > k) {
                        heap.pop();
                    }
                }
            }
        }

        std::vector<int> result;
        while (!heap.empty()) {
            result.push_back(heap.top().second);
            heap.pop();
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    BipartGraph::BipartGraph(std::vector<std::vector<TagType>> tags1, std::vector<std::vector<TagType>> tags2) {
        const size_t nodeCount = tags1.size();
        adjList.resize(nodeCount);

        std::vector<std::vector<double>> points1, points2;
        for (const auto& tag : tags1) {
            points1.push_back(TagToVector(tag));
        }
        for (const auto& tag : tags2) {
            points2.push_back(TagToVector(tag));
        }

        const double threshold = 1.0;
        const size_t maxEdges = 5;

        for (int i = 0; i < nodeCount; ++i) {
            if (points1[i].empty()) continue;

            auto closest = FindClosest(points1[i], points2, threshold, maxEdges);
            for (int j : closest) {
                adjList[i].push_back(j);
            }
        }
    }

    BipartGraph::BipartGraph(const std::vector<std::vector<int>>& adjacencyList)
        : adjList(adjacencyList) {
    }

    BipartGraph::BipartGraph(const std::vector<std::vector<int>>& adjacencyList)
        : adjList(adjacencyList) {
    }
}
