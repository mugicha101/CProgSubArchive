// 2026-08-01 15:08:17 
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
using lll = __int128_t;
using ulll = unsigned __int128_t;

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

ll closestDiff(multiset<ll> &s, ll t) {
    if (s.empty()) return LLONG_MAX; // no values to compare against
    auto l = s.lower_bound(t); // first val >= t
    if (l == s.end()) return abs(*prev(l) - t); // no val >= t, must be last value < t
    if (l == s.begin()) return abs(*l - t); // no val < t, must be first value >= t
    return min(abs(*l - t), abs(*prev(l) - t)); // both val < t and val >= t exist, pick min
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    ll n, k, x; cin >> n >> k >> x;
    vector<ll> vals(n); vcin(vals);
    
    // want sum of up to k values to be as close as possible to sum(arr) - x * (n-k) (<= 1.5 * 10^12)
    ll s = accumulate(all(vals), 0LL);

    // construct all pairs left and right then 2sum: O(n^3 lg(n^2)) (still too high)
    // don't actually need to consider all pairs each iteration, just new left ones matching with closest to right
    // don't even need to store left ones
    // O(n^2 lg(n^2))

    // edge case: k < 4
    // k=1: trivial
    // k=2: 2sum
    // k=3: match left pairs with right singles

    ld bestDbl = (ld)abs(s - x * n) / (ld)n; // k = 0

    // k = 1
    if (k >= 1) {
        ll t = s - x * (n-1);
        // cout << 1 << " " << t << endl;
        // pause();
        ll best = LLONG_MAX;
        for (int i = 0; i < n; ++i) {
            best = min(best, abs(vals[i] - t));
        }
        if (best != LLONG_MAX) bestDbl = min(bestDbl, (ld)best / (ld)(n-1));
    }

    // k = 2
    if (k >= 2) {
        ll t = s - x * (n-2);
        // cout << 2 << " " << t << endl;
        // pause();
        ll best = LLONG_MAX;
        multiset<ll> left;
        for (ll v : vals) {
            best = min(best, closestDiff(left, t - v));
            left.insert(v);
        }
        if (best != LLONG_MAX) bestDbl = min(bestDbl, (ld)best / (ld)(n-2));
    }

    // k = 3
    if (k >= 3) {
        ll t = s - x * (n-3);
        // cout << 3 << " " << t << endl;
        // pause();
        ll best = LLONG_MAX;
        multiset<ll> right;
        for (ll v : vals) right.insert(v);
        for (int i = 0; i < n; ++i) {
            right.erase(right.find(vals[i]));
            for (int j = 0; j < i; ++j) {
                best = min(best, closestDiff(right, t - (vals[i] + vals[j])));
            }
        }
        if (best != LLONG_MAX) bestDbl = min(bestDbl, (ld)best / (ld)(n-3));
    }

    // k = 4
    if (k >= 4) {
        ll t = s - x * (n-4);
        // cout << 4 << " " << t << endl;
        // pause();
        ll best = LLONG_MAX;
        multiset<ll> right;
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                right.insert(vals[i] + vals[j]);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                right.erase(right.find(vals[i] + vals[j]));
            }
            for (int j = 0; j < i; ++j) {
                best = min(best, closestDiff(right, t - (vals[i] + vals[j])));
            }
        }
        if (best != LLONG_MAX) bestDbl = min(bestDbl, (ld)best / (ld)(n-4));
    }

    cout << bestDbl << endl;
}
