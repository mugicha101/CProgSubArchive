/*
Gold 1
2098 - 외판원 순회
meta: {"problemId": 2098, "titleKo": "외판원 순회", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "외판원 순회", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 12937, "level": 15, "votedUserCount": 197, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 3.408099889755249, "official": true, "tags": [{"key": "bitmask", "isMeta": false, "bojTagId": 14, "problemCount": 1027, "displayNames": [{"language": "ko", "name": "비트마스킹", "short": "비트마스킹"}, {"language": "en", "name": "bitmask", "short": "bitmask"}, {"language": "ja", "name": "ビット表現", "short": "ビット表現"}], "aliases": [{"alias": "비트필드"}, {"alias": "비트마스크"}]}, {"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "dp_bitfield", "isMeta": false, "bojTagId": 87, "problemCount": 409, "displayNames": [{"language": "ko", "name": "비트필드를 이용한 다이나믹 프로그래밍", "short": "비트필드를 이용한 다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming using bitfield", "short": "bitfield dp"}, {"language": "ja", "name": "ビットを使用した動的計画法", "short": "ビットdp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "비트마스크"}, {"alias": "비트dp"}]}, {"key": "tsp", "isMeta": false, "bojTagId": 138, "problemCount": 71, "displayNames": [{"language": "ko", "name": "외판원 순회 문제", "short": "외판원 순회"}, {"language": "en", "name": "travelling salesman problem", "short": "tsp"}, {"language": "ja", "name": "巡回セールスマン問題", "short": "巡回セールスマン"}], "aliases": [{"alias": "외판원순회"}]}], "metadata": {}}
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

int n;
int cost[16][16];
int memo[16][1 << 16];
int dfs(int curr, int visited) {
    if (visited + 1 == (1 << n)) return cost[curr][0];

    int &r = memo[curr][visited];
    if (r != -1) return r;

    int best = INT_MAX >> 4;
    for (int next = 0; next < n; ++next) {
        if ((visited >> next) & 1) continue;

        best = min(best, cost[curr][next] + dfs(next, visited | (1 << next)));
    }
    
    r = best;
    return best;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> cost[i][j];
            if (cost[i][j] == 0) cost[i][j] = INT_MAX >> 4;
        }
    }
    memset(memo, -1, sizeof(memo));
    cout << dfs(0, 1) << "\n";
}
