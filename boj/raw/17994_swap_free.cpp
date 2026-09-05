#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
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

    // given set of anagrams, can rep anagrams as nodes and swaps as edges in graph
    // need to find largest set of non-adjacent nodes
    int n; cin >> n;
    vector<string> arr(n);
    for (string &s : arr) {
        cin >> s;
    }
    int k = arr[0].size();
    
    // first form edges
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        const string &a = arr[i];
        for (int j = i+1; j < n; ++j) {
            const string &b = arr[j];

            // check if swappable
            int t = 0;
            int s = -1;
            for (int l = 0; t < 3 && l < k; ++l) {
                if (a[l] == b[l]) continue;

                if (++t == 1) {
                    s = l;
                } else {
                    t += !(b[l] == a[s] && a[l] == b[s]);
                }
            }
            if (t != 2) continue;

            // if swappable, add edge
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }

    // due to nature of the graph, if x adjacent to y and y adjacent to z, x not adjacent to z
    // this means graph is bipartite V, U
    // |maximum independent set| = n - |min vertex cover on bipartite graph| = n - |maximum matching (via konig's theorem)| = n - max flow from U to V
    // first color the nodes
    vector<int> color(n, -1); // color
    queue<int> q;
    for (int root = 0; root < n; ++root) {
        if (color[root] != -1) continue;

        color[root] = 0;
        q.push(root);
        int c = 0;
        while (!q.empty()) {
            c = 1 - c;
            for (int qi = (int)q.size(); qi > 0; --qi) {
                int curr = q.front();
                q.pop();
                for (int next : adj[curr]) {
                    if (color[next] != -1) {
                        if (color[next] != c) return {};
                        continue;
                    }

                    color[next] = c;
                    q.push(next);
                }
            }
        }
    }

    // construct flow graph
    // src: n -> all nodes colored 0
    // sink: all nodes colored 1 -> n+1
    Dinic mf(n+2);
    for (int i = 0; i < n; ++i) {
        if (color[i]) {
            mf.addEdge(i, n+1, 1);
            continue;
        }
        mf.addEdge(n, i, 1);

        for (int j : adj[i]) {
            assert(color[j] == 1);

            mf.addEdge(i, j, 1);
        }
    }
    int f = (int)mf.calc(n, n+1);
    cout << n - f << endl;
}
