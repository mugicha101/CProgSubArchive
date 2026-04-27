/*
Gold 1
1562 - 계단 수
meta: {"problemId": 1562, "titleKo": "계단 수", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "계단 수", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 7481, "level": 15, "votedUserCount": 315, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.848099946975708, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "bitmask", "isMeta": false, "bojTagId": 14, "problemCount": 1027, "displayNames": [{"language": "ko", "name": "비트마스킹", "short": "비트마스킹"}, {"language": "en", "name": "bitmask", "short": "bitmask"}, {"language": "ja", "name": "ビット表現", "short": "ビット表現"}], "aliases": [{"alias": "비트필드"}, {"alias": "비트마스크"}]}, {"key": "dp_bitfield", "isMeta": false, "bojTagId": 87, "problemCount": 409, "displayNames": [{"language": "ko", "name": "비트필드를 이용한 다이나믹 프로그래밍", "short": "비트필드를 이용한 다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming using bitfield", "short": "bitfield dp"}, {"language": "ja", "name": "ビットを使用した動的計画法", "short": "ビットdp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "비트마스크"}, {"alias": "비트dp"}]}], "metadata": {}}
*/

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

int memo[101][1 << 10][10];
int dfs(int l, int m, int d) {
    if (l == 0) return m + 1 == (1 << 10);

    int &r = memo[l][m][d];
    if (r != -1) return r;

    r = 0;
    if (d > 0) r += dfs(l-1, m | (1 << (d-1)), d-1);
    if (d < 9) r += dfs(l-1, m | (1 << (d+1)), d+1);
    if (r >= 1000000000) r -= 1000000000;
    
    return r;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // dp: remaining length l, used digit mask m, last digit d -> ways to form numbers with 0-9 using remaining length
    // 1 <= l <= 100, 0 <= m <= 2^10 - 1 = 1023, 0 <= d <= 9, so statespace is at most 100 * 1024 * 10 = 1024000
    memset(memo, -1, sizeof(memo));
    ll sum = 0;
    int n; cin >> n;
    for (int d = 1; d < 10; ++d) {
        sum += dfs(n-1, 1 << d, d);
    }
    cout << sum % 1000000000LL << endl;
}
