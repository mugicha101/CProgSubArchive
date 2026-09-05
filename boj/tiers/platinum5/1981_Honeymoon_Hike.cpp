/*
Platinum 5
1981 - Honeymoon Hike
meta: {"problemId": 1981, "titleKo": "배열에서 이동", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "배열에서 이동", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Honeymoon Hike", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 2222, "level": 16, "votedUserCount": 163, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.88070011138916, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "binary_search", "isMeta": false, "bojTagId": 12, "problemCount": 1665, "displayNames": [{"language": "ko", "name": "이분 탐색", "short": "이분 탐색"}, {"language": "en", "name": "binary search", "short": "binary search"}, {"language": "ja", "name": "二分探索", "short": "二分探索"}], "aliases": [{"alias": "이분탐색"}, {"alias": "이진탐색"}]}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}, {"key": "grid_graph", "isMeta": false, "bojTagId": 221, "problemCount": 264, "displayNames": [{"language": "ko", "name": "격자 그래프", "short": "격자 그래프"}, {"language": "en", "name": "grid graph", "short": "grid graph"}], "aliases": []}], "metadata": {}}
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

    int n; cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            cin >> grid[r][c];
        }
    }
    
    // fix min height, minimize max height (dijkstras in O(n^2lgn))
    // O(kn^2lgn)
    int startH = grid[0][0];
    int endH = grid[n-1][n-1];
    int maxMinH = min(startH, endH);
    vector<vector<int>> minMaxH(n, vector<int>(n));
    int best = 1000;
    for (int minH = 0; minH <= maxMinH; ++minH) {
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
        for (auto &row : minMaxH) {
            fill(all(row), 1000);
        }
        auto check = [&](int h, int r, int c) {
            h = max(h, grid[r][c]);
            if (grid[r][c] < minH || minMaxH[r][c] <= h) return;

            minMaxH[r][c] = h;
            pq.emplace(h, r, c);
        };
        check(0, 0, 0);

        while (!pq.empty()) {
            auto [h, r, c] = pq.top();
            pq.pop();
            if (r) check(h, r-1, c);
            if (c) check(h, r, c-1);
            if (r+1 < n) check(h, r+1, c);
            if (c+1 < n) check(h, r, c+1);
        }
        best = min(best, minMaxH[n-1][n-1] - minH);
    }
    cout << best << "\n";
}
