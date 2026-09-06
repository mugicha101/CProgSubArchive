// 2023-03-03 04:13:09 
#include <unordered_set>
#include <bits/stdc++.h>

typedef long long ll;
#define INPUT false

using namespace std;

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(0);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif

    // input
    int nodes, edges, profitCap;
    cin >> nodes >> edges >> profitCap;
    vector<vector<pair<int,int>>> adjList(nodes);
    for (int i = 0; i < edges; ++i) {
        int src, dst, profit;
        cin >> src >> dst >> profit;
        adjList[src-1].emplace_back(dst-1, profit);
    }

    // dijkstras path
    vector<pair<int,int>> heap; // node, profit
    vector<int> maxProfit(nodes, INT_MIN);
    maxProfit[0] = 0;
    heap.emplace_back(0, 0);
    auto cmp = [](pair<int,int>& a, pair<int,int>& b) {
        return a.second < b.second;
    };
    while (!heap.empty()) {
        pop_heap(heap.begin(), heap.end(), cmp);
        int node = heap.back().first;
        int profit = heap.back().second;
        heap.pop_back();
        if (profit < maxProfit[node])
            continue;
        for (auto& nb : adjList[node]) {
            int newProfit = min(profitCap, profit + nb.second);
            if (maxProfit[nb.first] >= newProfit)
                continue;
            maxProfit[nb.first] = newProfit;
            heap.emplace_back(nb.first, newProfit);
            push_heap(heap.begin(), heap.end(), cmp);
        }
    }
    cout << maxProfit.back() << endl;
}
