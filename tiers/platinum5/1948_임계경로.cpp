/*
Platinum 5
1948 - 임계경로
meta: {"problemId": 1948, "titleKo": "임계경로", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "임계경로", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 4489, "level": 16, "votedUserCount": 257, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.0076000690460205, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "dag", "isMeta": false, "bojTagId": 213, "problemCount": 340, "displayNames": [{"language": "ko", "name": "방향 비순환 그래프", "short": "dag"}, {"language": "en", "name": "directed acyclic graph", "short": "dag"}, {"language": "ja", "name": "有向非巡回グラフ", "short": "有向非巡回グラフ"}], "aliases": []}, {"key": "topological_sorting", "isMeta": false, "bojTagId": 78, "problemCount": 255, "displayNames": [{"language": "ko", "name": "위상 정렬", "short": "위상 정렬"}, {"language": "en", "name": "topological sorting", "short": "topological sorting"}, {"language": "ja", "name": "トポロジカルソート", "short": "トポロジカルソート"}], "aliases": []}, {"key": "traceback", "isMeta": false, "bojTagId": 235, "problemCount": 216, "displayNames": [{"language": "ko", "name": "역추적", "short": "역추적"}, {"language": "en", "name": "traceback", "short": "traceback"}], "aliases": []}], "metadata": {}}
*/

#include <bits/stdc++.h>
 
using namespace std;
 
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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // acyclic
    // find the set of edges that are in a longest path
    // can do toposort and track longest distance to reach each vertex as well as which edges are on that
    // trivially, longest path must use longest distance to each vertex in it
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    vector<int> indeg(n);
    vector<int> maxDist(n, 0);
    vector<vector<int>> maxDistEdges(n); // incoming edges on any max dist path to this node
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        adj[a].emplace_back(b, c);
        ++indeg[b];
    }

    // toposort to find max dist paths
    int dest = 0;
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0) q.push(i);
    }
    for (int i = 0; i < n; ++i) {
        int curr = q.front();
        dest = curr;
        q.pop();
        for (auto [next, cost] : adj[curr]) {
            int dist = maxDist[curr] + cost;
            
            if (dist >= maxDist[next]) {
                if (dist > maxDist[next]) {
                    maxDist[next] = dist;
                    maxDistEdges[next].clear();
                }
                maxDistEdges[next].push_back(curr);
            }

            if (--indeg[next] == 0) q.push(next);
        }
    }

    // backwards traversal on each longest path
    int maxPathRoads = 0;
    vector<bool> visited(n);
    q.push(dest);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        maxPathRoads += (int)maxDistEdges[curr].size();
        for (int prev : maxDistEdges[curr]) {
            if (visited[prev]) continue;

            visited[prev] = true;
            q.push(prev);
        }
    }
    cout << maxDist[dest] << endl;
    cout << maxPathRoads << endl;
}
