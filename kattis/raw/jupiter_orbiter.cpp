// 2026-08-12 02:33:21 
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

struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f, c, oc;
    };
    vector<vector<Edge>> g;
    vector<ll> ec;
    vector<Edge*> cur;
    vector<vector<int>> hs; vector<int> H;
    vector<int> co;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n), co(2*n) {}

    void addEdge(int s, int t, ll cap, ll rcap=0) {
        if (s == t) return;
        assert(cap>=0);
        g[s].push_back({t, (int)g[t].size(), 0, cap, cap});
        g[t].push_back({s, (int)g[s].size()-1, 0, rcap, rcap});
    }

    void addFlow(Edge& e, ll f) {
        Edge &back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    ll calc(int s, int t) {
        int v = (int)g.size(); H[s] = v; ec[t] = 1;
        co[0] = v-1;
        for (int i = 0; i < v; ++i) cur[i] = g[i].data();
        for (Edge& e : g[s]) addFlow(e, e.c);

        for (int hi = 0;;) {
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            int u = hs[hi].back(); hs[hi].pop_back();
            while (ec[u] > 0)    // discharge u
                if (cur[u] == g[u].data() + (int)g[u].size()) {
                    H[u] = 1e9;
                    for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest]+1)
                        H[u] = H[e.dest]+1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v)
                        for (int i = 0; i < v; ++i) if (hi < H[i] && H[i] < v) --co[H[i]], H[i] = v + 1;
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
        }
    }
    bool leftOfMinCut(int a) { return H[a] >= (int)g.size(); }
    void reset() {
        for (auto &row : g) {
            for (auto &e : row) {
                e.f = 0;
                e.c = e.oc;
            }
        }
        fill(ec.begin(), ec.end(), 0);
        fill(H.begin(), H.end(), 0);
        fill(cur.begin(), cur.end(), nullptr);
        for (auto &v : hs) v.clear();
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    // n = num windows [1,30]
    // q = num fifos [1,30]
    // s = num sensors [1,100]
    int n, q, s; cin >> n >> q >> s;
    vector<ll> sq(s); // sensor -> destination fifo [0,q-1]
    for (ll &x : sq) {
        cin >> x;
        --x;
    }
    vector<ll> qcap(q); cin >> qcap; // fifo -> capacity [1,10^6]
    vector<ll> wdat(n); // window -> amount of transmitable data [1,10^6]
    ll totalData = 0;
    vector<vector<ll>> qdat(q, vector<ll>(n)); // queue, window -> data sent to queue between current window and prior window
    for (int i = 0; i < n; ++i) {
        cin >> wdat[i];
        for (int j = 0; j < s; ++j) {
            ll x; cin >> x;
            qdat[sq[j]][i] += x;
            totalData += x;
        }
    }

    // LLF doesn't work because it assumes that can always do work on task from release to deadline, but queue cannot go below 0
    // uniprocessor table driven scheduling solveable by max flow
    // can add queue state instead of just the processor state at each time interval
    // each time interval is [enqueue by window, transmission window]

    // node (Q,i,j,0): queue j size at start of interval i
    // (Q,i,j,0) -(qcap[j])-> (Q,i,j,1) ensures queue j capacity not violated
    // (SRC) -(qdat[j][i])-> (Q,i,j,0) models enqueue by window i
    // (Q,i,j,1) -(wdat[i])-> (I,i) models transmitting data from the queue during time interval i
    // (I,i) -(wdat[i])-> (SNK) limits transmission time across all queues during time interval i
    // (Q,i,j,1) -(qcap[j])-> (i,j+1,0) models carrying data over to next time interval

    // number of nodes: (n * q * 2 queue nodes) + (n interval nodes) + (2 for SRC/SNK) < 1000
    // max edge capacity: 10^6
    auto queue_node = [&](int i, int j, int k) {
        return (i * q + j) * 2 + k;
    };
    auto itv_node = [&](int i) {
        return n * q * 2 + i;
    };
    int src = n * q * 2 + n;
    int snk = src + 1;

    PushRelabel mf(snk + 1);
    for (int i = 0; i < n; ++i) {
        mf.addEdge(itv_node(i), snk, wdat[i]);
        for (int j = 0; j < q; ++j) {
            mf.addEdge(src, queue_node(i,j,0), qdat[j][i]);
            mf.addEdge(queue_node(i,j,0), queue_node(i,j,1), qcap[j]);
            mf.addEdge(queue_node(i,j,1), itv_node(i), wdat[i]);
            if (i+1 < n) mf.addEdge(queue_node(i,j,1), queue_node(i+1,j,0), qcap[j]);
        }
    }
    ll f = mf.calc(src,snk);
    cout << (f == totalData ? "possible\n" : "impossible\n");
}
