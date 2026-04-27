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

ll dfs(ll &longestPath, vector<vector<pair<int,ll>>> &adj, int parent, int curr) {
    ll maxTwo[2] = {0, 0};
    for (auto [next, d] : adj[curr]) {
        if (next == parent) continue;

        ll dist = dfs(longestPath, adj, curr, next) + d;
        if (dist <= maxTwo[0]) continue;

        maxTwo[0] = dist;
        if (maxTwo[0] > maxTwo[1]) swap(maxTwo[0], maxTwo[1]);
    }
    longestPath = max(longestPath, maxTwo[0] + maxTwo[1]);
    return maxTwo[1];
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<vector<pair<int,ll>>> adj(n);
    while (n--) {
        int a; cin >> a; --a;
        int b;
        while (cin >> b, --b != -2) {
            ll d; cin >> d;
            adj[a].emplace_back(b, d);
        }
    }

    // every path on tree T has some LCA a in the path (a can be an endpoint)
    // for each LCA a, find longest dist to leaf for each child subtree, add max 2
    ll longestPath = 0;
    dfs(longestPath, adj, 0, 0);
    cout << longestPath << endl;
}
