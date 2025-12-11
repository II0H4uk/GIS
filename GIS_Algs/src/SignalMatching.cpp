#include "pch.h"

#include <KoenigGraph.h>
#include <SignalMatching.h>
#include <thread>

namespace GIS_Algs {

    // Отрефакторено
    std::vector<std::pair<std::vector<int>, std::vector<int>>> SignalMatching::Start(const GIS_Data::KoenigGraph& g1, const GIS_Data::KoenigGraph& g2, const GIS_Data::Config& config) {

        std::vector<int> inputs1 = GetInputNets(g1);
        std::vector<int> inputs2 = GetInputNets(g2);

        std::vector<int> vddId;
        std::vector<int> gndId;
        /*findPowerNets(g1.getNetName(), "vdd", vddId, g1.getNodeCount());
        findPowerNets(g1.getNetName(), "gnd", gndId, g1.getNodeCount());*/

        //MatchInputs(g1, inputs1, g2, inputs2);

        std::vector<std::vector<int>> inputSignals = GenerateSignals(inputs1, config.GetSignalIterations(), vddId, gndId);

        std::vector<int> topo1 = GetTopoOrder(g1, inputs1);
        std::vector<int> topo2 = GetTopoOrder(g2, inputs2);

        std::vector<std::vector<int>> S1 = RunStochastic(g1, topo1, inputs1, config.GetSignalIterations(), inputSignals);
        std::vector<std::vector<int>> S2 = RunStochastic(g2, topo2, inputs2, config.GetSignalIterations(), inputSignals);

        std::vector<std::pair<std::vector<int>, std::vector<int>>> elemMap = MatchElems(g1, S1, g2, S2, config.GetQuantScale());

        return elemMap;
    }

    void SignalMatching::findPowerNets(const std::vector<std::string>& nets_name, const std::string& name, std::vector<int>& power_net, int node_count) {

        for (int i = 0; i < nets_name.size(); ++i) {

            std::string net_lower = nets_name[i];
            std::transform(net_lower.begin(), net_lower.end(), net_lower.begin(),
                [](unsigned char c) { return std::tolower(c); });

            if (net_lower.find(name) != std::string::npos)
                power_net.push_back(i + node_count);
        }
    }

    // Отрефакторено
    std::vector<int> SignalMatching::GetInputNets(const GIS_Data::KoenigGraph& g) {

        //if (g.getInputChains().size() != 0) //временное решение, так-то должно быть закомиченным
        //    return g.getInputChains();

        std::vector<int> inputs;
        for (int i = g.getNodeCount(); i < g.getNodeCount() + g.getHyperEdgeCount(); ++i)
            if (g.getAdjListT()[i].size() == 0)
                inputs.push_back(i);

        return inputs;
    }

