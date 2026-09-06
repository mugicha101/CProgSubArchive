// 2024-11-17 21:52:14 
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
const ll MOD = 1000000007;
const ll INF = LLONG_MAX >> 2;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int n, m, k;
    cin >> n >> m >> k;

    int start = -1;

    unordered_map<ll, pair<ll, int>> visited;
    unordered_set<ll> dup;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (i+1 != k) dup.insert(x);
        else start = x;
    }

    vector<pair<char, ll>> ops(m);
    for (int i = 0; i < m; ++i) {
        cin >> ops[i].first >> ops[i].second;
    }

    queue<pair<ll, pair<ll, int>>> q;
    q.emplace(start, make_pair(-1, -1));
    visited[start] = make_pair(-1, -1);
    ll res = -1;
    while (!q.empty()) {
        auto [curr, parent] = q.front();
        // cout << curr << " " << parent.first << " " << parent.second << endl;
        q.pop();
        if (dup.count(curr) == 0) {
            res = curr;
            break;
        }

        for (int i = 0; i < m; ++i) {
            auto &[b, r] = ops[i];

            ll next = b == '-' ? curr - r : b == '*' ? curr * r : b == '+' ? curr + r : curr / r;
            if (next < 0 || visited.count(next)) continue;

            // cout << "op " << b << " " << r << " " << next << endl;

            pair<ll, int> parent = make_pair(curr, i);
            visited[next] = parent;
            q.emplace(next, parent);
        }
    }

    if (res == -1) {
        cout << -1 << endl;
        return 0;
    }

    // cout << res << endl;
    vector<int> chain;
    while (res != start) {
        chain.push_back(visited[res].second + 1);
        res = visited[res].first;
        // cout << res << endl;
    }
    // cout << "A" << endl;
    reverse(chain.begin(), chain.end());
    cout << chain.size() << endl;
    for (int x : chain) cout << x << endl;

    return 0;
}
