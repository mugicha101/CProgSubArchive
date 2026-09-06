// 2026-08-19 00:16:21 
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

    ll n, totalTime; cin >> n >> totalTime;
    ll a, b, c, t0; cin >> a >> b >> c >> t0;

    // n <= 10^9
    // t <= 10^18
    // 1 <= a, b, c <= 10^6
    // 1 <= t0 <= c
    // t(i) = ((a * t(i-1) + b) % c) + 1
    // worst case: a=1,b=1,c=1 so t(i) = 1
    // so can't just iterate over all problems
    // notice that problem times are cyclic dependent on t(i-1) on group {1,2,...,c}
    // since c <= 10^6, cyclic group at most 10^6 large, so iterating over all problem times possible
    // if we know the cyclic group, we can figure out the number of each problem that exists
    // from this we sort by time required and greedily solve

    // form group
    vector<int> g(1, t0);
    int cycleStart = -1;
    unordered_map<int,int> seen;
    seen[t0] = 0;
    while (true) {
        ll ti = ((a * (ll)g.back() + b) % c) + 1;
        auto it = seen.find(ti);
        if (it != seen.end()) {
            cycleStart = it->second;
            break;
        }

        seen[ti] = (int)g.size();
        g.push_back(ti);
    }

    // calc occurances of ith element in group (0 indexed)
    int gn = g.size();
    int cnt = (n - cycleStart) / (gn - cycleStart);
    int ext = (n - cycleStart) % (gn - cycleStart);
    auto getOccs = [&](int i) {
        return i < cycleStart ? 1 : cnt + (int)(i - cycleStart < ext);
    };
    
    // order elements in group by increasing time to determine solve order
    vector<int> order(gn);
    iota(all(order), 0);
    sort(all(order), [&](int i, int j) {
        return g[i] < g[j];
    });

    // greedily solve in increasing time order
    ll solves = 0;
    ll time = 0;
    ll penalty = 0;
    const i128 M = 1000000007;
    for (int i : order) {
        i128 probTime = g[i];
        i128 remTime = totalTime - time;
        if (probTime > remTime) break;

        i128 probCnt = getOccs(i);
        if (probCnt == 0) continue;

        i128 probSolves = min(probCnt, remTime / probTime);
        solves += probSolves;

        // penalty added
        // = sum(time + k * probTime for k=1 to probSolves)
        // = time * probSolves + probTime * sum(k for k=1 to probSolves)
        // = time * probSolves + probTime * (1 + probSolves) * probSolves / 2
        penalty = ((i128)penalty + (i128)time * (i128)probSolves + (((i128)probTime * (i128)(1 + probSolves) * (i128)probSolves) >> 1)) % M;
        time += probSolves * probTime;
    }
    cout << solves << " " << penalty << "\n";
}
