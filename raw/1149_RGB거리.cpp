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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n;
    cin >> n;
    vector<array<int,3>> costs(n);
    for (auto &h : costs) {
        cin >> h[0] >> h[1] >> h[2];
    }
    array<int,3> minCost = costs[0]; // dp[i][j] = min cost to paint houses up to i, with ith house painted j, compress i away
    for (int i = 1; i < n; ++i) {
        minCost = {
            min(minCost[1], minCost[2]) + costs[i][0],
            min(minCost[0], minCost[2]) + costs[i][1],
            min(minCost[0], minCost[1]) + costs[i][2]
        };
    }
    cout << min({minCost[0], minCost[1], minCost[2]}) << endl;
}
