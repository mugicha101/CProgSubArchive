// 2025-11-10 01:44:21 
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000009
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

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

#define EPS 1e-9
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

inline void madd(int &x, int v) {
    x += v;
    x = x >= MOD ? x - MOD : x;
}

int main() {
    cin.tie()->sync_with_stdio(0);
    cout << fixed << setprecision(12);

    int n, m, k; cin >> n >> m >> k;
    const int OUT = 1;
    const int INC = 2;
    vector<vector<pair<int,char>>> adj(n); // dst, dir
    vector<int> deg(n);
    auto findEdge = [&](int i, int j) -> pair<int,char> & {
        auto &a = adj[i];
        int lo = 0;
        int hi = (int)a.size()-1;
        while (lo != hi) {
            int m = (lo + hi) >> 1;
            if (a[m].first < j) lo = m+1;
            else hi = m;
        }
        assert(a[lo].first == j);
        return a[lo];
    };
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].emplace_back(b, 0);
        adj[b].emplace_back(a, 0);
        ++deg[a]; ++deg[b];
    }
    for (auto &a : adj) sort(a.begin(), a.end());
    
    // find node with k unknown edges, assign all to incoming edges
    vector<int> order;
    order.reserve(n);
    for (int i = 0; i < n; ++i) if (deg[i] <= k) order.push_back(i);
    for (int i = 0; i < n; ++i) {
        assert((int)order.size() > i);
        int curr = order[i];
        // cout << curr << endl;
        for (auto &[next, d] : adj[curr]) {
            if (d) continue;

            d = INC;
            findEdge(next, curr).second = OUT;
            // cout << next << " -> " << curr << endl;
            if (--deg[next] == k) order.push_back(next);
        }
    }
    // cout << "COLOR" << endl;

    // reverse the order to assign colors since guaranteed at most k neighbors at time of visit
    vector<int> color(n);
    vector<int> t(n);
    for (int i = n-1; i >= 0; --i) {
        int curr = order[i];
        // cout << curr << endl;
        int nc = 0;
        for (auto [next, d] : adj[curr]) {
            if (color[next] == 0) continue;
            t[nc++] = color[next];
        }
        sort(t.begin(), t.begin() + nc);
        color[curr] = 1;
        for (int j = 0; j < nc; ++j) {
            // cout << t[j] << " ";
            color[curr] += t[j] == color[curr];
        }
        // cout << endl;
        // cout << curr << " " << color[curr] << endl;
        assert(color[curr] <= k+1);
    }
    for (int x : color) cout << x << " ";
    cout << "\n";
}
