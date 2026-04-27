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

#include <bits/stdc++.h>

using namespace std;

vector<int> disc;
vector<int> low;
vector<bool> artic;
vector<pair<int,int>> bridges;
int nextTime = 0;

int artic_dfs(vector<vector<int>> &adj, int curr, int parent) {
    int children = 0;
    disc[curr] = low[curr] = nextTime++;

    for (int next : adj[curr]) {
        if (next == parent) continue;

        if (disc[next] != -1) {
            low[curr] = min(low[curr], disc[next]);
            continue;
        }

        ++children;
        artic_dfs(adj, next, curr);
        if (disc[curr] <= low[next]) artic[curr] = true;
        if (disc[curr] < low[next]) bridges.emplace_back(min(curr, next), max(curr, next));
        low[curr] = min(low[curr], low[next]);
    }

    return children;
}

vector<int> findArticulationPoints(vector<vector<int>> &adj, bool bridgesOnly) {
    int n = adj.size();
    low = disc = vector<int>(n, -1);
    bridges.clear();
    artic = vector<bool>(n, false);

    for (int root = 0; root < n; ++root) {
        if (disc[root] != -1) continue;

        artic[root] = artic_dfs(adj, root, -1) > 1;
    }

    if (bridgesOnly) return {};
    vector<int> res;
    for (int i = 0; i < n; ++i) if (artic[i]) res.push_back(i);
    
    return res;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<pair<int,int>> edges;
    while (m--) {
        int a, b; cin >> a >> b; --a; --b;
        if (a > b) swap(a, b);
        edges.emplace_back(a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    findArticulationPoints(adj, true);
    cout << bridges.size() << "\n";
    sort(all(bridges));
    for (auto &[a, b] : bridges) {
        cout << a+1 << " " << b+1 << "\n";
    }
}
