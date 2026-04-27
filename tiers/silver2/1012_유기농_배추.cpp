/*
Silver 2
1012 - 유기농 배추
meta: {"problemId": 1012, "titleKo": "유기농 배추", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "유기농 배추", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 69590, "level": 9, "votedUserCount": 148, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 2.4714999198913574, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}, {"key": "dfs", "isMeta": false, "bojTagId": 127, "problemCount": 964, "displayNames": [{"language": "ko", "name": "깊이 우선 탐색", "short": "깊이 우선 탐색"}, {"language": "en", "name": "depth-first search", "short": "dfs"}, {"language": "ja", "name": "深さ優先探索", "short": "dfs"}], "aliases": [{"alias": "depth first"}, {"alias": "depthfirst"}]}, {"key": "grid_graph", "isMeta": false, "bojTagId": 221, "problemCount": 264, "displayNames": [{"language": "ko", "name": "격자 그래프", "short": "격자 그래프"}, {"language": "en", "name": "grid graph", "short": "grid graph"}], "aliases": []}, {"key": "flood_fill", "isMeta": false, "bojTagId": 210, "problemCount": 82, "displayNames": [{"language": "ko", "name": "플러드 필", "short": "플러드 필"}, {"language": "en", "name": "flood-fill", "short": "ff"}, {"language": "ja", "name": "flood-fill", "short": "ff"}], "aliases": []}], "metadata": {}}
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

    int tc; cin >> tc;
    while (tc--) {
        int rows, cols, k; cin >> rows >> cols >> k;
        vector<vector<bool>> grid(rows, vector<bool>(cols, true));
        while (k--) {
            int r, c; cin >> r >> c;
            grid[r][c] = false;
        }

        // count components
        int comps = 0;
        queue<pair<int,int>> q;
        for (int sr = 0; sr < rows; ++sr) {
            for (int sc = 0; sc < cols; ++sc) {
                if (grid[sr][sc]) continue;

                ++comps;
                grid[sr][sc] = true;
                q.emplace(sr, sc);
                while (!q.empty()) {
                    auto [r, c] = q.front();
                    q.pop();
                    auto check = [&](int r, int c) {
                        if (grid[r][c]) return;

                        grid[r][c] = true;
                        q.emplace(r, c);
                    };
                    if (r) check(r-1, c);
                    if (c) check(r, c-1);
                    if (r+1 < rows) check(r+1, c);
                    if (c+1 < cols) check(r, c+1);
                }
            }
        }
        cout << comps << "\n";
    }
}
