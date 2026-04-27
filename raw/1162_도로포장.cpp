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
