/*
Gold 5
7576 - 토마토
meta: {"problemId": 7576, "titleKo": "토마토", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "토마토", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 63487, "level": 11, "votedUserCount": 170, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 2.5653998851776123, "official": true, "tags": [{"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "grid_graph", "isMeta": false, "bojTagId": 221, "problemCount": 264, "displayNames": [{"language": "ko", "name": "격자 그래프", "short": "격자 그래프"}, {"language": "en", "name": "grid graph", "short": "grid graph"}], "aliases": []}, {"key": "shortest_path", "isMeta": false, "bojTagId": 215, "problemCount": 990, "displayNames": [{"language": "ko", "name": "최단 경로", "short": "최단 경로"}, {"language": "en", "name": "shortest path", "short": "shortest path"}, {"language": "ja", "name": "最短経路", "short": "最短経路"}], "aliases": []}], "metadata": {}}
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

    int rows, cols;
    cin >> cols >> rows;
    int remaining = 0;
    vector<vector<int8_t>> grid(rows, vector<int8_t>(cols, 0));
    queue<pair<int,int>> q;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int x; cin >> x;
            grid[r][c] = (int8_t)x;
            if (x == 1) q.emplace(r, c);
            remaining += x != -1;
        }
    }
    int days = -1;
    while (!q.empty()) {
        ++days;
        for (int qi = (int)q.size(); qi > 0; --qi) {
            auto [r, c] = q.front();
            q.pop();
            --remaining;
            auto check = [&](int r, int c) {
                if (grid[r][c] != 0) return;

                grid[r][c] = 1;
                q.emplace(r, c);
            };
            if (r) check(r-1, c);
            if (c) check(r, c-1);
            if (r+1 < rows) check(r+1, c);
            if (c+1 < cols) check(r, c+1);
        }
    }
    cout << (remaining ? -1 : max(days, 0)) << endl;
}
