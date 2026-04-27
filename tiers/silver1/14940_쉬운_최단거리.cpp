/*
Silver 1
14940 - 쉬운 최단거리
meta: {"problemId": 14940, "titleKo": "쉬운 최단거리", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "쉬운 최단거리", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 18458, "level": 10, "votedUserCount": 201, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.5710999965667725, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}, {"key": "grid_graph", "isMeta": false, "bojTagId": 221, "problemCount": 264, "displayNames": [{"language": "ko", "name": "격자 그래프", "short": "격자 그래프"}, {"language": "en", "name": "grid graph", "short": "grid graph"}], "aliases": []}], "metadata": {}}
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
#define sz(x) ((int)x.size())

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int rows, cols; cin >> rows >> cols;
    vector<vector<int>> grid(rows, vector<int>(cols));
    queue<pair<int,int>> q;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cin >> grid[r][c];
            grid[r][c] -= 2;
            if (grid[r][c] == 0) q.emplace(r, c);
        }
    }
    int d = 0;
    while (!q.empty()) {
        ++d;
        for (int qi = (int)q.size(); qi > 0; --qi) {
            auto [r, c] = q.front();
            q.pop();
            auto check = [&](int r, int c) {
                if (grid[r][c] != -1) return;

                grid[r][c] = d;
                q.emplace(r, c);
            };
            if (r) check(r-1, c);
            if (c) check(r, c-1);
            if (r+1 < rows) check(r+1, c);
            if (c+1 < cols) check(r, c+1);
        }
    }
    for (auto &row : grid) {
        for (int x : row) {
            cout << (x == -2 ? 0 : x) << " ";
        }
        cout << "\n";
    }
}
