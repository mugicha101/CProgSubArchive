/*
Gold 4
1753 - 최단경로
meta: {"problemId": 1753, "titleKo": "최단경로", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "최단경로", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 44579, "level": 12, "votedUserCount": 346, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.6147000789642334, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "shortest_path", "isMeta": false, "bojTagId": 215, "problemCount": 990, "displayNames": [{"language": "ko", "name": "최단 경로", "short": "최단 경로"}, {"language": "en", "name": "shortest path", "short": "shortest path"}, {"language": "ja", "name": "最短経路", "short": "最短経路"}], "aliases": []}, {"key": "dijkstra", "isMeta": false, "bojTagId": 22, "problemCount": 725, "displayNames": [{"language": "ko", "name": "데이크스트라", "short": "데이크스트라"}, {"language": "en", "name": "dijkstra's", "short": "dijkstra's"}, {"language": "ja", "name": "ダイクストラ法", "short": "ダイクストラ法"}], "aliases": [{"alias": "다익"}, {"alias": "다익스트라"}, {"alias": "데이크스트라"}]}], "metadata": {}}
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

vector<int> sssp(vector<vector<pair<int,int>>> &adj, int src) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> minDist(adj.size(), INT_MAX);
    minDist[src] = 0;
    pq.emplace(0, src);
    while (!pq.empty()) {
        auto [currDist, curr] = pq.top();
        pq.pop();
        if (currDist > minDist[curr]) continue;

        for (auto [next, w] : adj[curr]) {
            int nextDist = currDist + w;
            if (nextDist >= minDist[next]) continue;

            minDist[next] = nextDist;
            pq.emplace(nextDist, next);
        }
    }
    return minDist;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, m, x; cin >> n >> m >> x;
    --x;
    vector<vector<pair<int,int>>> adj(n);
    while (m--) {
        int a, b, c; cin >> a >> b >> c;
        --a; --b;
        adj[a].emplace_back(b, c);
    }

    vector<int> dist = sssp(adj, x);
    for (int d : dist) cout << (d == INT_MAX ? "INF" : to_string(d)) << "\n";
}
