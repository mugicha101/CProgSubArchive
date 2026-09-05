/*
Platinum 5
1162 - Revamping Trails
meta: {"problemId": 1162, "titleKo": "도로포장", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "도로포장", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Revamping Trails", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 3486, "level": 16, "votedUserCount": 253, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.195899963378906, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "shortest_path", "isMeta": false, "bojTagId": 215, "problemCount": 990, "displayNames": [{"language": "ko", "name": "최단 경로", "short": "최단 경로"}, {"language": "en", "name": "shortest path", "short": "shortest path"}, {"language": "ja", "name": "最短経路", "short": "最短経路"}], "aliases": []}, {"key": "dijkstra", "isMeta": false, "bojTagId": 22, "problemCount": 725, "displayNames": [{"language": "ko", "name": "데이크스트라", "short": "데이크스트라"}, {"language": "en", "name": "dijkstra's", "short": "dijkstra's"}, {"language": "ja", "name": "ダイクストラ法", "short": "ダイクストラ法"}], "aliases": [{"alias": "다익"}, {"alias": "다익스트라"}, {"alias": "데이크스트라"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;

const int MOD = 1000000007;
 
typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
// #define endl "\n"

// extend a using b
void extendKnap(vector<ll> &a, vector<ll> &b) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; i + j < n; ++j) {
            a[i + j] = min(a[i + j], a[i] + b[j]);
        }
    }
}

int dfs(vector<vector<ll>> &knap, vector<ll> &cost, vector<vector<int>> &adj, int curr) {
    int subtreeSize = 1;
    for (int next : adj[curr]) {
        subtreeSize += dfs(knap, cost, adj, next);
        extendKnap(knap[curr], knap[next]);
    }
    knap[curr][subtreeSize] = min(knap[curr][subtreeSize], cost[curr]);
    return subtreeSize;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // dijkstra with extra dimension k for remaining highways
    int n, m, k; cin >> n >> m >> k;
    vector<vector<pair<int,ll>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int a, b; ll c; cin >> a >> b >> c; --a; --b;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }
    priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> pq;
    vector<vector<ll>> dist(k+1, vector<ll>(n, LLONG_MAX));
    auto check = [&](ll d, int kv, int pos) {
        if (dist[kv][pos] <= d) return;

        dist[kv][pos] = d;
        pq.emplace(d, kv, pos);
    };
    check(0, k, 0);
    while (!pq.empty()) {
        auto [d, kv, curr] = pq.top();
        pq.pop();
        if (d > dist[kv][curr]) continue;
        for (auto &[next, c] : adj[curr]) {
            check(d + c, kv, next);
            if (kv) check(d, kv - 1, next);
        }
    }
    ll best = LLONG_MAX;
    for (int kv = 0; kv <= k; ++kv) {
        best = min(best, dist[kv][n-1]);
    }
    cout << best << "\n";
}
