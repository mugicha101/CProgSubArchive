#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;

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

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

#include <bits/stdc++.h>
using namespace std;

vector<int> val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int tarjans_dfs(int j, G& g, F& f) {
  int low = val[j] = ++Time, x; z.push_back(j);
  for (auto e : g[j]) if (comp[e] < 0)
    low = min(low, val[e] ?: tarjans_dfs(e,g,f));

  if (low == val[j]) {
    do {
      x = z.back(); z.pop_back();
      comp[x] = ncomps;
      cont.push_back(x);
    } while (x != j);
    f(cont); cont.clear();
    ncomps++;
  }
  return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
  int n = g.size();
  val.assign(n, 0); comp.assign(n, -1);
  Time = ncomps = 0;
  for (int i = 0; i < n; ++i) if (comp[i] < 0) tarjans_dfs(i, g, f);
}

struct TarjansRes {
    vector<int> ll;
    vector<int> id;
    vector<vector<int>> sccs;
    int nextId = 0;
    TarjansRes(vector<vector<int>> &adj) : ll(adj.size()), id(adj.size(), -1) {
        vector<int> stackPrev(adj.size(), -1);
        for (int i = 0; i < (int)adj.size(); ++i) {
            if (id[i] != -1) continue;

            stackPrev[i] = i;
            int stackBack = i;
            dfs(adj, stackPrev, stackBack, i);
        }

        unordered_map<int,int> sccId;
        for (int i = 0; i < (int)adj.size(); ++i) {
            if (ll[i] != id[i]) continue;
            
            sccId[id[i]] = sccId.size();
        }
        sccs.resize(sccId.size());
        for (int i = 0; i < (int)adj.size(); ++i) {
            sccs[sccId[ll[i]]].push_back(i);
        }
        sort(all(sccs), [](vector<int> &a, vector<int> &b) {
            return a[0] < b[0];
        });
    }

    void dfs(vector<vector<int>> &adj, vector<int> &stackPrev, int &stackBack, int curr) {
        id[curr] = nextId;
        ll[curr] = nextId;
        ++nextId;
        
        for (int next : adj[curr]) {
            if (id[next] == -1) {
                stackPrev[next] = curr;
                stackBack = next;
                dfs(adj, stackPrev, stackBack, next);
                ll[curr] = min(ll[curr], ll[next]);
            } else if (stackPrev[next] != -1) {
                ll[curr] = min(ll[curr], ll[next]);
            }
        }
        if (ll[curr] != id[curr]) return;
        
        while (stackBack != curr) {
            int temp = stackBack;
            ll[temp] = id[curr];
            stackBack = stackPrev[stackBack];
            stackPrev[temp] = -1;
        }
        stackBack = stackPrev[stackBack];
        stackPrev[curr] = -1;
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);
    
    // input
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    while (m--) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].push_back(b);
    }

    // tarjans
    /*
    TarjansRes res(adj);
    cout << res.sccs.size() << "\n";
    for (auto &scc : res.sccs) {
        for (int x : scc) cout << x+1 << " ";
        cout << -1 << "\n";
    }
    */
    vector<vector<int>> sccs;
    scc(adj, [&](vector<int> &comp) {
        sccs.push_back(comp);
        sort(all(sccs.back()));
    });
    sort(sccs.begin(), sccs.end(), [](auto &a, auto &b) {
        return a[0] < b[0];
    });
    cout << sccs.size() << "\n";
    for (auto &s : sccs) {
        for (int x : s) cout << x+1 << " ";
        cout << -1 << "\n";
    }
}