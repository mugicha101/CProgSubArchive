#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // toposort ordering
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> indeg(n);
    while (m--) {
        int l; cin >> l;
        int a; cin >> a; --a;
        while (--l) {
            int b; cin >> b; --b;
            adj[a].push_back(b);
            ++indeg[b];
            a = b;
        }
    }

    vector<int> topo;
    topo.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0) topo.push_back(i);
    }

    for (int i = 0; i < (int)topo.size(); ++i) {
        for (int next : adj[topo[i]]) {
            if (--indeg[next]) continue;

            topo.push_back(next);
        }
    }
    if ((int)topo.size() < n) {
        cout << "0\n";
        return 0;
    }

    for (int x : topo) cout << x+1 << "\n";
}