    // Отрефакторено
    void SignalMatching::MatchInputs(
        const GIS_Data::KoenigGraph& g1, const std::vector<int>& in1,
        const GIS_Data::KoenigGraph& g2, std::vector<int>& in2
    ) {
        std::unordered_set<std::string> types;
        for (auto [type, elems] : g1.getBlocksType())
            types.insert(type);
        for (auto [type, elems] : g2.getBlocksType())
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

    // Отрефакторено
    std::vector<std::pair<std::vector<int>, std::vector<int>>> SignalMatching::MatchElems(
        const GIS_Data::KoenigGraph& g1, const std::vector<std::vector<int>>& S1,
        const GIS_Data::KoenigGraph& g2, const std::vector<std::vector<int>>& S2,
        int quantScale
    ) {
        std::vector<std::pair<int, int>> mapping;
        mapping.reserve(std::min(g1.getNodeCount(), g2.getNodeCount()));

        std::vector<std::pair<std::vector<int>, std::vector<int>>> clusters;

        for (auto& elems1 : g1.getBlocksType()) {
            auto elems2 = g2.getBlocksType().find(elems1.first);
            if (elems2 == g2.getBlocksType().end()) continue;

            std::unordered_map<std::string, std::vector<int>> typeQuant1, typeQuant2;
            typeQuant1.reserve(elems1.second.size()); typeQuant2.reserve(elems2->second.size());
            for (int el : elems1.second)
                typeQuant1[QuantKey(S1[el], quantScale)].push_back(el);
            for (int el : elems2->second)
                typeQuant2[QuantKey(S2[el], quantScale)].push_back(el);

            for (auto& q1 : typeQuant1) {
                auto q2 = typeQuant2.find(q1.first);
                if (q2 == typeQuant2.end()) {
                    clusters.push_back({ q1.second, std::vector<int>()});
                    continue;
                }

                clusters.push_back({q1.second, q2->second});
            }
            for (auto& q2 : typeQuant2) {
                auto q1 = typeQuant1.find(q2.first);
                if (q1 == typeQuant1.end())
                    clusters.push_back({ std::vector<int>(), q2.second});
            }
        }
        return clusters;
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

            // восстановление пути
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

    // Отрефакторено
    std::vector<std::vector<int>> SignalMatching::GenerateSignals(std::vector<int> inputs, int iterations, const std::vector<int>& vdd, const std::vector<int>& gnd) {
        std::mt19937 rng;
        std::uniform_int_distribution<> signals(0, 1);

        std::vector<std::vector<int>> inputSignals(iterations, std::vector<int>(inputs.size(), 0));
        for (int it = 0; it < iterations; ++it)
            for (int i = 0; i < inputSignals[it].size(); ++i)
                inputSignals[it][i] = signals(rng);

        /*for (int i = 0; i < iterations; ++i) {
            for (int j = 0; j < vdd.size(); ++j) {
                int vdd_i = std::find(std::begin(inputs), std::end(inputs), vdd[j]) - std::begin(inputs);
                inputSignals[i][vdd_i] = 1;
            }
            for (int j = 0; j < gnd.size(); ++j) {
                int gnd_i = std::find(std::begin(inputs), std::end(inputs), gnd[j]) - std::begin(inputs);
                inputSignals[i][gnd_i] = 0;
            }
        }*/
        return inputSignals;
    }

    // Отрефакторено
    std::vector<int> SignalMatching::GetTopoOrder(const GIS_Data::KoenigGraph& g, const std::vector<int>& inputs) {

        std::queue<int> q;
        for (int input : inputs)
            q.push(input);

        int skipInput = inputs.size();
        std::vector<int> order; order.reserve(g.getNodeCount() + g.getHyperEdgeCount() - inputs.size());
        std::vector<int> visDeg(g.getNodeCount() + g.getHyperEdgeCount(), 0);
        std::vector<bool> isTrigger(visDeg.size(), false);

        while (!q.empty()) {
            int node = q.front(); q.pop();
            if (--skipInput < 0 && !isTrigger[node])
                order.push_back(node);

            for (int neigh : g.getAdjList()[node]) {
                if (++visDeg[neigh] == g.getAdjListT()[neigh].size() && !isTrigger[neigh])
                    q.push(neigh);
                if (g.getAdjList()[node].size() < 1000 && visDeg[neigh] != g.getAdjListT()[neigh].size() && !isTrigger[neigh])
                    Process6TSRAM(order, visDeg, isTrigger, g, neigh);
            }
        }

        return order;
    }

    void SignalMatching::Process6TSRAM(std::vector<int>& order, std::vector<int>& visDeg, std::vector<bool>& isTrigger, const GIS_Data::KoenigGraph& g, int firstCh) {

        if (g.getAdjListT()[firstCh].size() != 3 || g.getAdjList()[firstCh].size() != 2)
            return;

        std::vector<int> transistors(4);
        transistors[0] = g.getAdjList()[firstCh][0];
        transistors[1] = g.getAdjList()[firstCh][1];
        if (g.getAdjList()[transistors[0]][0] != g.getAdjList()[transistors[1]][0])
            return;
        int secondCh = g.getAdjList()[transistors[0]][0];
        
        if (g.getAdjListT()[secondCh].size() != 3 || g.getAdjList()[secondCh].size() != 2)
            return;

        transistors[2] = g.getAdjList()[secondCh][0];
        transistors[3] = g.getAdjList()[secondCh][1];

        if (g.getAdjList()[transistors[2]][0] != firstCh || g.getAdjList()[transistors[3]][0] != firstCh)
            return;
        for (int i = 0; i < g.getAdjListT()[secondCh].size(); ++i) {
            if (g.getAdjListT()[secondCh][i] == transistors[0] || g.getAdjListT()[secondCh][i] == transistors[1])
                continue;
            order.push_back(g.getAdjListT()[secondCh][i]);
        }
        order.push_back(firstCh);
        order.push_back(secondCh);
        for (int transistor : transistors) {
            isTrigger[transistor] = true;
            order.push_back(transistor);
        }
        isTrigger[firstCh] = true;
        isTrigger[secondCh] = true;
    }

    // Отрефакторено
    std::vector<std::vector<int>> SignalMatching::RunStochastic(const GIS_Data::KoenigGraph& g, const std::vector<int>& topoOrder, const std::vector<int>& inputNetsG, int iterations, std::vector<std::vector<int>>& inputBits) {
        std::vector<std::vector<int>> values(g.getNodeCount() + g.getHyperEdgeCount());
        for (int i = 0; i < values.size(); ++i)
            values[i].reserve(iterations);

        for (int i = 0; i < iterations; ++i) {
            std::vector<int> buf = SimulateOnce(g, topoOrder, inputNetsG, inputBits[i]);

            for (int j = 0; j < values.size(); ++j)
                values[j].push_back(buf[j]);
        }
        return values;
    }

    // Отрефакторено
    std::vector<int> SignalMatching::GetInputSign(const GIS_Data::KoenigGraph& g, const std::unordered_set<std::string>& allTypes, int inputNet, int maxDepth) {

        std::vector<int> elemsSign;
        elemsSign.push_back(g.getAdjList()[inputNet].size());

        std::vector<int> elemDepth(maxDepth + 1, 0);
        std::vector<int> netDepth(maxDepth + 1, 0);
        std::unordered_map<std::string, int> types; types.reserve(allTypes.size());
        for (std::string type : allTypes) {
            types[type] = 0;
        }

        std::queue<std::pair<int, int>> q;
        std::vector<bool> vis(g.getNodeCount() + g.getHyperEdgeCount(), 0);
        q.push({ inputNet, 0 });
        vis[inputNet] = true;

        while (!q.empty()) {
            auto [node, depth] = q.front(); q.pop();
            if (depth > maxDepth)
                continue;

            if (node < g.getNodeCount()) {
                ++elemDepth[depth];
                types[g.getBlocks()[node].getType()]++;
            }
            else {
                ++netDepth[depth];
                types["N"]++;
            }

            for (int v : g.getAdjList()[node]) {
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

    // Отрефакторено
    double SignalMatching::L2(const std::vector<int>& a, const std::vector<int>& b) {
        double s = 0.0;
        for (int i = 0; i < a.size(); ++i)
            s += (a[i] - b[i]) * (a[i] - b[i]);
        return std::sqrt(s);
    }

    // Отрефакторено
    std::vector<int> SignalMatching::SimulateOnce(
        const GIS_Data::KoenigGraph& g,
        const std::vector<int>& topoOrder,
        const std::vector<int>& inputNets,
        const std::vector<int>& inputBits
    ) {
        std::vector<int> value(g.getNodeCount() + g.getHyperEdgeCount(), -1);

        for (int i = 0; i < inputNets.size(); ++i)
            value[inputNets[i]] = inputBits[i];

        for (int e : topoOrder) {

            if (e < g.getNodeCount()) {
                std::vector<int> prev_vals(g.getAdjListT()[e].size());
                for (int i = 0; i < g.getAdjListT()[e].size(); ++i)
                    prev_vals[i] = value[g.getAdjListT()[e][i]];
                value[e] = g.getBlocks()[e].execute(prev_vals)[0];
            }
            else
            {
                int max_val = -1;
                for (int edge : g.getAdjListT()[e])
                    if (value[edge] > max_val) max_val = value[edge];
                value[e] = max_val;
            }
        }

        return value;
    }

    // Отрефакторено
    std::string SignalMatching::QuantKey(const std::vector<int>& sig, int scale) {
        std::string key;
        key.reserve(sig.size() * std::log10(scale) + sig.size() - 1);

        for (int i = 0; i < sig.size(); ++i) {
            if (i) key += '#';
            key += std::to_string(std::llround(sig[i] * scale));
        }

        return key;
    }
}
