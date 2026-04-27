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


vector<vector<pair<int,int>>> adj;
vector<unsigned int> depth;
vector<int> rootDist; // dist from root
vector<int> parent;
vector<int> anc; // lca skip
vector<int> chain;

// lca tree
void tree(int curr) {
    chain.push_back(curr);
    for (auto [next, d] : adj[curr]) {
        if (next == parent[curr]) continue;

        parent[next] = curr;
        rootDist[next] = rootDist[curr] + d;
        depth[next] = depth[curr] + 1;

        // set ancestor to lsb(depth[next]) up the chain
        int lsb = depth[next] & (-depth[next]);
        anc[next] = chain[chain.size() - lsb];

        tree(next);
    }
    chain.pop_back();
}

int main() {
    // env setup
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n;
    cin >> n;
    adj.resize(n);
    for (int i = 1; i < n; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        --a; --b;
        adj[a].emplace_back(b, d);
        adj[b].emplace_back(a, d);
    }
    depth.resize(n);
    rootDist.resize(n);
    parent.resize(n);
    anc.resize(n);
    tree(0);
    int m;
    cin >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        if (depth[a] < depth[b]) swap(a, b);
        
        // align depths O(lg(n))
        int ta = a, tb = b;
        while (depth[ta] > depth[tb]) {
            ta = depth[anc[ta]] < depth[tb] ? parent[ta] : anc[ta];
        }

        // lca O(lg(n))
        while (ta != tb) {
            if (anc[ta] == anc[tb]) {
                ta = parent[ta];
                tb = parent[tb];
            } else {
                ta = anc[ta];
                tb = anc[tb];
            }
        }

        // calc dist
        int dist = rootDist[a] + rootDist[b] - rootDist[ta] * 2;
        cout << dist << endl;
    }
}
