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

#define MOD 1000000007

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

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

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f, c;
    };
    vector<vector<Edge>> g;
    vector<ll> ec;
    vector<Edge*> cur;
    vector<vector<int>> hs; vector<int> H;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}

    void addEdge(int s, int t, ll cap, ll rcap=0) {
        if (s == t) return;
        g[s].push_back({t, (int)g[t].size(), 0, cap});
        g[t].push_back({s, (int)g[s].size()-1, 0, rcap});
    }

    void addFlow(Edge& e, ll f) {
        Edge &back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    ll calc(int s, int t) {
        int v = (int)g.size(); H[s] = v; ec[t] = 1;
        vector<int> co(2*v); co[0] = v-1;
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
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // l <= 50000: length of canyon
    // w <= 50000: width of canyon
    // n <= 250: number of soldiers

    // need to kill soldier iff connected from top to bottom of canyon
    // thus need to minimize soliders killed to separate top and bottom of canyon
    // min cut max flow
    // each soldier has edge to each neighbor and top/bottom of canyon if in range
    // src: bot of canyon
    // dst: top of canyon
    // soldier i split into 2 nodes: in_i -(1)-> out_i
    // edges (i, j) represented by out_i -(INF)-> in_j
    // since out_i -> in_j has infinite capacity, can only cut in_i -> out_i of cost 1 to split graph (equal to killing soldier i)
    // thus min cost = min soldiers to kill
    // V = 2n+2 <= 502
    // E <= n(n-1) + 3n = 63000
    // push relabel: O(V^2sqrt(E)) <= 63252502 < 10^8
    // serialization: in_i = i*2, out_i = i*2+1, top = n*2, bot = n*2+1
    
    ll l, w, n; cin >> l >> w >> n;
    const ll RS = 200 * 200;
    vector<pair<ll,ll>> arr(n);
    PushRelabel f(n*2+2);
    int bot = n*2;
    int top = n*2+1;
    for (auto &[x, y] : arr) cin >> x >> y;
    for (int i = 0; i < n; ++i) {
        ll ax = arr[i].first, ay = arr[i].second;

        // inner edge
        f.addEdge(i*2, i*2+1, 1);

        // edges to overlapping soldiers
        for (int j = i+1; j < n; ++j) {
            ll bx = arr[j].first, by = arr[j].second;
            ll dx = bx - ax;
            ll dy = by - ay;
            ll ds = dx * dx + dy * dy;
            if (ds > RS) continue;

            f.addEdge(i*2+1, j*2, n+1);
            f.addEdge(j*2+1, i*2, n+1);
        }

        // edges to canyon walls
        if (ay <= 100) f.addEdge(bot, i*2, n+1);
        if (ay >= w-100) f.addEdge(i*2+1, top, n+1);
    }
    cout << f.calc(bot, top) << "\n";
}
