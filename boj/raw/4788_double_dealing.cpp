#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    // input
    while (true) {
        int n, k;
        cin >> n >> k;
        if (n == 0 && k == 0) break;

        // find constant mapping
        vector<int> mapping;
        mapping.reserve(n);
        vector<vector<int>> players(k);
        for (int card = 0; card < n; ++card)
            players[card % k].push_back(card);
        for (auto &p : players)
            for (int i = p.size()-1; i >= 0; --i)
                mapping.push_back(p[i]);

        // determine chains
        // lcm of chains is answer
        ll res = 1;
        vector<bool> visited(n);
        for (int i = 0; i < n; ++i) {
            if (visited[i]) continue;
            int chainLen = 0;
            int card = i;
            while (!visited[card]) {
                ++chainLen;
                visited[card] = true;
                card = mapping[card];
            }
            res = lcm(res, (ll)chainLen);
        }

        cout << res << "\n";
    }
}

