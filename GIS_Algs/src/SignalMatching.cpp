#include "pch.h"

#include <KoenigGraph.h>
#include <SignalMatching.h>

namespace GIS_Algs {

    // �������������
    std::vector<std::pair<std::vector<int>, std::vector<int>>> SignalMatching::Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, int iterations, int quantScale) {

        std::vector<int> inputs1 = GetInputNets(g1);
        std::vector<int> inputs2 = GetInputNets(g2);

        MatchInputs(g1, inputs1, g2, inputs2);

        std::vector<std::vector<double>> inputSignals = GenerateSignals(inputs1.size(), iterations);

        std::vector<int> topo1 = GetTopoOrder(g1, inputs1);
        std::vector<int> topo2 = GetTopoOrder(g2, inputs2);

        std::vector<std::vector<double>> S1 = RunStochastic(g1, topo1, inputs1, iterations, inputSignals);
        std::vector<std::vector<double>> S2 = RunStochastic(g2, topo2, inputs2, iterations, inputSignals);

        std::vector<std::pair<std::vector<int>, std::vector<int>>> elemMap = MatchElems(g1, S1, g2, S2, quantScale);

        return elemMap;
    }

    // �������������
    std::vector<int> SignalMatching::GetInputNets(const GIS_Data::KoenigGraph& g) {

        if (g.GetInputChains().size() != 0)
            return g.GetInputChains();

        std::vector<int> inputs;
        for (int i = g.GetNodeCount(); i < g.GetNodeCount() + g.GetHyperEdgeCount(); ++i)
            if (g.GetAdjListT()[i].size() == 0)
                inputs.push_back(i);

        return inputs;
    }

    // �������������
    void SignalMatching::MatchInputs(
        const GIS_Data::KoenigGraph& g1, const std::vector<int>& in1,
        const GIS_Data::KoenigGraph& g2, std::vector<int>& in2
    ) {
        std::unordered_set<char> types;
        for (auto [type, elems] : g1.GetElemsType())
            types.insert(type);
        for (auto [type, elems] : g2.GetElemsType())
            types.insert(type);

        const int n1 = in1.size(), n2 = in2.size();
        std::vector<std::vector<int>> elemCount1; elemCount1.reserve(n1);
        std::vector<std::vector<int>> elemCount2; elemCount2.reserve(n2);
        for (int net : in1)
            elemCount1.push_back(GetInputSign(g1, types, net, 3));
        for (int net : in2)
            elemCount2.push_back(GetInputSign(g2, types, net, 3));

        std::vector<std::vector<double>> cost(std::max(n1, n2), std::vector<double>(std::max(n1, n2), 0.0));
        for (int i = 0; i < cost.size(); ++i) {
            for (int j = 0; j < cost[i].size(); ++j) {
                if (i < n1 && j < n2)
                    cost[i][j] = L2(elemCount1[i], elemCount2[j]);
                else
                    cost[i][j] = 1e8;
            }
        }

        std::vector<int> assign = HungarianAlg(cost);
        std::vector<int> buf(in2);
        for (int i = 0; i < buf.size(); ++i) {
            in2[i] = buf[assign[i]];
        }
    }

    // �������������
    std::vector<std::pair<std::vector<int>, std::vector<int>>> SignalMatching::MatchElems(
        const GIS_Data::KoenigGraph& g1, const std::vector<std::vector<double>>& S1,
        const GIS_Data::KoenigGraph& g2, const std::vector<std::vector<double>>& S2,
        int quantScale
    ) {
        std::vector<std::pair<int, int>> mapping;
        mapping.reserve(std::min(g1.GetNodeCount(), g2.GetNodeCount()));

        std::vector<std::pair<std::vector<int>, std::vector<int>>> clusters;

        std::vector<std::pair<int, int>> a;
        int single = 0;
        for (auto& elems1 : g1.GetElemsType()) {
            auto elems2 = g2.GetElemsType().find(elems1.first);
            if (elems2 == g2.GetElemsType().end()) continue;

            std::unordered_map<std::string, std::vector<int>> typeQuant1, typeQuant2;
            typeQuant1.reserve(elems1.second.size()); typeQuant2.reserve(elems2->second.size());
            for (int el : elems1.second)
                typeQuant1[QuantKey(S1[el], quantScale)].push_back(el);
            for (int el : elems2->second)
                typeQuant2[QuantKey(S2[el], quantScale)].push_back(el);

            for (auto& q1 : typeQuant1) {
                auto q2 = typeQuant2.find(q1.first);
                if (q2 == typeQuant2.end()) continue;

                clusters.push_back({q1.second, q2->second});
                /*if (q1.second.size() == 1 && q2->second.size() == 1)
                    single++;
                else
                    a.push_back({ q1.second.size(), q2->second.size() });

                int c = std::min(q1.second.size(), q2->second.size());
                for (int i = 0; i < c; ++i)
                    mapping.emplace_back(q1.second[i], q2->second[i]);*/
            }
        }
        return clusters;
    }

    std::pair<std::vector<std::pair<int, int>>, int> SignalMatching::MatchFromClusters(
    const std::vector<std::pair<std::vector<int>, std::vector<int>>>& clusters
    ) {
        std::vector<std::pair<int, int>> mapping;
        int reliableMatches = 0;

        // Сначала обрабатываем однозначные кластеры
        for (const auto& cluster : clusters) {
            const auto& elems1 = cluster.first;
            const auto& elems2 = cluster.second;

            if (elems1.size() == 1 && elems2.size() == 1) {
                // Однозначное сопоставление
                mapping.emplace_back(elems1[0], elems2[0]);
                reliableMatches++;
            }
        }

        // Затем обрабатываем остальные кластеры
        for (const auto& cluster : clusters) {
            const auto& elems1 = cluster.first;
            const auto& elems2 = cluster.second;

            if (!(elems1.size() == 1 && elems2.size() == 1)) {
                // Неоднозначное сопоставление - берем первые элементы
                int count = std::min(elems1.size(), elems2.size());
                for (int i = 0; i < count; ++i) {
                    mapping.emplace_back(elems1[i], elems2[i]);
                }
            }
        }

        return {mapping, reliableMatches};
    }

    std::vector<int> SignalMatching::HungarianAlg(const std::vector<std::vector<double>>& cost) {
        int nRows = cost.size();
        int nCols = cost[0].size();
        const double INF = std::numeric_limits<double>::infinity();

        std::vector<double> u(nRows + 1, 0.0), v(nCols + 1, 0.0);
        std::vector<int> p(nCols + 1, 0), way(nCols + 1, 0);

        for (int i = 1; i <= nRows; ++i) {
            p[0] = i;
            int j0 = 0;
            std::vector<double> minv(nCols + 1, INF);
            std::vector<bool> used(nCols + 1, false);

            do {
                used[j0] = true;
                int i0 = p[j0], j1 = 0;
                double delta = INF;

                for (int j = 1; j <= nCols; ++j) {
                    if (used[j]) continue;
                    double cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }

                for (int j = 0; j <= nCols; ++j) {
                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    }
                    else {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while (p[j0] != 0);

            // �������������� ����
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0 != 0);
        }

        std::vector<int> assignment(nRows, -1);
        for (int j = 1; j <= nCols; ++j)
            if (p[j] != 0)
                assignment[p[j] - 1] = j - 1;

        return assignment;
    }

    // �������������
    std::vector<std::vector<double>> SignalMatching::GenerateSignals(int inputsCount, int iterations) {
        std::mt19937 rng;
        std::uniform_real_distribution<> signals(0.0, 1.0);
        std::vector<std::vector<double>> inputSignals(iterations, std::vector<double>(inputsCount, 0));
        for (int it = 0; it < iterations; ++it)
            for (int i = 0; i < inputSignals[it].size(); ++i)
                inputSignals[it][i] = signals(rng);
        return inputSignals;
    }

    // �������������
    std::vector<int> SignalMatching::GetTopoOrder(const GIS_Data::KoenigGraph& g, const std::vector<int>& inputs) {

        std::queue<int> q;
        for (int input : inputs)
            q.push(input);

        int skipInput = inputs.size();
        std::vector<int> order; order.reserve(g.GetNodeCount() + g.GetHyperEdgeCount() - inputs.size());
        std::vector<int> visDeg(g.GetNodeCount() + g.GetHyperEdgeCount(), 0);

        while (!q.empty()) {
            int node = q.front(); q.pop();
            if (--skipInput < 0)
                order.push_back(node);

            for (int neigh : g.GetAdjList()[node]) {
                if (++visDeg[neigh] == g.GetAdjListT()[neigh].size())
                    q.push(neigh);
            }
        }

        return order;
    }

    // �������������
    std::vector<std::vector<double>> SignalMatching::RunStochastic(const GIS_Data::KoenigGraph& g, const std::vector<int>& topoOrder, const std::vector<int>& inputNetsG, int iterations, std::vector<std::vector<double>>& inputBits) {
        std::vector<std::vector<double>> values(g.GetNodeCount() + g.GetHyperEdgeCount());
        for (int i = 0; i < values.size(); ++i)
            values[i].reserve(iterations);

        for (int i = 0; i < iterations; ++i) {
            std::vector<double> buf = SimulateOnce(g, topoOrder, inputNetsG, inputBits[i]);

            for (int j = 0; j < values.size(); ++j)
                values[j].push_back(buf[j]);
        }
        return values;
    }

    // �������������
    std::vector<int> SignalMatching::GetInputSign(const GIS_Data::KoenigGraph& g, const std::unordered_set<char>& allTypes, int inputNet, int maxDepth) {

        std::vector<int> elemsSign;
        elemsSign.push_back(g.GetAdjList()[inputNet].size());

        std::vector<int> elemDepth(maxDepth + 1, 0);
        std::vector<int> netDepth(maxDepth + 1, 0);
        std::unordered_map<char, int> types; types.reserve(allTypes.size());
        for (char type : allTypes) {    // �������� �� ������ ����������� ��-�� ����������� ������� ����� ������ � ��� ��������� =(
            types.emplace(type, 0);
        }

        std::queue<std::pair<int, int>> q;
        std::vector<bool> vis(g.GetNodeCount() + g.GetHyperEdgeCount(), 0);
        q.push({ inputNet, 0 });
        vis[inputNet] = true;

        while (!q.empty()) {
            auto [node, depth] = q.front(); q.pop();
            if (depth > maxDepth)
                continue;

            if (node < g.GetNodeCount()) {
                ++elemDepth[depth];
                types[g.GetElements()[node].GetType()]++;
            }
            else {
                ++netDepth[depth];
                types['N']++;
            }

            for (int v : g.GetAdjList()[node]) {
                if (vis[v])
                    continue;

                vis[v] = true;
                q.push({ v, depth + 1 });
            }
        }

        for (int i = 1; i <= maxDepth; ++i)
            elemsSign.push_back(elemDepth[i]);
        for (int i = 1; i <= maxDepth; ++i)
            elemsSign.push_back(netDepth[i]);
        for (auto [type, count] : types) elemsSign.push_back(count);
        return elemsSign;
    }

    // �������������
    double SignalMatching::L2(const std::vector<int>& a, const std::vector<int>& b) {
        double s = 0.0;
        for (int i = 0; i < a.size(); ++i)
            s += (a[i] - b[i]) * (a[i] - b[i]);
        return std::sqrt(s);
    }

    // �������������
    std::vector<double> SignalMatching::SimulateOnce(
        const GIS_Data::KoenigGraph& g,
        const std::vector<int>& topoOrder,
        const std::vector<int>& inputNets,
        const std::vector<double>& inputBits
    ) {
        std::vector<double> value(g.GetNodeCount() + g.GetHyperEdgeCount(), 0.0);

        for (int i = 0; i < inputNets.size(); ++i)
            value[inputNets[i]] = inputBits[i];

        for (int e : topoOrder) {
            char elType = e < g.GetNodeCount() ? g.GetElements()[e].GetType() : 'N';
            switch (elType) {
            case 'M':
                if (value[g.GetAdjListT()[e][1]] > 0.6)
                    value[e] = value[g.GetAdjListT()[e][0]];
                break;
            case 'D':
                if (value[g.GetAdjListT()[e][0]] > 0.8)
                    value[e] = value[g.GetAdjListT()[e][0]];
                break;
            case 'R':
                if (value[g.GetAdjListT()[e][0]] > 0.1)
                    value[e] = value[g.GetAdjListT()[e][0]];
                break;
            case 'N':
                value[e] = value[g.GetAdjListT()[e][0]];
                break;
            default:
                if (value[g.GetAdjListT()[e][0]] > 0.5)
                    value[e] = value[g.GetAdjListT()[e][0]];
                break;
            }

            /*double sum = 0.0;
            for (int node : g.GetAdjListT()[e])
                sum += value[node];
            value[e] += sum / g.GetAdjListT()[e].size();*/
        }

        return value;
    }

    // �������������
    std::string SignalMatching::QuantKey(const std::vector<double>& sig, int scale) {
        std::string key;
        key.reserve(sig.size() * std::log10(scale) + sig.size() - 1);

        for (int i = 0; i < sig.size(); ++i) {
            if (i) key += '#';
            key += std::to_string(std::llround(sig[i] * scale));
        }

        return key;
    }
}
