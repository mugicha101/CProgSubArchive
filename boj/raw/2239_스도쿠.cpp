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
