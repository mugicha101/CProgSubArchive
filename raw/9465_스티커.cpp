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

    int tc;
    cin >> tc;
    while (tc--) {
        // knapsack dp
        // dp[c][r] = max score picking row r (0 or 1) in column j (1 indexed)
        // dp[0][r] = 0
        int cols; cin >> cols;
        vector<vector<int>> grid(2, vector<int>(cols));
        for (int r = 0; r < 2; ++r) {
            for (int c = 0; c < cols; ++c) {
                cin >> grid[r][c];
            }
        }
        vector<vector<int>> dp(2, vector<int>(cols+2));
        for (int c = 0; c < cols; ++c) {
            for (int r = 0; r < 2; ++r) {
                auto update = [&](int tr, int tc, int v) {
                    dp[tr][tc] = max(dp[tr][tc], v);
                };
                int skip = dp[r][c];
                int pick = dp[r][c] + grid[r][c];
                update(r, c+1, skip);
                update(r, c+2, pick);
                update(1-r, c+1, pick);
            }
        }
        cout << max({dp[0][cols], dp[0][cols+1], dp[1][cols], dp[1][cols+1]}) << endl;
    }
}
