/*
Platinum 5
11438 - LCA 2
meta: {"problemId": 11438, "titleKo": "LCA 2", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "LCA 2", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 8742, "level": 16, "votedUserCount": 381, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.9316000938415527, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "trees", "isMeta": false, "bojTagId": 120, "problemCount": 1920, "displayNames": [{"language": "ko", "name": "트리", "short": "트리"}, {"language": "en", "name": "tree", "short": "tree"}, {"language": "ja", "name": "木", "short": "木"}], "aliases": [{"alias": "trees"}]}, {"key": "lca", "isMeta": false, "bojTagId": 41, "problemCount": 224, "displayNames": [{"language": "ko", "name": "최소 공통 조상", "short": "최소 공통 조상"}, {"language": "en", "name": "lowest common ancestor", "short": "lca"}, {"language": "ja", "name": "最下位共通祖先", "short": "lca"}], "aliases": []}, {"key": "sparse_table", "isMeta": false, "bojTagId": 84, "problemCount": 220, "displayNames": [{"language": "ko", "name": "희소 배열", "short": "희소 배열"}, {"language": "en", "name": "sparse table", "short": "sparse table"}, {"language": "ja", "name": "sparse table", "short": "sparse table"}], "aliases": [{"alias": "스파스어레이"}, {"alias": "sparse table"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

#include <bits/stdc++.h>
using namespace std;

struct LCATree {
    vector<vector<int>> children;
    vector<int> parent;
    vector<int> depth;
    vector<int> lift;
    LCATree(vector<vector<int>> &adj, int root = 0) : children(adj.size()), parent(adj.size()), depth(adj.size()), lift(adj.size()) {
        vector<int> anc;
        lift[root] = root;
        build(adj, anc, root);
    }

    void build(vector<vector<int>> &adj, vector<int> &anc, int curr) {
        depth[curr] = (int)anc.size();
        anc.push_back(curr);
        int jump = anc[(int)anc.size() - ((depth[curr] + 1) & (-depth[curr] - 1))];
        for (int next : adj[curr]) {
            if (next == parent[curr]) continue;

            children[curr].push_back(next);
            parent[next] = curr;
            lift[next] = jump;
            build(adj, anc, next);
        }
        anc.pop_back();
    }

    int lca(int a, int b) {
        if (depth[a] > depth[b]) swap(a, b);
        while (depth[b] > depth[a]) {
            b = depth[lift[b]] >= depth[a] ? lift[b] : parent[b];
        }
        while (a != b) {
            bool skip = lift[a] != lift[b];
            a = skip ? lift[a] : parent[a];
            b = skip ? lift[b] : parent[b];
        }
        return a;
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    LCATree lcaTree(adj);
    int m; cin >> m;
    while (m--) {
        int a, b; cin >> a >> b; --a; --b;
        cout << lcaTree.lca(a, b) + 1 << "\n";
    }
}
