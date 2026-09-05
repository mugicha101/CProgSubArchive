/*
Gold 5
13549 - 숨바꼭질 3
meta: {"problemId": 13549, "titleKo": "숨바꼭질 3", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "숨바꼭질 3", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 28621, "level": 11, "votedUserCount": 277, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.020599842071533, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}, {"key": "shortest_path", "isMeta": false, "bojTagId": 215, "problemCount": 990, "displayNames": [{"language": "ko", "name": "최단 경로", "short": "최단 경로"}, {"language": "en", "name": "shortest path", "short": "shortest path"}, {"language": "ja", "name": "最短経路", "short": "最短経路"}], "aliases": []}, {"key": "dijkstra", "isMeta": false, "bojTagId": 22, "problemCount": 725, "displayNames": [{"language": "ko", "name": "데이크스트라", "short": "데이크스트라"}, {"language": "en", "name": "dijkstra's", "short": "dijkstra's"}, {"language": "ja", "name": "ダイクストラ法", "short": "ダイクストラ法"}], "aliases": [{"alias": "다익"}, {"alias": "다익스트라"}, {"alias": "데이크스트라"}]}, {"key": "0_1_bfs", "isMeta": false, "bojTagId": 176, "problemCount": 84, "displayNames": [{"language": "ko", "name": "0-1 너비 우선 탐색", "short": "0-1 너비 우선 탐색"}, {"language": "en", "name": "0-1 bfs", "short": "0-1 bfs"}, {"language": "ja", "name": "0-1 bfs", "short": "0-1 bfs"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
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
#define sz(x) ((int)x.size())

void dfs(vector<vector<int>> &adj, vector<int> &parent, int curr) {
    for (int next : adj[curr]) {
        if (next == parent[curr]) continue;

        parent[next] = curr;
        dfs(adj, parent, next);
    }
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, k; cin >> n >> k;
    
    if (n >= k) {
        cout << n-k << "\n";
        return 0;
    }

    vector<bool> visited(k * 2);
    queue<int> q;
    auto check = [&](int x) {
        if (x < 0 || x >= (int)visited.size() || visited[x]) return false;

        q.push(x);
        visited[x] = true;
        return true;
    };
    auto powCheck = [&](int x) {
        int p = x;
        while (check(p)) {
            p <<= 1;
        }
    };
    powCheck(n);
    int steps = 0;
    while (!visited[k]) {
        ++steps;
        for (int qi = (int)q.size(); qi > 0; --qi) {
            int x = q.front();
            q.pop();
            powCheck(x-1);
            powCheck(x+1);
        }
    }
    cout << steps << endl;
}
