#pragma once

#include "pch.h"
#include <SignalMatchEnhanced.h>

namespace GIS_Algs {
    std::vector<std::pair<std::vector<int>, std::vector<int>>> SignalMatchEnhanced::Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, const GIS_Data::Config& config) {

        // Вызов гибридного сопоставления входов
        std::vector<int> inputMatching = MatchInputChainsHybrid(g1, g2, 20, 10, 20);

        // Интерпретация результата
        auto inputs1 = g1.getInputChains();
        auto inputs2 = g2.getInputChains();

        /*inputs2[0] = 7;
        inputs2[0] = 4;
        inputs2[0] = 6;
        inputs2[0] = 5;*/

        for (int i = 0; i < inputMatching.size(); ++i) {
            int j = inputMatching[i];

            if (j >= 0) {
                std::cout
                    << "Input "
                    << inputs1[i]
                    << " (" << g1.getNetName()[inputs1[i]] << ")"
                    << "  -->  "
                    << inputs2[j]
                    << " (" << g2.getNetName()[inputs2[j]] << ")"
                    << std::endl;
            }
            else {
                std::cout
                    << "Input "
                    << inputs1[i]
                    << " (" << g1.getNetName()[inputs1[i]] << ")"
                    << "  -->  UNMATCHED"
                    << std::endl;
            }
        }

        return std::vector<std::pair<std::vector<int>, std::vector<int>>>();
    }

    uint64_t SignalMatchEnhanced::SimulateConeOnce(const GIS_Data::KoenigGraph& g, const std::vector<int>& topo, const std::vector<int>& cone, const std::vector<int>& inputs, std::mt19937& rng) {
        int N = g.getNodeCount() + g.getHyperEdgeCount();
        std::vector<int> value(N, 0);

        std::bernoulli_distribution bit(0.5);
        for (int in : inputs)
            value[in] = bit(rng);

        uint64_t h = 1469598103934665603ULL; // FNV-1a

        for (int v : topo) {
            if (v < g.getNodeCount()) {
                std::vector<int> args;
                args.reserve(g.getAdjListT()[v].size());
                for (int u : g.getAdjListT()[v])
                    args.push_back(value[u]);
                value[v] = g.getBlocks()[v].execute(g.getAdjListT()[v])[0];
            }
            else {
                int mx = 0;
                for (int u : g.getAdjListT()[v])
                    mx = std::max(mx, value[u]);
                value[v] = mx;
            }

            // если вершина входит в конус — учитываем
            if (std::binary_search(cone.begin(), cone.end(), v)) {
                h ^= (uint64_t)value[v];
                h *= 1099511628211ULL;
            }
        }
        return h;
    }

    SignalMatchEnhanced::InputSignature SignalMatchEnhanced::BuildInputSignature(const GIS_Data::KoenigGraph& g, int input, const std::vector<int>& topo, int rounds, int maxDepth, std::mt19937& rng) {
        InputSignature sig;

        auto cone = ComputeCone(g, input, maxDepth);
        std::sort(cone.begin(), cone.end());

        sig.stats.influence =
            double(cone.size()) /
            double(g.getNodeCount() + g.getHyperEdgeCount());

        int ones = 0;

        for (int r = 0; r < rounds; ++r) {
            uint64_t h = SimulateConeOnce(g, topo, cone, g.getInputChains(), rng);
            sig.hashes.push_back(h);
            ones += (h & 1);
        }

        double p = double(ones) / rounds;
        if (p > 0 && p < 1)
            sig.stats.entropy = -p * log2(p) - (1 - p) * log2(1 - p);
        else
            sig.stats.entropy = 0.0;

        // итоговый вес
        sig.stats.weight = sig.stats.entropy * std::exp(-3.0 * sig.stats.influence);

        return sig;
    }

    std::vector<int> SignalMatchEnhanced::MatchInputChainsHybrid(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, int rounds, int maxDepth, int outerRounds) {
        auto topo1 = topoOrder(g1, g1.getInputChains());
        auto topo2 = topoOrder(g2, g2.getInputChains());

        int n1 = g1.getInputChains().size();
        int n2 = g2.getInputChains().size();

        std::vector<std::vector<int>> votes(n1, std::vector<int>(n2, 0));

        for (int it = 0; it < outerRounds; ++it) {
            std::mt19937 rng(1234 + it);

            std::vector<InputSignature> S1, S2;

            for (int i = 0; i < n1; ++i)
                S1.push_back(BuildInputSignature(g1, g1.getInputChains()[i], topo1, rounds, maxDepth, rng));

            for (int j = 0; j < n2; ++j)
                S2.push_back(BuildInputSignature(g2, g2.getInputChains()[j], topo2, rounds, maxDepth, rng));

            for (int i = 0; i < n1; ++i) {
                double best = 0;
                int bestj = -1;

                for (int j = 0; j < n2; ++j) {
                    double s = CompareSignatures(S1[i], S2[j]);
                    if (s > best) {
                        best = s;
                        bestj = j;
                    }
                }

                if (bestj != -1)
                    votes[i][bestj]++;
            }
        }

        std::vector<int> match(n1, -1);
        for (int i = 0; i < n1; ++i) {
            int bestj = -1, bestv = 0;
            for (int j = 0; j < n2; ++j)
                if (votes[i][j] > bestv) {
                    bestv = votes[i][j];
                    bestj = j;
                }
            if (bestv > outerRounds / 2)
                match[i] = bestj;
        }
        return match;
    }

    double SignalMatchEnhanced::CompareSignatures(const InputSignature& a, const InputSignature& b) {
        int same = 0;
        int R = a.hashes.size();

        for (int i = 0; i < R; ++i)
            if (a.hashes[i] == b.hashes[i])
                same++;

        double sim = double(same) / R;
        return sim * a.stats.weight * b.stats.weight;
    }

    std::vector<int> SignalMatchEnhanced::ComputeCone(const GIS_Data::KoenigGraph& g, int input, int maxDepth) {
        int N = g.getNodeCount() + g.getHyperEdgeCount();

        std::vector<int> depth(N, -1);
        std::deque<int> q;

        depth[input] = 0;
        q.push_back(input);

        std::vector<int> cone;
        cone.reserve(64);

        while (!q.empty()) {
            int curr_node = q.front(); q.pop_front();
            cone.push_back(curr_node);

            if (depth[curr_node] == maxDepth)
                continue;

            for (int next_node : g.getAdjList()[curr_node]) {
                if (depth[next_node] == -1) {
                    depth[next_node] = depth[curr_node] + 1;
                    q.push_back(next_node);
                }
            }
        }
        return cone;
    }

    // Kahn algorithm
    std::vector<int> SignalMatchEnhanced::topoOrder(const GIS_Data::KoenigGraph& g, const std::vector<int>& inputs) {
        int N = g.getNodeCount() + g.getHyperEdgeCount();

        std::vector<int> indeg(N);
        for (int v = 0; v < N; ++v)
            indeg[v] = g.getAdjListT()[v].size();

        std::vector<char> isInput(N, 0);
        for (int in : inputs)
            isInput[in] = 1;

        std::deque<int> q;
        std::vector<int> order;
        order.reserve(N);

        // снимаем вклад входов
        for (int in : inputs) {
            for (int u : g.getAdjList()[in])
                if (--indeg[u] == 0 && !isInput[u])
                    q.push_back(u);
        }

        while (!q.empty()) {
            int v = q.front(); q.pop_front();
            order.push_back(v);

            for (int u : g.getAdjList()[v])
                if (--indeg[u] == 0 && !isInput[u])
                    q.push_back(u);
        }

        return order;
    }
}
