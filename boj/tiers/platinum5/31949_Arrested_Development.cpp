/*
Platinum 5
31949 - Arrested Development
meta: {"problemId": 31949, "titleKo": "Arrested Development", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Arrested Development", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 73, "level": 16, "votedUserCount": 13, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.6438000202178955, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "knapsack", "isMeta": false, "bojTagId": 148, "problemCount": 345, "displayNames": [{"language": "ko", "name": "배낭 문제", "short": "배낭"}, {"language": "en", "name": "knapsack", "short": "knapsack"}, {"language": "ja", "name": "ナップサック問題", "short": "ナップサック"}], "aliases": [{"alias": "냅색"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;

const int MOD = 1000000007;
 
typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
// #define endl "\n"

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // variant of multicore scheduling with per-core WCETs for each task
    // n <= 50, k <= 10^5 (k = max WCET)
    // sum time <= 5 * 10^6

    // naive 2D:
    // dp state: tasks processed, intern a time, intern b time -> reachable
    // this blows up to 1.250 * 10^15

    // optimized 1D:
    // dp state: tasks processed, intern a time -> minimal intern b time
    // dp transition: dp[i][a][b] -> dp[i-1][a+t[i][a]][b-t[i][b]]
    // this consists of 2.5 * 10^8 states, each being visited O(1) times

    int n; cin >> n;
    vector<pair<int,int>> tasks(n);
    int asum = 0, bsum = 0;
    for (auto &[a, b] : tasks) {
        cin >> a >> b;
        asum += a;
        bsum += b;
    }
    
    vector<int> dp(asum + 1, bsum + 1);
    dp[0] = bsum;
    for (auto &[ta, tb] : tasks) {
        for (int a = asum; a >= ta; --a) {
            dp[a] = min(dp[a], dp[a - ta] - tb);
        }
    }

    int best = INT_MAX;
    for (int a = 0; a <= asum; ++a) {
        best = min(best, max(a, dp[a]));
    }
    cout << best << endl;
}
