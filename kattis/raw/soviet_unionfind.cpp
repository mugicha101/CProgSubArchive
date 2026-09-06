// 2026-08-17 13:31:53 
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
using i128 = __int128_t;
using u128 = unsigned __int128_t;

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

struct UnionFind {
    vector<int> uf;
    vector<int> val;
    vector<bool> stale;
    unordered_map<int,int> vmap; // val -> index
    
    int add(int x) {
        int i = uf.size();
        uf.push_back(i);
        val.push_back(x);
        stale.push_back(false);
        vmap[x] = i;
        return i;
    }

    pair<int,bool> find(int i) {
        if (uf[i] != i) {
            auto [r,s] = find(uf[i]);
            if (s) {
                stale[i] = true;
                uf[i] = i;
                return {add(val[i]), true};
            }
            uf[i] = r;
            return {r, false};
        } else {
            return {i, stale[i]};
        }
    }

    void merge(int a, int b) {
        int ra = find(vmap[a]).first;
        int rb = find(vmap[b]).first;
        if (ra != rb) uf[rb] = ra;
    }

    void balkanize(int x) {
        int r = find(vmap[x]).first;
        stale[r] = true;
        add(val[r]);
    }

    int owner(int x) {
        return val[find(vmap[x]).first];
    }

    void dump() {
        for (int i = 0; i < (int)uf.size(); ++i) {
            cout << i+1 << " " << uf[i]+1 << " " << val[i] << " " << stale[i] << "\n";
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    // if balkanized, mark as stale and make new node for it
    // any child of it will hit the stale node as root, and should be marked as stale aswell (for subnodes) and create a new node
    // since can form component of k size with min k-1 merges, nodes affected by balkanization ammortized to number of merges
    // num nodes bounded by number of queries
    UnionFind uf;
    int n, q; cin >> n >> q;
    for (int x = 1; x <= n; ++x) uf.add(x);

    while (q--) {
        char t; cin >> t;
        if (t == 'a') {
            int x, y; cin >> x >> y;
            // cout << "ANNEX " << x << " <- " << y << "\n";
            uf.merge(x, y);
        } else if (t == 'b') {
            int x; cin >> x;
            // cout << "BALK " << x << "\n";
            uf.balkanize(x);
        } else if (t == 'c') {
            int x; cin >> x;
            // cout << "FIND " << x << "\n";
            cout << uf.owner(x) << "\n";
        } else {
            assert(false);
        }
        // uf.dump();
    }
}
