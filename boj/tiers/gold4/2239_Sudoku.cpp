/*
Gold 4
2239 - Sudoku
meta: {"problemId": 2239, "titleKo": "스도쿠", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "스도쿠", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Sudoku", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 11967, "level": 12, "votedUserCount": 288, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.1549999713897705, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "backtracking", "isMeta": false, "bojTagId": 5, "problemCount": 656, "displayNames": [{"language": "ko", "name": "백트래킹", "short": "백트래킹"}, {"language": "en", "name": "backtracking", "short": "backtrack"}, {"language": "ja", "name": "バックトラック法", "short": "バックトラック"}], "aliases": [{"alias": "백트래킹"}, {"alias": "퇴각검색"}, {"alias": "퇴각 검색"}]}], "metadata": {}}
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

uint8_t board[9][9];
bitset<10> rowMask[9] = {};
bitset<10> colMask[9] = {};
bitset<10> regionMask[9] = {};

inline int regionId(int r, int c) {
    return (r / 3) * 3 + (c / 3);
}

void toggle(int r, int c, int d) {
    rowMask[r][d].flip();
    colMask[c][d].flip();
    regionMask[regionId(r, c)][d].flip();
}

bool dfs(int r, int c) {
    if (r == 9) return true;

    int nr = r + (c == 8);
    int nc = c == 8 ? 0 : c + 1;

    if (board[r][c]) {
        return dfs(nr, nc);
    }

    bitset<10> used = rowMask[r] | colMask[c] | regionMask[regionId(r, c)];
    for (int d = 1; d <= 9; ++d) {
        if (used[d]) continue;

        toggle(r, c, d);
        board[r][c] = d;
        if (dfs(nr, nc)) return true;

        toggle(r, c, d);
    }
    board[r][c] = 0;

    return false;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            char x; cin >> x;
            board[r][c] = x - '0';
            if (board[r][c]) toggle(r, c, board[r][c]);
        }
    }

    // in each tile, try available options until complete
    dfs(0, 0);
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            cout << (int)board[r][c];
        }
        cout << endl;
    }
}
