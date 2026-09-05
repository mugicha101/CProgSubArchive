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

    // negative weight cycle (NWC) detection using BF
    // need to determine if starting node is on a NWC
    // add meta start node that reaches all nodes with dist 0, run BF from this new start node
    // NWC iff BF is updated on |V|th iteration (since BF detects NWC reachable from start node)
    int farms; cin >> farms;
    while (farms--) {
        int n, m, w; cin >> n >> m >> w;
        vector<array<int,3>> edges(m + w);
        edges.reserve(m * 2 + w);

        // input edges
        for (auto &e : edges) {
            cin >> e[0] >> e[1] >> e[2];
            --e[0]; --e[1];
        }
        
        // handle wormholes
        for (int i = m; i < (int)edges.size(); ++i) edges[i][2] = -edges[i][2];

        // handle bidirectional
        for (int i = 0; i < m; ++i) edges.push_back({edges[i][1], edges[i][0], edges[i][2]});

        vector<int> dist(n, 0);
        for (int i = 1; i < n; ++i) {
            for (auto &e : edges) {
                dist[e[1]] = min(dist[e[1]], dist[e[0]] + e[2]);
            }
        }
        bool nwc = false;
        for (auto &e : edges) {
            if (dist[e[1]] > dist[e[0]] + e[2]) {
                nwc = true;
                break;
            }
        }
        cout << (nwc ? "YES" : "NO") << "\n";
    }
}
