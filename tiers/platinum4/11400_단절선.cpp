/*
Platinum 4
11400 - 단절선
meta: {"problemId": 11400, "titleKo": "단절선", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "단절선", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 2824, "level": 17, "votedUserCount": 201, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.399399995803833, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "dfs", "isMeta": false, "bojTagId": 127, "problemCount": 964, "displayNames": [{"language": "ko", "name": "깊이 우선 탐색", "short": "깊이 우선 탐색"}, {"language": "en", "name": "depth-first search", "short": "dfs"}, {"language": "ja", "name": "深さ優先探索", "short": "dfs"}], "aliases": [{"alias": "depth first"}, {"alias": "depthfirst"}]}, {"key": "articulation", "isMeta": false, "bojTagId": 4, "problemCount": 75, "displayNames": [{"language": "ko", "name": "단절점과 단절선", "short": "단절점과 단절선"}, {"language": "en", "name": "articulation points and bridges", "short": "articulation points and bridges"}, {"language": "ja", "name": "関節点と橋", "short": "関節点と橋"}], "aliases": [{"alias": "단절점"}, {"alias": "단절선"}, {"alias": "브리지"}, {"alias": "브릿지"}, {"alias": "bridge"}]}], "metadata": {}}
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

vector<int> disc;
vector<int> low;
vector<bool> artic;
vector<pair<int,int>> bridges;
int nextTime = 0;

int artic_dfs(vector<vector<int>> &adj, int curr, int parent) {
    int children = 0;
    disc[curr] = low[curr] = nextTime++;

    for (int next : adj[curr]) {
        if (next == parent) continue;

        if (disc[next] != -1) {
            low[curr] = min(low[curr], disc[next]);
            continue;
        }

        ++children;
        artic_dfs(adj, next, curr);
        if (disc[curr] <= low[next]) artic[curr] = true;
        if (disc[curr] < low[next]) bridges.emplace_back(min(curr, next), max(curr, next));
        low[curr] = min(low[curr], low[next]);
    }

    return children;
}

vector<int> findArticulationPoints(vector<vector<int>> &adj, bool bridgesOnly) {
    int n = adj.size();
    low = disc = vector<int>(n, -1);
    bridges.clear();
    artic = vector<bool>(n, false);

    for (int root = 0; root < n; ++root) {
        if (disc[root] != -1) continue;

        artic[root] = artic_dfs(adj, root, -1) > 1;
    }

    if (bridgesOnly) return {};
    vector<int> res;
    for (int i = 0; i < n; ++i) if (artic[i]) res.push_back(i);
    
    return res;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<pair<int,int>> edges;
    while (m--) {
        int a, b; cin >> a >> b; --a; --b;
        if (a > b) swap(a, b);
        edges.emplace_back(a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    findArticulationPoints(adj, true);
    cout << bridges.size() << "\n";
    sort(all(bridges));
    for (auto &[a, b] : bridges) {
        cout << a+1 << " " << b+1 << "\n";
    }
}
