/*
Gold 2
35357 - GUID Generator
meta: {"problemId": 35357, "titleKo": "GUID Generator", "titles": [{"language": "en", "languageDisplayName": "en", "title": "GUID Generator", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 11, "level": 14, "votedUserCount": 2, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.6363999843597412, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "trees", "isMeta": false, "bojTagId": 120, "problemCount": 1920, "displayNames": [{"language": "ko", "name": "트리", "short": "트리"}, {"language": "en", "name": "tree", "short": "tree"}, {"language": "ja", "name": "木", "short": "木"}], "aliases": [{"alias": "trees"}]}, {"key": "hashing", "isMeta": false, "bojTagId": 8, "problemCount": 208, "displayNames": [{"language": "ko", "name": "해싱", "short": "해싱"}, {"language": "en", "name": "hashing", "short": "hash"}, {"language": "ja", "name": "ハッシュ化", "short": "ハッシュ"}], "aliases": []}, {"key": "trie", "isMeta": false, "bojTagId": 79, "problemCount": 166, "displayNames": [{"language": "ko", "name": "트라이", "short": "트라이"}, {"language": "en", "name": "trie", "short": "trie"}, {"language": "ja", "name": "トライ木", "short": "トライ"}], "aliases": []}], "metadata": {}}
*/

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
