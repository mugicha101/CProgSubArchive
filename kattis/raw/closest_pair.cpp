// 2026-08-26 19:13:47 
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
using u128 = __uint128_t;

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

ostream& operator<<(ostream& os, i128 x) {
    if (x < 0) {
        x = -x;
        os << '-';
    }
    static char s[40];
    int i = 0;
    while (x) {
        s[i++] = '0' + x % 10;
        x /= 10;
    }
    if (i == 0) s[i++] = '0';
    while (i) os << s[--i];
    return os;
}

istream& operator>>(istream& is, i128 &x) {
    static string s; is >> s;
    x = 0;
    bool neg = s[0] == '-';
    for (int i = 0; i < s.size(); ++i) {
        x = x * 10 + (s[i] - '0');
    }
    if (neg) x = -x;
    return is;
}

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-12
#define each(i, x) for (auto &i : x)
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

struct UnionFind {
    vector<int> uf;
    vector<int> rank;
    int comps;
    UnionFind(int size) : uf(size), rank(size), comps(size) {
        iota(uf.begin(), uf.end(), 0);
    }

    int find(int x) {
        if (uf[x] != x) uf[x] = find(uf[x]);
        return uf[x];
    }

    bool merge(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) return false;

        --comps;
        if (ra > rb) {
            uf[rb] = ra;
        } else {
            uf[ra] = rb;
            rank[rb] += rank[ra] == rank[rb];
        }
        return true;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);   
    
    while (true) {
        int n = 0;
        cin >> n;
        if (n == 0) break;

        vector<pair<ll,ll>> pts(n);
        for (auto &[x,y] : pts) {
            ld fx, fy; cin >> fx >> fy;
            x = (int)round(fx * 100);
            y = (int)round(fy * 100);
        }
        sort(all(pts));

        // spatial hashing only works with tiles of same distance size
        // sweepline: when ordered by x, can only consider points whos dx^2 <= best squared dist
        // get initial guess through random sampling
        ll res = LLONG_MAX;
        ll cap = LLONG_MAX;
        int resA = -1, resB = -1;
        auto check = [&](int i, int j) {
            ll dx = pts[i].first - pts[j].first;
            ll dy = pts[i].second - pts[j].second;
            ll d = dx * dx + dy * dy;
            if (d >= res) return;
            
            resA = i;
            resB = j;
            res = d;
            cap = (int)sqrt((ld)res);
        };
        srand(time(NULL));
        for (int l = 0; l < 1000; ++l) {
            int i = rand() % n;
            int j = rand() % (n-1);
            j += j >= i;
            check(i, j);
        }
        set<pair<int,int>> w; // (y, idx)
        int j = 0;
        for (int i = 0; i < n; ++i) {
            while (pts[i].first - pts[j].first > cap) {
                w.erase(make_pair(pts[j].second, j));
                ++j;
            }
            auto it = w.lower_bound(make_pair(pts[i].second - cap, -1));
            while (it != w.end() && abs(pts[it->second].second - pts[i].second) <= cap) {
                check(i, it->second);
                ++it;
            }
            w.emplace(pts[i].second, i);
        }

        auto printHelper = [](ll v) {
            string sign = v < 0 ? "-" : "";
            v = abs(v);
            string r = to_string(v % 100);
            r = string(2-r.size(), '0') + r;
            return sign + to_string(v / 100) + "." + r;
        };
        
        cout << printHelper(pts[resA].first) << " " << printHelper(pts[resA].second) << " " << printHelper(pts[resB].first) << " " << printHelper(pts[resB].second) << "\n";
    }
}
