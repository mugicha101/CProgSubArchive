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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)


struct Dinic {
    using ll = long long;
    using vi = vector<int>;
    struct Edge {
      int to, rev;
      ll c, oc;
      ll flow() { return max(oc - c, 0LL); }  // if you need flows
    };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, ll c, ll rcap = 0) {
      adj[a].push_back({b, (int)adj[b].size(), c, c});
      adj[b].push_back({a, (int)adj[a].size() - 1, rcap, rcap});
    }
    ll dfs(int v, int t, ll f) {
      if (v == t || !f) return f;
      for (int& i = ptr[v]; i < (int)adj[v].size(); i++) {
        Edge& e = adj[v][i];
        if (lvl[e.to] == lvl[v] + 1) {
          if (ll p = dfs(e.to, t, min(f, e.c))) {
            e.c -= p, adj[e.to][e.rev].c += p;
            return p;
          }
        }
      }
      return 0;
    }
    ll calc(int s, int t) {
      ll flow = 0;
      q[0] = s;
      for (int L = 0; L < 31; ++L)
        do {  // 'int L=30' maybe faster for random data
          lvl = ptr = vi(q.size());
          int qi = 0, qe = lvl[s] = 1;
          while (qi < qe && !lvl[t]) {
            int v = q[qi++];
            for (Edge e : adj[v])
              if (!lvl[e.to] && e.c >> (30 - L))
                q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
          }
          while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
        } while (lvl[t]);
      return flow;
    }
    struct CutEdge {
      int from, to;
      ll f, c;
    };
    pair<vector<CutEdge>, vector<bool>> minCut(int s, int t) {
      calc(s, t);
      queue<int> q;
      vector<CutEdge> mc;
      vector<bool> visited(adj.size());
      visited[s] = true;
      q.push(s);
      while (!q.empty()) {
        int from = q.front();
        q.pop();
        for (Edge& e : adj[from]) {
          if (visited[e.to] ||
              (e.oc ? e.flow() == e.oc : adj[e.to][e.rev].flow() == 0))
            continue;
  
          visited[e.to] = true;
          q.push(e.to);
        }
      }
      for (int from = 0; from < (int)adj.size(); ++from) {
        for (Edge& e : adj[from]) {
          if (e.flow() && visited[from] && !visited[e.to])
            mc.push_back({from, e.to, e.flow(), e.oc});
        }
      }
      return make_pair(mc, visited);
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
  };
  

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // N employees M tasks
    // each employee can complete a subset of tasks
    // map 1 employee to each task
    // up to K employees can complete 2 tasks
    // max flow
    // src -1----------> e_i -1--> t_j -1---> dst
    //    \-k-> alt -/
    // serialization:
    // e_i: i
    // t_i: n + i
    // alt: n + m
    // src: alt + 1
    // dst: dst + 1
    int n, m, k; cin >> n >> m >> k;
    Dinic f(n + m + 3);
    int alt = n + m, src = alt + 1, dst = src + 1;
    auto eId = [&](int i) { return i; };
    auto tId = [&](int i) { return n + i; };
    f.addEdge(src, alt, k);
    for (int i = 0; i < n; ++i) {
        int a; cin >> a;
        f.addEdge(src, eId(i), 1);
        f.addEdge(alt, eId(i), 1);
        for (int j = 0; j < a; ++j) {
            int t; cin >> t; --t;
            f.addEdge(eId(i), tId(t), 1);
        }
    }
    for (int i = 0; i < m; ++i) {
        f.addEdge(tId(i), dst, 1);
    }
    cout << f.calc(src, dst) << endl;
}
