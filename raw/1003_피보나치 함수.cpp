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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // dp[i][j] = # times j appears for fib(i)
    vector<array<int,2>> dp;
    dp.push_back({1, 0});
    dp.push_back({0, 1});
    auto extend = [&]() {
        int n = (int)dp.size();
        dp.push_back({dp[n-2][0] + dp[n-1][0], dp[n-2][1] + dp[n-1][1]});
    };


    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        while ((int)dp.size() <= n) extend();
        cout << dp[n][0] << " " << dp[n][1] << "\n";
    }
}
