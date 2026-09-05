/*
Platinum 5
5719 - Almost Shortest Path
meta: {"problemId": 5719, "titleKo": "거의 최단 경로", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "거의 최단 경로", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Almost Shortest Path", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 4845, "level": 16, "votedUserCount": 396, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.881100177764893, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "shortest_path", "isMeta": false, "bojTagId": 215, "problemCount": 990, "displayNames": [{"language": "ko", "name": "최단 경로", "short": "최단 경로"}, {"language": "en", "name": "shortest path", "short": "shortest path"}, {"language": "ja", "name": "最短経路", "short": "最短経路"}], "aliases": []}, {"key": "dijkstra", "isMeta": false, "bojTagId": 22, "problemCount": 725, "displayNames": [{"language": "ko", "name": "데이크스트라", "short": "데이크스트라"}, {"language": "en", "name": "dijkstra's", "short": "dijkstra's"}, {"language": "ja", "name": "ダイクストラ法", "short": "ダイクストラ法"}], "aliases": [{"alias": "다익"}, {"alias": "다익스트라"}, {"alias": "데이크스트라"}]}, {"key": "traceback", "isMeta": false, "bojTagId": 235, "problemCount": 216, "displayNames": [{"language": "ko", "name": "역추적", "short": "역추적"}, {"language": "en", "name": "traceback", "short": "traceback"}], "aliases": []}], "metadata": {}}
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
    int minDist[500];

    while (true) {
        int n, m; cin >> n >> m;
        if (n == 0) break;

        int src, dst; cin >> src >> dst;
        vector<tuple<int,int,int>> edges(m);
        for (auto &[a, b, w] : edges) {
            cin >> a >> b >> w;
        }

        // bellman ford to find shortest path
        auto bf = [&minDist, n](vector<tuple<int,int,int>> &edges, int src) {
            for (int i = 0; i < n; ++i) minDist[i] = INT_MAX >> 1;
            minDist[src] = 0;
            for (int i = 1; i < n; ++i) {
                for (auto &[a, b, w] : edges) {
                    minDist[b] = min(minDist[b], minDist[a] + w);
                }
            }
        };
        bf(edges, src);
        // for (int i = 0; i < n; ++i) cout << minDist[i] << " ";
        // cout << endl;

        // bellman ford from dst using shortest path edges
        vector<tuple<int,int,int>> revSPEdges;
        vector<int> revSPEdgeIds;
        revSPEdges.reserve(edges.size());
        revSPEdgeIds.reserve(edges.size());
        for (int i = 0; i < (int)edges.size(); ++i) {
            auto &[a, b, w]  = edges[i];
            if (minDist[b] != minDist[a] + w) continue;
            
            revSPEdges.emplace_back(b, a, 0);
            revSPEdgeIds.push_back(i);
        }
        bf(revSPEdges, dst);
        // for (int i = 0; i < n; ++i) cout << minDist[i] << " ";
        // cout << endl;

        // augment shortest paths on reverse sp graph from original graph
        for (int i = 0; i < (int)revSPEdges.size(); ++i) {
            auto &[a, b, w]  = revSPEdges[i];
            if (minDist[a] == (INT_MAX >> 1)) continue;
            
            get<2>(edges[revSPEdgeIds[i]]) = INT_MAX >> 1;
        }

        // bellman ford again
        bf(edges, src);
        // for (int i = 0; i < n; ++i) cout << minDist[i] << " ";
        // cout << endl;
        cout << (minDist[dst] == (INT_MAX >> 1) ? -1 : minDist[dst]) << "\n";
    }
}
