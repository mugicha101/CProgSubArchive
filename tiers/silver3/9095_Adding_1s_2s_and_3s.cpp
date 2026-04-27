/*
Silver 3
9095 - Adding 1s, 2s, and 3s
meta: {"problemId": 9095, "titleKo": "1, 2, 3 더하기", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "1, 2, 3 더하기", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Adding 1s, 2s, and 3s", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 73108, "level": 8, "votedUserCount": 208, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.5324000120162964, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}], "metadata": {}}
*/

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

    int tc;
    cin >> tc;
    ll fac[21];
    fac[0] = 1;
    fac[1] = 1;
    for (ll x = 2; x < 21; ++x) fac[x] = fac[x-1] * x;

    // ways[i][j] = ways to sum to j using i terms
    // 0 <= i <= 11, 0 <= j <= 11
    // ways[0][j>0] = 0
    // ways[0][0] = 1
    // ways[i>0][0] = 0
    // ways[i][j] = ways[i-1][j-3] + ways[i-1][j-2] + ways[i-1][j-1]
    int ways[12][12] = {};
    ways[0][0] = 1;
    for (int i = 1; i <= 11; ++i) {
        ways[i][1] = ways[i-1][0];
        ways[i][2] = ways[i-1][0] + ways[i-1][1];
        for (int j = 3; j <= 11; ++j) {
            ways[i][j] = ways[i-1][j-3] + ways[i-1][j-2] + ways[i-1][j-1];
        }
    }
    
    while (tc--) {
        int x;
        cin >> x;

        int sum = 0;
        for (int i = 0; i <= 11; ++i) sum += ways[i][x];
        cout << sum << endl;
    }
}
