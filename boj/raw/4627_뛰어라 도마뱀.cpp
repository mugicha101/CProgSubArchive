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

    // flow represents lizards path
    // pillar split in 2: in_{r,c} -(k)-> out_{r,c} where k is number of jumps left (flow represents lizard jumping off this pillar)
    // out_{r,c} leads to all reachable in_{jr,jc} pillars and dst if in range of safety (flow = k of r,c)
    // src -(1)-> pillar with lizard to represent lizard start

    // serialization:
    // in_{r,c}: (r*cols + c) * 2
    // out_{r,c}: (r*cols + c) * 2 + 1
    // src: rows*cols*2
    // dst: src+1
    int tc; cin >> tc;
    for (int tci = 1; tci <= tc; ++tci) {
        int rows, d; cin >> rows >> d;
        vector<string> pil(rows); vcin(pil);
        vector<string> liz(rows); vcin(liz);
        int cols = pil[0].size();

        auto id = [&](int r, int c) {
            return (r * cols + c) * 2;
        };
        int src = rows * cols * 2;
        int dst = src + 1;
        int numLiz = 0;
        PushRelabel f(dst+1);
        // cout << rows << " " << cols << endl;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                int in = id(r,c);
                int out = in+1;
                int dur = pil[r][c] - '0';
                if (dur == 0) continue;
                
                f.addEdge(in, out, dur);

                // check if lizard on pillar
                if (liz[r][c] == 'L') {
                    ++numLiz;
                    f.addEdge(src, in, 1);
                }

                // check if can reach edge (if so always optimal to take)
                if (r-d < 0 || c-d < 0 || r+d >= rows || c+d >= cols) {
                    f.addEdge(out, dst, dur);
                    continue;
                }

                // transitions to other pillars
                for (int jr = 0; jr < rows; ++jr) {
                    for (int jc = 0; jc < cols; ++jc) {
                        if (r == jr && c == jc) continue;
                        if (abs(jr-r) + abs(jc-c) > d) continue;
                        f.addEdge(out, id(jr,jc), dur);
                    }
                }
            }
        }
        cout << "Case #" << tci << ": ";
        int dead = numLiz - f.calc(src, dst);
        if (dead) {
            cout << dead;
        } else {
            cout << "no";
        }
        cout << " lizard";
        if (dead <= 1) {
            cout << " was";
        } else {
            cout << "s were";
        }
        cout << " left behind.\n";
        // for (auto &r : liz) cout << r << "\n";
        // for (int i = 0; i < rows*cols*2; ++i) {
        //     int sr = (i/2) / cols;
        //     int sc = (i/2) % cols;
        //     for (auto &e : f.g[i]) {
        //         if (e.f <= 0) continue;

        //         int j = e.dest;
        //         int dr = (j/2) / cols;
        //         int dc = (j/2) % cols;
        //         cout << "(" << sr << "," << sc << ") -(" << e.f << ")-> (" << dr << "," << dc << ")\n";
        //     }
        // }
    }
}
