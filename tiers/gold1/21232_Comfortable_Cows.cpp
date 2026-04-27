/*
Gold 1
21232 - Comfortable Cows
meta: {"problemId": 21232, "titleKo": "Comfortable Cows", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Comfortable Cows", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 123, "level": 15, "votedUserCount": 26, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.512200117111206, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "simulation", "isMeta": false, "bojTagId": 141, "problemCount": 1369, "displayNames": [{"language": "ko", "name": "시뮬레이션", "short": "시뮬레이션"}, {"language": "en", "name": "simulation", "short": "simulation"}, {"language": "ja", "name": "シミュレーション", "short": "シミュレーション"}], "aliases": []}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}, {"key": "grid_graph", "isMeta": false, "bojTagId": 221, "problemCount": 264, "displayNames": [{"language": "ko", "name": "격자 그래프", "short": "격자 그래프"}, {"language": "en", "name": "grid graph", "short": "grid graph"}], "aliases": []}, {"key": "queue", "isMeta": false, "bojTagId": 72, "problemCount": 74, "displayNames": [{"language": "ko", "name": "큐", "short": "큐"}, {"language": "en", "name": "queue", "short": "queue"}, {"language": "ja", "name": "キュー", "short": "キュー"}], "aliases": []}], "metadata": {}}
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

    const int N = 2048;
    vector<vector<bool>> board(N * 2, vector<bool>(N * 2));
    
    queue<pair<int,int>> q;
    int cows = 0;
    auto check = [&](int x, int y) {
        if (!board[x][y]) return;

        int nbs = (int)board[x - 1][y] + (int)board[x + 1][y] + (int)board[x][y - 1] + (int)board[x][y + 1];
        if (nbs != 3) return;

        q.emplace(x - 1, y);
        q.emplace(x + 1, y);
        q.emplace(x, y - 1);
        q.emplace(x, y + 1);
    };

    vector<pair<int,int>> input(n);
    for (auto &[x, y] : input) {
        cin >> x >> y; x += N; y += N;
    }
    for (int i = 0; i < n; ++i) {
        q.push(input[i]);
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            if (board[x][y]) continue;

            board[x][y] = true;
            ++cows;
            check(x, y);
            check(x-1, y);
            check(x+1, y);
            check(x, y-1);
            check(x, y+1);
        }
        int added = cows - (i + 1);
        cout << added << "\n";
    }
}
