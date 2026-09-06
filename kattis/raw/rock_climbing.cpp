// 2026-08-07 22:47:28 
#include <cmath>
#include <limits>
#include <random>
#include <queue>
#include <array>
#include <thread>
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

// using namespace __gnu_pbds;
// template <class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000009
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
using i128 = __int128_t;
using u128 = unsigned __int128_t;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
pair<T,U> operator-(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    }
    os << "]";
    return os;
}

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-12
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    int rows, cols; cin >> rows >> cols;
    rows += 2;
    cin.ignore(100, '\n');
    cin.ignore(100, '\n');
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    for (int r = 1; r+1 < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cin >> grid[r][c];
        }
        // cout << grid[r] << endl;
    }

    // bsearch on starting energy
    
    auto check = [&](int se) {
        // dijkstra doesn't work because negative values
        // use bellmanford, if negative cycle exists then need 0 energy to start
        // start with -se dist to 0,0
        // check if can reach end with <= 0 dist
        // prevent any connections resulting in positive dist
        vector<vector<int>> minDist(rows, vector<int>(cols, INT_MAX >> 1));
        minDist[rows-1][0] = -se;
        auto relax = [&]() -> bool {
            bool res = false;
            auto trans = [&](int r, int c, int nr, int nc) {
                int newDist = minDist[r][c] + grid[nr][nc];
                if (newDist >= minDist[nr][nc] || newDist > 0) return;

                res = true;
                minDist[nr][nc] = newDist;
            };
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if (r) trans(r,c,r-1,c);
                    if (c) trans(r,c,r,c-1);
                    if (r+1 < rows) trans(r,c,r+1,c);
                    if (c+1 < cols) trans(r,c,r,c+1);
                }
            }
            return res;
        };
        for (int i = (rows + 1) * cols; i >= 0; --i) {
            if (!relax()) break;
        }
        // cout << se << " " << minDist[0][0] << endl;
        return minDist[0][0] <= 0;
    };
    int lo = 0;
    int hi = 0;
    for (auto &r : grid) for (int x : r) hi += max(x,0);
    // cout << lo << " " << hi << endl;
    while (lo != hi) {
        int se = (lo + hi) >> 1;
        if (check(se)) {
            hi = se;
        } else {
            lo = se + 1;
        }
    }
    cout << lo << endl;
}
