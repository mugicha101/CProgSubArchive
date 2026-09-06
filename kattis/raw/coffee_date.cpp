// 2026-08-09 21:42:15 
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

    int n, m, a, b; cin >> n >> m >> a >> b;
    vector<vector<tuple<int,int,int,int>>> adj(n); // curr stop -> (next stop, travel time, route offset, route period)

    for (int i = 0; i < m; ++i) {
        int c, s; cin >> c >> s;
        vector<int> rs(s), rt(s-1); cin >> rs >> rt;
        int o = 0;
        for (int j = 1; j < s; ++j) {
            adj[rs[j-1]].emplace_back(rs[j], rt[j-1], o, c);
            o += rt[j-1];
        }
    }

    auto minDist = [&](int src) {
        vector<int> minTime(n, INT_MAX);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // time, stop
        pq.emplace(0, src);
        minTime[src] = 0;
        while (!pq.empty()) {
            auto [currTime, currStop] = pq.top();
            pq.pop();
            if (currTime > minTime[currStop]) continue;

            for (const auto &[nextStop, travelTime, routeOffset, routePeriod] : adj[currStop]) {
                int o = ((currTime - routeOffset) % routePeriod + routePeriod) % routePeriod;
                int waitTime = o == 0 ? 0 : routePeriod - o;
                int arrivalTime = currTime + waitTime + travelTime;
                if (arrivalTime >= minTime[nextStop]) continue;

                minTime[nextStop] = arrivalTime;
                pq.emplace(arrivalTime, nextStop);
            }
        }
        return minTime;
    };

    vector<int> amt = minDist(a);
    vector<int> bmt = minDist(b);
    int best = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (amt[i] == INT_MAX || bmt[i] == INT_MAX) continue;

        best = min(best, max(amt[i], bmt[i]));
    }
    cout << (best == INT_MAX ? "NO COFFEE FOR YOU" : to_string(best)) << "\n";
}
