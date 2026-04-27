/*
Gold 3
1005 - ACM Craft
meta: {"problemId": 1005, "titleKo": "ACM Craft", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "ACM Craft", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 20270, "level": 13, "votedUserCount": 576, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.1624999046325684, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "dag", "isMeta": false, "bojTagId": 213, "problemCount": 340, "displayNames": [{"language": "ko", "name": "방향 비순환 그래프", "short": "dag"}, {"language": "en", "name": "directed acyclic graph", "short": "dag"}, {"language": "ja", "name": "有向非巡回グラフ", "short": "有向非巡回グラフ"}], "aliases": []}, {"key": "topological_sorting", "isMeta": false, "bojTagId": 78, "problemCount": 255, "displayNames": [{"language": "ko", "name": "위상 정렬", "short": "위상 정렬"}, {"language": "en", "name": "topological sorting", "short": "topological sorting"}, {"language": "ja", "name": "トポロジカルソート", "short": "トポロジカルソート"}], "aliases": []}], "metadata": {}}
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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int tc; cin >> tc;
    while (tc--) {
        int n, k; cin >> n >> k;
        vector<int> buildTime(n); // time it takes to construct
        for (int &x : buildTime) cin >> x;
        vector<int> releaseTime(n); // time until construction can start
        vector<vector<int>> adj(n);
        vector<int> indeg(n);
        while (k--) {
            int a, b; cin >> a >> b; --a; --b;
            adj[a].push_back(b);
            ++indeg[b];
        }
        
        // toposort, keep track of first arrival time
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indeg[i]) continue;

            q.push(i);
        }
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            int t = releaseTime[curr] + buildTime[curr];
            for (int next : adj[curr]) {
                releaseTime[next] = max(releaseTime[next], t);
                if (--indeg[next]) continue;

                q.push(next);
            }
        }
        
        int w; cin >> w; --w;
        cout << releaseTime[w] + buildTime[w] << "\n";
    }
}
