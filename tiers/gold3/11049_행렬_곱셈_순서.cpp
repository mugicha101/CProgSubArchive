/*
Gold 3
11049 - 행렬 곱셈 순서
meta: {"problemId": 11049, "titleKo": "행렬 곱셈 순서", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "행렬 곱셈 순서", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 15911, "level": 13, "votedUserCount": 156, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 2.2643001079559326, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned int uint;
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
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

#include <bits/stdc++.h>
using namespace std;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<int> vals(n+1);
    vector<int> next(n+1);
    iota(all(next), 1);
    for (int i = 0; i < n; ++i) {
        cin >> vals[i] >> vals[i+1];
    }

    // each layer, split matrices into 2 parenthesis groups
    // these groups all resolve to same matrix regardless of ops
    // [i, j] refers to group spanning ith matrix to j-1th matrix
    // so parenthesis split will be [i, k], [k, j]
    // dp[i][j] = min ops to get to matrix [i, j] (i < j)
    // dp[i][i+1] = 0
    // dp[i][j] = min(dp[i][k] + dp[k][j] + v[i] * v[k] * v[j] : i < k < j)
    // can do bottom up in increasing matrix spans
    n = vals.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int d = 2; d < n; ++d) {
        for (int j = d; j < n; ++j) {
            int i = j - d;
            dp[i][j] = INT_MAX;
            int m = vals[i] * vals[j];
            for (int k = i+1; k < j; ++k) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + vals[k] * m);
            }
        }
    }
    cout << dp[0][n-1] << endl;
}