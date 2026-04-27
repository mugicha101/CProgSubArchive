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

struct LCATree {
    vector<vector<int>> children;
    vector<int> parent;
    vector<int> depth;
    vector<int> lift;
    LCATree(vector<vector<int>> &adj, int root = 0) : children(adj.size()), parent(adj.size()), depth(adj.size()), lift(adj.size()) {
        vector<int> anc;
        lift[root] = root;
        build(adj, anc, root);
    }

    void build(vector<vector<int>> &adj, vector<int> &anc, int curr) {
        depth[curr] = (int)anc.size();
        anc.push_back(curr);
        int jump = anc[(int)anc.size() - ((depth[curr] + 1) & (-depth[curr] - 1))];
        for (int next : adj[curr]) {
            if (next == parent[curr]) continue;

            children[curr].push_back(next);
            parent[next] = curr;
            lift[next] = jump;
            build(adj, anc, next);
        }
        anc.pop_back();
    }

    int lca(int a, int b) {
        if (depth[a] > depth[b]) swap(a, b);
        while (depth[b] > depth[a]) {
            b = depth[lift[b]] >= depth[a] ? lift[b] : parent[b];
        }
        while (a != b) {
            bool skip = lift[a] != lift[b];
            a = skip ? lift[a] : parent[a];
            b = skip ? lift[b] : parent[b];
        }
        return a;
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    LCATree lcaTree(adj);
    int m; cin >> m;
    while (m--) {
        int a, b; cin >> a >> b; --a; --b;
        cout << lcaTree.lca(a, b) + 1 << "\n";
    }
}
