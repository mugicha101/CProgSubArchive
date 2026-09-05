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
    vector<vector<pair<int,int>>> rev(n);
    while (m--) {
        int a, b, c; cin >> a >> b >> c;
        --a; --b;
        adj[a].emplace_back(b, c);
        rev[b].emplace_back(a, c);
    }

    vector<int> dist = sssp(adj, x);
    vector<int> revDist = sssp(rev, x);
    int res = 0;
    for (int i = 0; i < n; ++i) res = max(res, dist[i] + revDist[i]);
    cout << res << endl;
}
