// 2026-08-11 16:20:36 
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
template<typename A, typename B> istream& operator>>(istream &is, pair<A, B> &p) { return is >> p.first >> p.second; }
template<typename T> istream& operator>>(istream &is, vector<T> &v) {
    for (auto &x : v) {
        is >> x;
    }
    return is;
}

template <typename... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t) {
    os << "(";
    apply([&os](const auto&... args) {
        size_t n = 0;
        ((os << (n++ ? ", " : "") << args), ...);
    }, t);
    return os << ")";
}

template <typename... Args>
istream& operator>>(istream& is, tuple<Args...>& t) {
    apply([&is](auto&... args) {
        ((is >> args), ...);
    }, t);
    return is;
}

template <typename T, size_t N>
ostream& operator<<(ostream& os, const array<T, N>& a) {
    os << "[";
    for (size_t i = 0; i < N; ++i) { 
        os << a[i]; 
        if (i != N - 1) 
            os << ", "; 
    }
    os << "]";
    return os;
}

template <typename T, size_t N>
istream& operator>>(istream& is, array<T, N> &a) {
    for (auto &x : a) {
        is >> x;
    }
    return is;
}

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-12
#define each(i, x) for (auto &i : x)
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    int n, m; cin >> n >> m;
    
    // switch - light pair only valid if light on == switch on for all photos
    // for each switch, store map X of valid lights
    // given photo p
    // X[s] &= p.switches[s]... == p.lights
    // X[s] &= ~p.switches[s]... ^ p.lights
    vector<bitset<1000>> switches(m);
    vector<bitset<1000>> lights(m);
    array<bitset<1000>,2> masks;
    for (int i = 0; i < n; ++i) masks[1][i] = true;
    vector<bitset<1000>> x(n, masks[1]);
    for (int i = 0; i < m; ++i) {
        string s, l; cin >> s >> l;
        for (int j = 0; j < n; ++j) {
            switches[i][j] = s[j] == '1';
            lights[i][j] = l[j] == '1';
        }
        for (int si = 0; si < n; ++si) {
            x[si] &= masks[!switches[i][si]] ^ lights[i];
        }
    }

    // observation: for a valid pair (s in switches, l in lights), if (s', l) is a valid pair, then s and s' have same valid pair set
    // likewise for l' and l
    // thus for each switch -> light mask, we find the number of switches with this light mask
    // 1:1 mapping only possible if num switches == num lights (so solution is 0 in these cases)
    // number of 1:1 mappings in this component is number of permutations
    // product of ways in each component is solution since components are disjoint
    vector<int> firstLightComp(n, -1);
    vector<int> switchComp(n);
    vector<int> compNumSwitches(n);
    for (int i = 0; i < n; ++i) {
        bitset<1000> y = x[i];
        if (y.count() == 0) {
            cout << 0 << "\n";
            return 0;
        }
        int f = 0;
        while (!y[f]) ++f;

        if (firstLightComp[f] == -1) {
            firstLightComp[f] = i;
            switchComp[i] = i;
        } else {
            switchComp[i] = firstLightComp[f];
        }
        ++compNumSwitches[switchComp[i]];
    }

    ll ways = 1;
    for (int i = 0; i < n; ++i) {
        if (switchComp[i] != i) continue;

        int ns = compNumSwitches[i];
        int nl = x[i].count();
        if (ns != nl) {
            cout << 0 << "\n";
            return 0;
        }

        for (ll x = 2; x <= ns; ++x) {
            ways = (ways * x) % 1000003;
        }
    }
    cout << ways << "\n";
}
