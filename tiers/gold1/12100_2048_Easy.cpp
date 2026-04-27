/*
Gold 1
12100 - 2048 (Easy)
meta: {"problemId": 12100, "titleKo": "2048 (Easy)", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "2048 (Easy)", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 20735, "level": 15, "votedUserCount": 456, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.5861001014709473, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "bruteforcing", "isMeta": false, "bojTagId": 125, "problemCount": 2803, "displayNames": [{"language": "ko", "name": "브루트포스 알고리즘", "short": "브루트포스 알고리즘"}, {"language": "en", "name": "bruteforcing", "short": "bruteforce"}, {"language": "ja", "name": "全探索", "short": "全探索"}], "aliases": [{"alias": "완전탐색"}, {"alias": "완전 탐색"}, {"alias": "브루트포스"}, {"alias": "bruteforce"}, {"alias": "brute force"}, {"alias": "완탐"}]}, {"key": "simulation", "isMeta": false, "bojTagId": 141, "problemCount": 1369, "displayNames": [{"language": "ko", "name": "시뮬레이션", "short": "시뮬레이션"}, {"language": "en", "name": "simulation", "short": "simulation"}, {"language": "ja", "name": "シミュレーション", "short": "シミュレーション"}], "aliases": []}, {"key": "backtracking", "isMeta": false, "bojTagId": 5, "problemCount": 656, "displayNames": [{"language": "ko", "name": "백트래킹", "short": "백트래킹"}, {"language": "en", "name": "backtracking", "short": "backtrack"}, {"language": "ja", "name": "バックトラック法", "short": "バックトラック"}], "aliases": [{"alias": "백트래킹"}, {"alias": "퇴각검색"}, {"alias": "퇴각 검색"}]}], "metadata": {}}
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

struct Board {
    int n;
    string board; // if board contains p, actual value is 2^p or 0 if p is 0
    Board(int n) : n(n), board(n * n, 0) {}
    inline char &at(int r, int c) {
        return board[r * n + c];
    }
    Board rotCCW() {
        Board res(n);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                res.at(n-c-1, r) = at(r, c);
            }
        }
        return res;
    }
    Board rotCW() {
        Board res(n);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                res.at(c, n-1-r) = at(r, c);
            }
        }
        return res;
    }
    Board rotFlip() {
        return rotCW().rotCW();
    }
    Board swipe() {
        Board res(n);
        for (int r = 0; r < n; ++r) {
            int t = 0;
            for (int c = 0; c < n; ++c) {
                if (at(r, c) == 0) continue;

                if (at(r, c) == res.at(r, t)) {
                    ++res.at(r, t++);
                } else {
                    t += res.at(r, t) > 0;
                    res.at(r, t) = at(r, c);
                }
            }
        }
        return res;
    }

    inline char maxVal() {
        return *max_element(all(board));
    }

    Board &debug() {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) cout << (int)at(r, c) << " ";
            cout << "\n";
        }
        return *this;
    }
};

// return max val, min moves to get to max val
pair<char,int> dfs(Board board, int moves) {
    if (moves == 0) return {board.maxVal(), 0};
    
    static unordered_map<string, vector<char>> memo; // board, moves -> res (0 if not found)
    auto it = memo.find(board.board);
    if (it != memo.end()) {
        vector<char> &memoRow = it->second;
        if (memoRow[moves] != 0) {
            while (moves > 0 && memoRow[moves-1] == memoRow[moves]) --moves;
            return {memoRow[moves], moves};
        }
    }

    char best = board.maxVal();
    int bestMoves = 0;
    auto check = [&](Board t) {
        if (t.board == board.board) return;

        auto [res, resMoves] = dfs(t, moves - 1);
        ++resMoves;
        if (res < best || (res == best && resMoves >= bestMoves)) return;

        best = res;
        bestMoves = resMoves;
    };
    check(board.swipe());
    check(board.rotCCW().swipe().rotCW());
    check(board.rotFlip().swipe().rotFlip());
    check(board.rotCW().swipe().rotCCW());
    
    /*
    cout << moves << endl;
    board.debug();
    cout << ((int)best) << " " << bestMoves << endl;
    */
    string states[4] = { board.board, board.rotCCW().board, board.rotFlip().board, board.rotCW().board };
    for (string &s : states) {
        vector<char> &memoRow = memo[s];
        memoRow.resize(11, 0);
        for (int m = bestMoves; m <= moves; ++m) memoRow[m] = best;
    }
    return {best, bestMoves};
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    Board base(n);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int v; cin >> v;
            char p = 0;
            while (v >> (p+1)) ++p;
            base.at(r, c) = p;
        }
    }

    cout << (1 << dfs(base, 5).first) << "\n";
}
