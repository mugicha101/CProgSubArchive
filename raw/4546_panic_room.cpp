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
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // let (u, v) be a door between room u and room v where u has the control panel
    // use min cut on flow graph to determine cost to split room u from any intruder
    // src -(INF)-> any room with intruder
    // u -(INF)-> v since cannot block u from entering v with a lock
    // v -(1)-> u since can lock u's control panel to prevent access from v
    // dst = panic room
    // INF can be set to 100n > max number of edges
    // if flow is INF then cannot block intruders
    // otherwise flow matches min cut with that being min number of locks to separate all intruders from panic room
    // serialization:
    // src: n
    // room i: i
    int tc; cin >> tc;
    while (tc--) {
        int n, p; cin >> n >> p;
        PushRelabel f(n+1);
        ll inf = 100 * n;
        for (int i = 0; i < n; ++i) {
            string t; cin >> t;
            if (t == "I") f.addEdge(n, i, inf);
            int c; cin >> c;
            while (c--) {
                int j; cin >> j;
                f.addEdge(i, j, inf);
                f.addEdge(j, i, 1);
            }
        }
        ll flow = f.calc(n, p);
        if (flow >= inf) {
            cout << "PANIC ROOM BREACH\n";
        } else {
            cout << flow << "\n";
        }
    }
}
