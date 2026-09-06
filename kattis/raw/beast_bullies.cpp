// 2026-08-07 22:14:19 
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

    // always a suffix of the sorted strengths of animals remaining
    int n; cin >> n;
    vector<ll> a(n); vcin(a); sort(all(a)); reverse(all(a));

    // animal should defend weakest to avoid state where it is removed
    // 2 animals: 0 should attack, 1 should defend, never a stalemate (0 always wins)
    // 3 animals: 0 should attack, 1 should defend, 2 should defend, stalemate if 0 not more powerful than 1 + 2
    // if state with k animals results in stalemate, all animals in it should attack for remaining states
    // remaining animals should avoid
    // this results in strongest k animals attacking and rest defending
    int attackers = 1;
    int res = 1;
    ll attackPower = a[0];
    ll defendPower = 0;
    for (int i = 1; i < a.size(); ++i) {
        defendPower += a[i];
        if (attackPower > defendPower) continue;

        res = i + 1;
        while (attackers < i + 1) {
            attackPower += a[attackers];
            defendPower -= a[attackers];
            ++attackers;
        }
    }
    cout << res << endl;
}
