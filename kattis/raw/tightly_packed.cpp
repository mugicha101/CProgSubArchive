// 2026-08-17 14:15:51 
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

ll solve(ll n) {
    // can use any boxes of ratio at most 1:2, which actually just means 
    // l is a typo should be 1 (original ICPC pset has that)
    // assuming that only 1 box allowed since otherwise can just spam 1x1 boxes
    // n <= 10^16 so some greedy probably
    // find rectangle of at most 1:2 with min area at least n
    // can search from sqrt(x) down to find best ratio for x
    // runs in ~10^8 ops if searching all but we only need 2:1 ratio
    // x / y <= 2y
    // x <= 2y^2
    // y >= sqrt(x/2)
    // sqrt(x) - sqrt(x/2) = sqrt(x)(1 - sqrt(0.5)) <= 0.3 * sqrt(x) <= 0.3 * 10^8 = 3 * 10^7
    // TLE

    // instead of trying all x >= y, try all w <= sqrt(n) and find corresponding h, candidate if h <= 2w
    ll best = LLONG_MAX;
    for (ll w = 1; w * w <= n; ++w) {
        ll h = (n + w - 1) / w;
        if (h > w * 2) continue;

        best = min(best, w * h - n);
    }
    return best;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    ll n; cin >> n;
    cout << solve(n) << "\n";
}
