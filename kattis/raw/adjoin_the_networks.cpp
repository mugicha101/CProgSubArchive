// 2026-07-30 03:53:38 
#include <cmath>
#include <limits>
#include <random>
#include <queue>
#include <array>
#include <thread>
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

#define MOD 1000000009
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
using lll = __int128_t;
using ulll = unsigned __int128_t;

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

#define EPS 1e-12
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);
    
    // to minimize edges added
    // equivalent to adding disjoint tree - 1 edges
    // optimal to connect at the center of each tree (find center dist by topo traversal)
    // width of tree: max dist (in edges) from center of tree
    // optimal to connect all nodes to a single tree so everything is <= 2 hops
    // max distance between nodes within tree a: diameter(a)
    // max distance between nodes in leaf tree a to center tree c: width(a) + width(c) + 1
    // max distance between nodes in non-adjacent trees a, b with center tree being c: width(a) + width(b) + 2
    // for each center, let S be the set of non-center tree widths
    // then max distance between nodes is max(max(S) + width(c) + 1, max(S) + max(S - max(S)) + 2, max diameter)
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    int k = n - m; // number of disjoint trees
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> tree(n, -1);
    vector<int> deg(n);
    vector<int> width(k, -1);
    for (int i = 0; i < n; ++i) deg[i] = adj[i].size();

    int nextTree = -1;
    int maxDiameter = 0;
    for (int i = 0; i < n; ++i) {
        if (tree[i] != -1) continue;
        
        // find nodes in tree and find max distance node from i
        tree[i] = ++nextTree;
        if (adj[i].size() == 0) {
            width[nextTree] = 0;
            continue;
        }
        vector<int> nodes;
        nodes.push_back(i);
        queue<int> q;
        for (int j = 0; j < (int)nodes.size(); ++j) {
            int curr = nodes[j];
            if (adj[curr].size() == 1) {
                q.push(curr);
            }
            for (int next : adj[curr]) {
                if (tree[next] != -1) continue;
                
                tree[next] = nextTree;
                nodes.push_back(next);
            }
        }

        // find width of tree
        int lastSize = 0;
        while (!q.empty()) {
            ++width[nextTree];
            lastSize = q.size();
            for (int qi = q.size(); qi > 0; --qi) {
                int curr = q.front();
                q.pop();
                for (int next : adj[curr]) {
                    if (deg[next] != 1 && --deg[next] == 1) {
                        q.push(next);
                    }
                }
            }
        }
        width[nextTree] += lastSize > 1;

        // find diameter of tree
        for (int x : nodes) deg[x] = 1;
        q.push(nodes.back());
        deg[nodes.back()] = 0;
        int d = -1;
        while (!q.empty()) {
            ++d;
            for (int qi = q.size(); qi > 0; --qi) {
                int curr = q.front();
                q.pop();
                for (int next : adj[curr]) {
                    if (deg[next] == 0) continue;
                    deg[next] = 0;
                    q.push(next);
                }
            }
        }
        // cout << "width=" << width[nextTree] << " diameter=" << d << endl;
        maxDiameter = max(maxDiameter, d);
    }

    if (k == 1) {
        cout << maxDiameter << endl;
        return 0;
    }
    if (k == 2) {
        cout << max(maxDiameter, width[0] + width[1] + 1) << endl;
        return 0;
    }

    // for (int x : width) cout << x << " ";
    // cout << endl;
    multiset<int> ws;
    for (int w : width) ws.insert(w);
    int res = INT_MAX;
    for (int i = 0; i < k; ++i) {
        ws.erase(ws.find(width[i]));
        auto it = --ws.end();
        int a = *it;
        it--;
        int b = *it;
        ws.insert(width[i]);

        res = min(res, max({maxDiameter, a + b + 2, a + width[i] + 1}));
    }
    cout << res << endl;
}
