/*
Gold 5
12865 - 평범한 배낭
meta: {"problemId": 12865, "titleKo": "평범한 배낭", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "평범한 배낭", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 46624, "level": 11, "votedUserCount": 123, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 2.654400110244751, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "knapsack", "isMeta": false, "bojTagId": 148, "problemCount": 345, "displayNames": [{"language": "ko", "name": "배낭 문제", "short": "배낭"}, {"language": "en", "name": "knapsack", "short": "knapsack"}, {"language": "ja", "name": "ナップサック問題", "short": "ナップサック"}], "aliases": [{"alias": "냅색"}]}], "metadata": {}}
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

void dfs(vector<vector<int>> &adj, vector<int> &parent, int curr) {
    for (int next : adj[curr]) {
        if (next == parent[curr]) continue;

        parent[next] = curr;
        dfs(adj, parent, next);
    }
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, k; cin >> n >> k;
    vector<pair<int,int>> items(n); // weight, value
    for (auto &x : items) cin >> x.first >> x.second;
    vector<int> dp(k+1, 0);
    for (int i = 0; i < n; ++i) {
        auto [w, v] = items[i];
        for (int j = k; j >= w; --j) {
            dp[j] = max(dp[j], dp[j-w] + v);
        }
    }
    cout << *max_element(all(dp)) << "\n";
}
