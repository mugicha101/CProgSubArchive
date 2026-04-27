/*
Gold 1
1035 - 조각 움직이기
meta: {"problemId": 1035, "titleKo": "조각 움직이기", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "조각 움직이기", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 943, "level": 15, "votedUserCount": 75, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.0381999015808105, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "bruteforcing", "isMeta": false, "bojTagId": 125, "problemCount": 2803, "displayNames": [{"language": "ko", "name": "브루트포스 알고리즘", "short": "브루트포스 알고리즘"}, {"language": "en", "name": "bruteforcing", "short": "bruteforce"}, {"language": "ja", "name": "全探索", "short": "全探索"}], "aliases": [{"alias": "완전탐색"}, {"alias": "완전 탐색"}, {"alias": "브루트포스"}, {"alias": "bruteforce"}, {"alias": "brute force"}, {"alias": "완탐"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}, {"key": "bitmask", "isMeta": false, "bojTagId": 14, "problemCount": 1027, "displayNames": [{"language": "ko", "name": "비트마스킹", "short": "비트마스킹"}, {"language": "en", "name": "bitmask", "short": "bitmask"}, {"language": "ja", "name": "ビット表現", "short": "ビット表現"}], "aliases": [{"alias": "비트필드"}, {"alias": "비트마스크"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007

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

int dfs(const vector<pair<int,int>> &pos, array<bitset<5>,5> &grid, int used, int d) {
    if (d == (int)pos.size()) return 0;

    int best = INT_MAX >> 4;
    if (d == 0) {
        for (int i = 0; i < (int)pos.size(); ++i) {
            grid[pos[i].first][pos[i].second] = true;
            best = min(best, dfs(pos, grid, 1 << i, 1));
            grid[pos[i].first][pos[i].second] = false;
        }
        return best;
    }

    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            if (grid[r][c] || !((r && grid[r-1][c]) || (c && grid[r][c-1]) || (r < 4 && grid[r+1][c]) || (c < 4 && grid[r][c+1]))) continue;

            grid[r][c] = true;
            for (int i = 0; i < (int)pos.size(); ++i) {
                if ((used >> i) & 1) continue;

                int dist = abs(pos[i].first - r) + abs(pos[i].second - c);
                best = min(best, dist + dfs(pos, grid, used | (1 << i), d+1));
            }
            grid[r][c] = false;
        }
    }
    return best;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    vector<pair<int,int>> pos;
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            char t; cin >> t;
            if (t == '*') pos.emplace_back(r, c);
        }
    }

    // optimal solution has one piece remaining still
    // rest of them must move to the starting piece
    // at most 5! possible orders to move pieces
    // to move a piece, move to closest neighboring tile (if multiple, pick one, guaranteed to have no blockers on optimal)
    // algorithm: fix one piece, try all next piece in all adjacent tile combos at cost of manhattan distance, # leaves <= 4 * 6 * 8 * 10 * 5! < 10^6
    // can scan entire 5x5 board per level while keeping < 10^7 ops (can maintain neighbor set but this is easier)
    array<bitset<5>,5> grid;
    cout << dfs(pos, grid, 0, 0) << endl;
}
