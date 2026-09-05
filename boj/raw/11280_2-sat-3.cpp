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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, m;
    cin >> n >> m;

    // implication graph
    vector<vector<int>> adj(n * 2); // vars + i = negative variant
    auto neg = [&](int i) {
        return i >= n ? i - n : i + n;
    };
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        auto trans = [&](int x) {
            return x < 0 ? neg(-x - 1) : x - 1;
        };
        a = trans(a); b = trans(b);
        
        adj[neg(a)].push_back(b);
        adj[neg(b)].push_back(a);
    }

    // scc spam to determine if neg(x) -> x && x -> neg(x) exists (not satisfiable iff this true)
    scc<vector<vector<int>>>(adj, [&](vector<int> &) {});
    for (int i = 0; i < n; ++i) {
        if (comp[i] == comp[neg(i)]) {
            cout << 0 << "\n";
            return 0;
        }
    }
    cout << 1 << "\n";
}
