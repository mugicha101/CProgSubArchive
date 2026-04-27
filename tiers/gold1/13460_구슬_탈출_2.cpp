/*
Gold 1
13460 - 구슬 탈출 2
meta: {"problemId": 13460, "titleKo": "구슬 탈출 2", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "구슬 탈출 2", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 20844, "level": 15, "votedUserCount": 432, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.3733999729156494, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "simulation", "isMeta": false, "bojTagId": 141, "problemCount": 1369, "displayNames": [{"language": "ko", "name": "시뮬레이션", "short": "시뮬레이션"}, {"language": "en", "name": "simulation", "short": "simulation"}, {"language": "ja", "name": "シミュレーション", "short": "シミュレーション"}], "aliases": []}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}], "metadata": {}}
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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int rows, cols; cin >> rows >> cols;
    vector<string> grid(rows);
    using pos_t = pair<int,int>;
    pos_t initR, initB;
    for (int r = 0; r < rows; ++r) {
        cin >> grid[r];
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '.' || grid[r][c] == '#' || grid[r][c] == 'O') continue;

            (grid[r][c] == 'R' ? initR : initB) = make_pair(r, c);
            grid[r][c] = '.';
        }
    }
    set<pair<pos_t, pos_t>> visited;
    queue<pair<pos_t,pos_t>> q;
    q.emplace(initR, initB);
    visited.insert(make_pair(initR, initB));

    auto at = [&](pos_t pos) -> char & {
        return grid[pos.first][pos.second];
    };
    auto move = [&](pos_t posR, pos_t posB, int dr, int dc) {
        auto moveBall = [&](pos_t &pos) {
            while (at(pos) == '.') {
                pos.first += dr;
                pos.second += dc;
            }
            if (at(pos) == '#') {
                pos.first -= dr;
                pos.second -= dc;
            }
        };
        at(posB) = '#';
        moveBall(posR);
        at(posB) = '.';
        if (at(posR) == '.') at(posR) = '#';
        moveBall(posB);
        if (at(posR) == '#') at(posR) = '.';
        if (at(posB) == '.') at(posB) = '#';
        moveBall(posR);
        if (at(posB) == '#') at(posB) = '.';
        pair<pos_t, pos_t> state = make_pair(posR, posB);
        if (at(posB) == 'O' || !visited.insert(state).second) return false;

        if (at(posR) == 'O') return true;
        
        q.emplace(posR, posB);
        return false;
    };

    for (int m = 1; m <= 10; ++m) {
        for (int qi = q.size(); qi > 0; --qi) {
            auto [posR, posB] = q.front();
            q.pop();

            if (move(posR, posB, -1, 0) || move(posR, posB, 1, 0) || move(posR, posB, 0, -1) || move(posR, posB, 0, 1)) {
                cout << m << "\n";
                return 0;
            }
        }
    }
    cout << -1 << "\n";
}
