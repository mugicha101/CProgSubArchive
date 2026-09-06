// 2023-03-03 15:29:38 
#include <unordered_set>
#include <bits/stdc++.h>

typedef long long ll;
#define INPUT false

using namespace std;

double hlTime(double hl, double startSize, double targetSize) {
    // ts = ss * 2^(-t/hl)
    // 2^(t/hl) * ts = ss
    // 2^(t/hl) = ss/ts
    // t/hl = lg(ss/ts)
    // t = hl * lg(ss/ts)
    return hl * log2(startSize / targetSize);
}

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(0);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif

    // input
    int initSize, targetSize, bladeCount;
    cin >> initSize >> targetSize >> bladeCount;
    vector<pair<int,int>> blades; // max size, halflife
    blades.reserve(bladeCount+1);
    blades.emplace_back(targetSize, 0);
    pair<int,int> bestBlade = make_pair(initSize, INT_MAX);
    for (int i = 0; i < bladeCount; ++i) {
        int maxSize, hl;
        cin >> maxSize >> hl;
        if (maxSize <= targetSize)
            continue;
        if (maxSize >= initSize)
            bestBlade.second = min(bestBlade.second, hl);
        else
            blades.emplace_back(maxSize, hl);
    }
    if (bestBlade.second == INT_MAX) {
        cout << -1 << endl;
        return 0;
    }
    
    // greedy - pick fastest blade until new fastest exists and switch to that
    auto cmp = [&](pair<int,int>& b1, pair<int,int>& b2) {
        return b1.first < b2.first;
    };
    sort(blades.begin(), blades.end(), cmp);
    double time = 0;
    for (int i = blades.size()-1; i >= 0; --i) {
        if (blades[i].second < bestBlade.second) {
            time += hlTime(bestBlade.second, bestBlade.first, blades[i].first);
            bestBlade = blades[i];
        }
    }
    cout.precision(16);
    cout << time << endl;
}
