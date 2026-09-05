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
