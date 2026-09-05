#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

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
    
    int tc; cin >> tc;
    while (tc--) {
        int rows, cols;
        bool grid[80][80];
        cin >> rows >> cols;
        for (int r = 0; r < rows; ++r) {
            string s; cin >> s;
            for (int c = 0; c < cols; ++c) {
                grid[r][c] = s[c] == 'x';
            }
        }

        // n * m <= 6400
        // naive dp: dp[i][m][nm] = max seats starting from ith row with prev row as mask m and current row as mask nm
        // can either add seat to current row or move to next row
        // states: 2^80 * 2^80 * 80 - way too large
        // identify all locations where seat is placeable, represent as set
        // each seat only depends on seats on opposite column parity (left, up/left, right, up/right)
        // can model this as a bipartite graph with edges between neighboring tiles, and solution reduces to maximum independent sets
        // by konigs, max independent sets = n - |max bipartite matching|
        // max bipartite matching can be done using max flow (since edges in remaining set = nodes)
        // edge from src -> all in U (cap 1)
        // original edges from U -> V (cap 1)
        // edge from all in V -> dst (cap 1)

        // construct graph
        vector<set<int>> adj(80 * 80);
        int amt = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c]) continue;
                ++amt;

                auto check = [&](int nr, int nc) {
                    if (grid[nr][nc]) return;
                    int a = r * 80 + c;
                    int b = nr * 80 + nc;
                    adj[a].insert(b);
                    adj[b].insert(a);
                };

                if (c) {
                    check(r, c-1);
                    if (r) check(r-1, c-1);
                }
                if (c+1 < cols) {
                    check(r, c+1);
                    if (r) check(r-1, c+1);
                }
            }
        }

        // max flow
        Dinic f(80 * 80 + 2); // tile r, c maps to node r * 80 + c, src = 80 * 80, dst = 80 * 80 + 1
        int src = 80 * 80;
        int dst = src + 1;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c]) continue;
                
                int i = r * 80 + c;
                if (c & 1) {
                    f.addEdge(src, i, 1);
                    for (int j : adj[i]) {
                        f.addEdge(i, j, 1);
                    }
                } else {
                    f.addEdge(i, dst, 1);
                }
            }
        }
        int res = amt - f.calc(src, dst);
        cout << res << "\n";
    }
}
