#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv) {
    int c, n;
    cin >> c >> n;
    unordered_set<int> visited;
    vector<int> states;
    states.push_back(0);
    for (int i = 0; i < n; ++i) {
        int l;
        cin >> l;
        for (int i = states.size()-1; i >= 0; --i) {
            auto check = [&](int cd1, int cd2) {
                if (cd1 < cd2)
                    swap(cd1, cd2);
                int s = (cd1 << 16) | cd2;
                if (visited.count(s))
                    return;
                visited.insert(s);
                states.push_back(s);
            };
            if ((states[i] >> 16) + l <= c)
                check((states[i] >> 16) + l, states[i] & 0xffff);
            if ((states[i] & 0xffff) + l <= c)
                check((states[i] >> 16), (states[i] & 0xffff) + l);
        }
    }
    int best = 0;
    int bestSum = 0;
    int bestDiff = 0;
    for (auto& s : states) {
        int cd1 = s >> 16;
        int cd2 = s & 0xffff;
        int sum = cd1 + cd2;
        int diff = cd1 - cd2;
        if (sum < bestSum || (sum == bestSum && diff >= bestDiff))
            continue;
        best = s;
        bestSum = sum;
        bestDiff = diff;
    }
    cout << (best >> 16) << " " << (best & 0xffff) << "\n";
}
