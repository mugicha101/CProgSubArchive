// 2024-10-22 19:02:42 
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    int n, m;
    cin >> n >> m;
    vector<int> marr(n+1);
    marr[0] = m;
    for (int i = 1; i <= n; ++i) {
        marr[i] = marr[i-1] * 2 / 3;
    }
    vector<int> vals(n);
    for (int i = 0; i < n; ++i) {
        cin >> vals[i];
    }
    vals.push_back(0);

    // state: (i, j) -> max score starting from index i in vals and j consecutive hours of penalty before i
    // note: i eaten guaranteed
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    int best = 0;
    for (int i = n-1; i >= 0; --i) {
        for (int j = 0; j < n; ++j) {
            int v = min(marr[j], vals[i]);

            for (int k = i+1; k <= n; ++k) {
                int j2 = k == i+1 ? j+1 : k == i+2 ? j : 0;
                dp[i][j] = max(dp[i][j], dp[k][j2] + v);
            }
        }
        best = max(best, dp[i][0]);
    }
    cout << best << endl;
}
