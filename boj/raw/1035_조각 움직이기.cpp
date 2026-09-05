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
