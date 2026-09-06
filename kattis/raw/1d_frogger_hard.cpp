// 2026-08-19 02:05:43 
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

struct node {
    int val; // jump value
    int next; // node frog jumps to from this node (-1 if falls off board)
    vector<int> prev; // nodes from jumps from to this node
    int id; // tree root if in inverse tree, -(cycle root)-1 if in cycle, n if not seen
    set<int> cycleMs; // if cycle root, stores cycle ms, empty otherwise
    int cycleSize; // if cycle root, stores cycle size, 0 otherwise
};

ostream& operator<<(ostream &os, const node &x) {
    os << "{val=" << x.val << ",next=" << x.next << ",prev=" << x.prev << ",id=" << x.id << "}";
    return os;
};

// traverse inverse tree and count valid (s,m) pairs for each node in inverse tree
ll dfs(const vector<node> &nodes, set<int> &mset, int curr) {
    bool dup = mset.count(nodes[curr].val);
    if (!dup) mset.insert(nodes[curr].val);

    ll res = mset.size();
    for (int next : nodes[curr].prev) {
        res += dfs(nodes, mset, next);
    }

    if (!dup) mset.erase(nodes[curr].val);
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    // find number of (s,m) s.t. frog starts from s and ends at m
    // can form succession graph consisting of inverse trees and cycles
    // inverse trees leads to a cycle or dead-ends if frog falls off board
    // given s, valid (s,m) depends on cases:
    // case 1: s in inverse tree
    //     # valid m = unique ms in successors of inverse tree (including self) and in nodes of cycle
    // case 2: s in cycle
    //     # valid m = unique ms in cycle
    //     thus valid (s,m) within a cycle is (unique ms in cycle) * (size of cycle)
    
    // n <= 200,000
    int n; cin >> n;
    vector<node> nodes(n);
    // srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        cin >> nodes[i].val;
        // nodes[i].val = i - (rand() % (n+1));
        nodes[i].next = i + nodes[i].val;
        if (nodes[i].next < 0 || nodes[i].next >= n) nodes[i].next = -1;
        nodes[i].id = n;
        nodes[i].cycleSize = 0;
    }

    for (int i = 0; i < n; ++i) {
        if (nodes[i].id != n) continue;

        vector<int> chain;
        int t = i;
        while (true) {
            chain.push_back(t);
            nodes[t].id = n+1;
            int u = nodes[t].next;
            if (u == -1 || nodes[u].id != n) break; // dead end root node or found existing structure

            t = u;
        }
        int u = nodes[t].next;
        if (u == -1) { // in new dead-end inverse tree
            int r = chain.back();
            while (!chain.empty()) {
                nodes[chain.back()].id = r;
                chain.pop_back();
            }
        } else if (nodes[u].id == n+1) { // in new cycle
            // handle new cycle
            nodes[u].id = -u-1;
            nodes[u].cycleMs.insert(nodes[u].val);
            nodes[u].cycleSize = 1;
            while (chain.back() != u) {
                nodes[chain.back()].id = -u-1;
                nodes[u].cycleMs.insert(nodes[chain.back()].val);
                ++nodes[u].cycleSize;
                chain.pop_back();
            }
            chain.pop_back();

            // handle new inverse tree
            if (!chain.empty()) {
                int r = chain.back();
                while (!chain.empty()) {
                    nodes[chain.back()].id = r;
                    chain.pop_back();
                }
            }
        } else if (nodes[u].id < 0) { // in new cycle-end inverse tree
            int r = chain.back();
            while (!chain.empty()) {
                nodes[chain.back()].id = r;
                chain.pop_back();
            }
        } else { // connects to existing inverse tree
            int r = nodes[u].id;
            while (!chain.empty()) {
                nodes[chain.back()].id = r;
                chain.pop_back();
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (nodes[i].next == -1) continue;

        nodes[nodes[i].next].prev.push_back(i);
    }

    ll res = 0;
    set<int> emptyMs;
    for (int i = 0; i < n; ++i) {
        if (nodes[i].id >= 0) {
           if (nodes[i].id != i) continue; // not a tree root

            // root of inverse tree
            set<int> &mset = nodes[i].next == -1 ? emptyMs : nodes[-nodes[nodes[i].next].id-1].cycleMs;
            res += dfs(nodes, mset, i);
        } else if (nodes[i].id < 0) {
            if (-nodes[i].id-1 != i) continue; // not a cycle root
            
            // cycle
            set<int> &mset = nodes[i].cycleMs;
            res += mset.size() * nodes[i].cycleSize;
        }
    }
    cout << res << "\n";

    // brute force checker
    // ll dbres = 0;
    // for (int i = 0; i < n; ++i) {
    //     set<int> mset;
    //     set<int> seen;
    //     int t = i;
    //     while (t != -1 && seen.count(t) == 0) {
    //         seen.insert(t);
    //         mset.insert(nodes[t].val);
    //         t = nodes[t].next;
    //     }
    //     dbres += mset.size();
    // }
    // assert(dbres == res);
}
