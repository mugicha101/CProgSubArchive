// 2026-08-07 03:52:58 
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

void solve() {
    // all inputs in range [1,10000]
    ll l1, a1, l2, a2, lt, at; cin >> l1 >> a1 >> l2 >> a2 >> lt >> at;

    // l1 * x + l2 * y = lt
    // a1 * x + a2 * y = at
    // [ l1 l2 ][ x ] = [ lt ]
    // [ a1 a2 ][ y ]   [ at ]
    // gauss jordan

    
    ll mat[2][3];
    mat[0][0] = l1;
    mat[0][1] = l2;
    mat[0][2] = lt;
    mat[1][0] = a1;
    mat[1][1] = a2;
    mat[1][2] = at;
    // auto dump = [&]() {
    //     for (int r = 0; r < 2; ++r) {
    //         for (int c = 0; c < 3; ++c) {
    //             cout << mat[r][c] << " ";
    //         }
    //         cout << endl;
    //     }
    // };

    // cout << "init:\n";
    // dump();
    
    ll m = lcm(mat[0][0], mat[1][0]);
    ll t[2];
    t[0] = m / mat[0][0];
    t[1] = m / mat[1][0];
    for (int i = 0; i < 3; ++i) {
        mat[0][i] *= t[0];
        mat[1][i] *= t[1];
        mat[1][i] -= mat[0][i];
    }

    // cout << "op 1:\n";
    // dump();

    if (mat[1][1] == 0) {
        // l1 * x + l2 * y = lt
        // if multiple ways to choose x, y s.t. x and y are integers, then still valid
        // we know l1, l2, lt > 0 since row 1 has not been modified
        
        ll fx = -1, fy = -1;
        l1 = mat[0][0];
        l2 = mat[0][1];
        lt = mat[0][2];
        ll lim = lt / l1;
        // cout << l1 << " " << l2 << " " << lt << endl;
        for (ll x = 1; x <= lim; ++x) {
            ll t = lt - l1 * x;
            if (t == 0 || t % l2) continue;
            ll y = t / l2;
            if (fx != -1) {
                cout << "?\n";
                return;
            }
            fx = x;
            fy = y;
        }
        if (fx == -1) {
            cout << "?\n";
            return;
        }
        cout << fx << " " << fy << "\n";
        return;
    }

    m = lcm(mat[0][1], mat[1][1]);
    t[0] = m / mat[0][1];
    t[1] = m / mat[1][1];
    for (int i = 0; i < 3; ++i) {
        mat[0][i] *= t[0];
        mat[1][i] *= t[1];
        mat[0][i] -= mat[1][i];
    }

    // cout << "op 2:\n";
    // dump();

    if (mat[0][2] == 0 || mat[1][2] == 0 || mat[0][2] % mat[0][0] || mat[1][2] % mat[1][1]) {
        cout << "?\n";
        return;
    }
    ll x = mat[0][2] / mat[0][0];
    ll y = mat[1][2] / mat[1][1];
    if (x < 0 || y < 0) {
        cout << "?\n";
        return;
    }
    cout << x << " " << y << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    int n; cin >> n;
    while (n--) {
        solve();
    }
}
