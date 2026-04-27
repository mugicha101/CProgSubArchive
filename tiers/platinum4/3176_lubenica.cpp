/*
Platinum 4
3176 - lubenica
meta: {"problemId": 3176, "titleKo": "도로 네트워크", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "도로 네트워크", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "lubenica", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 4014, "level": 17, "votedUserCount": 277, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.541599988937378, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "trees", "isMeta": false, "bojTagId": 120, "problemCount": 1920, "displayNames": [{"language": "ko", "name": "트리", "short": "트리"}, {"language": "en", "name": "tree", "short": "tree"}, {"language": "ja", "name": "木", "short": "木"}], "aliases": [{"alias": "trees"}]}, {"key": "lca", "isMeta": false, "bojTagId": 41, "problemCount": 224, "displayNames": [{"language": "ko", "name": "최소 공통 조상", "short": "최소 공통 조상"}, {"language": "en", "name": "lowest common ancestor", "short": "lca"}, {"language": "ja", "name": "最下位共通祖先", "short": "lca"}], "aliases": []}, {"key": "sparse_table", "isMeta": false, "bojTagId": 84, "problemCount": 220, "displayNames": [{"language": "ko", "name": "희소 배열", "short": "희소 배열"}, {"language": "en", "name": "sparse table", "short": "sparse table"}, {"language": "ja", "name": "sparse table", "short": "sparse table"}], "aliases": [{"alias": "스파스어레이"}, {"alias": "sparse table"}]}], "metadata": {}}
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

#include <bits/stdc++.h>

using namespace std;

struct LCATree {
    vector<vector<int>> children;
    vector<pair<int,int>> parent; // target, edge
    vector<int> depth;
    vector<tuple<int,int,int>> lift; // target, min edge, max edge
    LCATree(vector<vector<pair<int,int>>> &adj, int root = 0) : children(adj.size()), parent(adj.size()), depth(adj.size()), lift(adj.size()) {
        vector<int> anc;
        vector<int> ancEdges;
        lift[root] = { root, 0, 0 };
        build(adj, anc, ancEdges, root);
    }

    void build(vector<vector<pair<int,int>>> &adj, vector<int> &anc, vector<int> &ancEdges, int curr) {
        depth[curr] = (int)anc.size();
        anc.push_back(curr);
        int jump = anc[(int)anc.size() - ((depth[curr] + 1) & (-depth[curr] - 1))];
        pair<int,int> jumpEdge = { INT_MAX, INT_MIN };
        int t = anc.size() - 1;
        while (anc[t] != jump) {
            jumpEdge.first = min(jumpEdge.first, ancEdges[t-1]);
            jumpEdge.second = max(jumpEdge.second, ancEdges[t-1]);
            --t;
        }
        ancEdges.emplace_back();
        for (auto [next, w] : adj[curr]) {
            if (next == parent[curr].first) continue;

            children[curr].push_back(next);
            parent[next] = { curr, w };
            ancEdges.back() = w;
            lift[next] = { jump, min(jumpEdge.first, w), max(jumpEdge.second, w) };
            build(adj, anc, ancEdges, next);
        }
        ancEdges.pop_back();
        anc.pop_back();
    }

    pair<int,int> edgeBounds(int a, int b) {
        if (depth[a] > depth[b]) swap(a, b);
        int minEdge = INT_MAX;
        int maxEdge = INT_MIN;
        while (depth[b] > depth[a]) {
            if (depth[get<0>(lift[b])] >= depth[a]) {
                // lift
                minEdge = min(minEdge, get<1>(lift[b]));
                maxEdge = max(maxEdge, get<2>(lift[b]));
                b = get<0>(lift[b]);
            } else {
                // no lift
                minEdge = min(minEdge, parent[b].second);
                maxEdge = max(maxEdge, parent[b].second);
                b = parent[b].first;
            }
        }
        while (a != b) {
            if (get<0>(lift[a]) != get<0>(lift[b])) {
                // lift
                minEdge = min({minEdge, get<1>(lift[a]), get<1>(lift[b])});
                maxEdge = max({maxEdge, get<2>(lift[a]), get<2>(lift[b])});
                a = get<0>(lift[a]);
                b = get<0>(lift[b]);
            } else {
                // no lift
                minEdge = min({minEdge, parent[a].second, parent[b].second});
                maxEdge = max({maxEdge, parent[a].second, parent[b].second});
                a = parent[a].first;
                b = parent[b].first;
            }
        }
        return { minEdge, maxEdge };
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<vector<pair<int,int>>> adj(n);
    for (int i = 1; i < n; ++i) {
        int a, b, c; cin >> a >> b >> c; --a; --b;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }
    LCATree lca(adj);

    int m; cin >> m;
    while (m--) {
        int a, b; cin >> a >> b; --a; --b;
        auto [ minEdge, maxEdge ] = lca.edgeBounds(a, b);
        cout << minEdge << " " << maxEdge << "\n";
    }
}
