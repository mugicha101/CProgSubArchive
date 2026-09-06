// 2026-08-09 22:17:50 
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

    int n; cin >> n;
    vector<int> a(n); cin >> a;
    vector<int> b(n); cin >> b;
    
    // horse a[i] will beat a prefix of b, this determines which cyclic offsets it wins
    // cyclic offset is right rotates
    // given a[i] beats first j in b, win range is [-i, j-i-1]
    vector<pair<int,int>> itvs;
    itvs.reserve(n*2);
    for (int i = 0; i < n; ++i) {
        int j = distance(b.begin(), upper_bound(all(b), a[i]));
        if (j == 0) continue;

        int a = (n-i) % n;
        int b = (n+j-i-1) % n;

        if (a <= b) itvs.emplace_back(a, b);
        else {
            itvs.emplace_back(a, n-1);
            itvs.emplace_back(0, b);
        }
    }
    sort(all(itvs));
    priority_queue<int, vector<int>, greater<int>> ends;
    int wins = 0;
    int next = 0;
    for (int i = 0; i < n; ++i) {
        while (next < itvs.size() && itvs[next].first == i) {
            ends.push(itvs[next].second);
            ++next;
        }
        wins += (int)ends.size() == n;
        while (!ends.empty() && ends.top() == i) ends.pop();
    }
    cout << wins << "\n";
}
