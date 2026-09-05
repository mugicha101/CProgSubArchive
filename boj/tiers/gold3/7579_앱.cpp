/*
Gold 3
7579 - 앱
meta: {"problemId": 7579, "titleKo": "앱", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "앱", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 11920, "level": 13, "votedUserCount": 136, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 2.8893001079559326, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "knapsack", "isMeta": false, "bojTagId": 148, "problemCount": 345, "displayNames": [{"language": "ko", "name": "배낭 문제", "short": "배낭"}, {"language": "en", "name": "knapsack", "short": "knapsack"}, {"language": "ja", "name": "ナップサック問題", "short": "ナップサック"}], "aliases": [{"alias": "냅색"}]}], "metadata": {}}
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

#include <bits/stdc++.h>
using namespace std;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // n <= 100, m <= 10^7
    // mem[i] <= 10^7
    // cost[i] <= 100
    // sum(costs) <= 100 * 100 = 10^4
    // knapsack state: maximize freed memory with set max cost
    // bsearch on max cost
    int n, m; cin >> n >> m;
    vector<int> mem(n); vcin(mem);
    vector<int> cost(n); vcin(cost);

    // check max amount of memory freeable with a set max cost
    auto maxFreeable = [&](int maxCost) {
        // simple knapsack
        vector<int> dp(maxCost+1);
        for (int i = 0; i < n; ++i) {
            int cv = cost[i];
            int mv = mem[i];
            for (int k = maxCost; k >= cv; --k) {
                dp[k] = max(dp[k], dp[k-cv] + mv);
            }
        }
        return *max_element(all(dp));
    };

    // bsearch on max cost
    int maxCostLB = 0;
    int maxCostUB = accumulate(all(cost), 0);
    while (maxCostLB != maxCostUB) {
        int maxCostEst = (maxCostLB + maxCostUB) >> 1;
        if (maxFreeable(maxCostEst) >= m) {
            maxCostUB = maxCostEst;
        } else {
            maxCostLB = maxCostEst + 1;
        }
    }
    cout << maxCostLB << "\n";
}
