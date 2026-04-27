/*
Gold 3
2533 - 사회망 서비스(SNS)
meta: {"problemId": 2533, "titleKo": "사회망 서비스(SNS)", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "사회망 서비스(SNS)", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 9304, "level": 13, "votedUserCount": 175, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 2.518899917602539, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "dp_tree", "isMeta": false, "bojTagId": 92, "problemCount": 597, "displayNames": [{"language": "ko", "name": "트리에서의 다이나믹 프로그래밍", "short": "트리에서의 다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming on trees", "short": "tree dp"}, {"language": "ja", "name": "木上の動的計画法", "short": "tree dp"}], "aliases": [{"alias": "트리dp"}]}, {"key": "trees", "isMeta": false, "bojTagId": 120, "problemCount": 1920, "displayNames": [{"language": "ko", "name": "트리", "short": "트리"}, {"language": "en", "name": "tree", "short": "tree"}, {"language": "ja", "name": "木", "short": "木"}], "aliases": [{"alias": "trees"}]}], "metadata": {}}
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

pair<int,int> dfs(vector<vector<int>> &adj, int curr, int parent = -1) {
    pair<int,int> res = {0, 1};
    for (int next : adj[curr]) {
        if (next == parent) continue;

        pair<int,int> nextRes = dfs(adj, next, curr);
        res.first += nextRes.second;
        res.second += min(nextRes.first, nextRes.second);
    }
    return res;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // tree dp: dp[i][0] = min early in subtree if this node not early, dp[i][1] = min early in subtree if this node is early
    pair<int,int> res = dfs(adj, 0);
    cout << min(res.first, res.second) << "\n";
}
