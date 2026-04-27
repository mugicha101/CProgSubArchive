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

void dfs(vector<vector<int>> &psum, int r, int c, int n, array<int,2> &out) {
    int s = psum[r+n][c+n] - psum[r][c+n] - psum[r+n][c] + psum[r][c];
    if (s == 0) {
        ++out[0];
        return;
    }
    if (s == n * n) {
        ++out[1];
        return;
    }
    n >>= 1;
    dfs(psum, r, c, n, out);
    dfs(psum, r + n, c, n, out);
    dfs(psum, r, c + n, n, out);
    dfs(psum, r + n, c + n, n, out);
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    ll n, t; cin >> n >> t;
    vector<ll> trees(n); for (ll &x : trees) cin >> x;

    // bsearch
    ll l = 0;
    ll r = *max_element(all(trees));
    while (l != r) {
        ll m = (l + r + 1) >> 1;
        ll logs = 0;
        for (ll x : trees) {
            logs += max(x - m, 0LL);
        }
        if (logs >= t) l = m;
        else r = m - 1;
    }
    cout << l << endl;
}
