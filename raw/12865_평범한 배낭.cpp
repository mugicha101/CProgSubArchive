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
    vector<pair<int,int>> items(n); // weight, value
    for (auto &x : items) cin >> x.first >> x.second;
    vector<int> dp(k+1, 0);
    for (int i = 0; i < n; ++i) {
        auto [w, v] = items[i];
        for (int j = k; j >= w; --j) {
            dp[j] = max(dp[j], dp[j-w] + v);
        }
    }
    cout << *max_element(all(dp)) << "\n";
}
