#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define endl "\n"

inline int remap(char c) {
    return c >= '0' && c <= '9' ? (int)(c - '0') : (int)(c - 'a') + 10;
}

struct Trie {
    Trie *next[16] = {};

    Trie *step(int c) {
        if (!next[c]) next[c] = new Trie();
        return next[c];
    }

    int cnt() {
        int res = 1;
        for (Trie *c : next) if (c) res += c->cnt();
        return res;
    }
};

void dfs(vector<int> h, vector<vector<int>> &adj, Trie *t, int curr, int prev) {
    t = t->step(h[curr]);
    for (int next : adj[curr]) {
        if (next == prev) continue;
        dfs(h, adj, t, next, curr);
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cout << fixed << setprecision(12);

    int n; cin >> n;
    string a; cin >> a;
    vector<int> h(n); for (int i = 0; i < n; ++i) h[i] = remap(a[i]);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n-1; ++i) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // trie from ever node as root
    Trie *rt = new Trie();
    for (int r = 0; r < n; ++r) {
        dfs(h, adj, rt, r, -1);
    }
    cout << rt->cnt()-1 << endl;

    return 0;
}
