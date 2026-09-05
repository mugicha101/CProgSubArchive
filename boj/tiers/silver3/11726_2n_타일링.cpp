/*
Silver 3
11726 - 2×n 타일링
meta: {"problemId": 11726, "titleKo": "2×n 타일링", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "2×n 타일링", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 65875, "level": 8, "votedUserCount": 224, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.6875, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}], "metadata": {}}
*/

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
int MOD = 1000000007;

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

    int n;
    cin >> n;
    MOD = 10007;

    // can either | or =
    // cannot misaligned blocks since doesn't fit
    // dp[k] = ways to fill k columns
    // dp[k] = dp[k-1] (add |) + dp[k-2] (add =) = (k+1)th fibonacci number
    // dp[0] = 1, dp[1] = 1
    int a = 1, b = 1;
    while (--n) {
        int c = a + b;
        if (c >= MOD) c -= MOD;
        a = b;
        b = c;
    }
    cout << b << endl;
}
