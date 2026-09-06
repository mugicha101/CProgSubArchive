// 2026-08-17 16:37:20 
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

class SegTree {
    // config
    using T = pair<int,int>; // type
    const T ZRV = {INT_MAX,-1}; // value to return if range is 0
    const T IV = {INT_MAX,-1}; // initial value of elements
    inline T op(T l, T r) const { return l.first == r.first ? max(l,r) : min(l,r); } // range query operator
    // config end

    vector<T> nodes;

    inline void asn(int i) { nodes[i] = op(nodes[left(i)], nodes[right(i)]); }
    inline int left(int i) const { return (i << 1) + 1; }
    inline int right(int i) const { return (i << 1) + 2; }
    inline int parent(int i) const { return (i - 1) >> 1; }
    inline int elem(int i) const { return (nodes.size() >> 1) + i; }
    inline bool leaf(int i) const { return i >= elem(0); }

    T query_helper(int index, int size, int first, int last) const {
        if (first >= size || last < 0) return ZRV;
        if (first <= 0 && last >= size-1) return nodes[index];
        size >>= 1;
        return op(query_helper(left(index), size, first, last), query_helper(right(index), size, first - size, last - size));
    }

    void dump_helper(int index, int indent) const {
        cout << string(indent * 2, ' ') << "(" <<  nodes[index] << ")" << endl;
        if (leaf(index)) return;
        dump_helper(left(index), indent+1);
        dump_helper(right(index), indent+1);
    }

public:

    SegTree(int size) {
        --size;
        int n = 1;
        while (size) {
            n <<= 1;
            size >>= 1;
        }
        nodes.resize(n * 2 - 1, IV);
        for (int i = n-2; i >= 0; --i) asn(i);
    }

    T get(int index) const { return nodes[elem(index)]; }
    T query(int first, int last) const { return query_helper(0, (nodes.size() + 1) >> 1, first, last); }
    void dump() const { dump_helper(0, 0); }

    void assign(int index, T value) {
        index = elem(index);
        nodes[index] = value;
        while (index) {
            index = parent(index);
            asn(index);
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    int n; cin >> n;
    vector<int> l(n), b(n); vcin(l); vcin(b);

    // assume is possible since trivial to check
    // this means l[i] >= b[i] if both sorted
    // take all barrels whos lids not large enough to begin with
    // these are free to swap arround without reducing unchanged barrels since they require a swap
    // optimal to sort from least to greatest and assign in decreasing size
    // if lid size not large enough, find smallest unchanged barrel with large enough lid, add it to changed set, assign lid
    // if no such barrel found or barrel larger than current barrel, impossible
    // can find smallest barrel with large enough lid by using segment tree with lid size rank as index, barrel size is value, min barrel size as query
    // edge case: not sure if this matters but tie break by picking larger lid index during segtree query

    vector<int> lorder(n); iota(all(lorder), 0); // lid size rank -> lid index
    vector<int> border = lorder;
    sort(all(lorder), [&](int i, int j) { return l[i] < l[j]; });
    sort(all(border), [&](int i, int j) { return b[i] < b[j]; });
    
    vector<int> lrank(n); // lid index -> lid size rank
    for (int i = 0; i < n; ++i) {
        if (l[lorder[i]] < b[border[i]]) {
            cout << "-1\n";
            return 0;
        }
        lrank[lorder[i]] = i;
    }

    priority_queue<int> ulr; // unmatched lid size ranks
    priority_queue<int> ub; // unmatched barrel sizes
    SegTree st(n); // unchanged barrel lid rank -> barrel size
    int unchanged = 0;
    for (int i = 0; i < n; ++i) {
        if (l[i] >= b[i]) {
            st.assign(lrank[i], make_pair(b[i], lrank[i]));
            ++unchanged;
        } else {
            ulr.push(lrank[i]);
            ub.push(b[i]);
        }
    }
    while (!ulr.empty()) {
        int clr = ulr.top(); ulr.pop();
        int cb = ub.top(); ub.pop();
        int cl = l[lorder[clr]];
        if (cb > cl) {
            // need to find first lid rank whose size at least cb
            int lo = clr;
            int hi = n-1;
            while (lo != hi) {
                int k = (lo + hi) >> 1;
                if (l[lorder[k]] < cb) {
                    lo = k + 1;
                } else {
                    hi = k;
                }
            }
            auto [qb, qlr] = st.query(lo, n-1);
            assert(qb < cb);
            st.assign(qlr, make_pair(INT_MAX, qlr));
            ub.push(qb);
            ulr.push(clr);
            --unchanged;
        }
    }
    cout << unchanged << "\n";
}

// lid: 3 1 3 4
// bar: 2 3 4 1

// unchanged: (3,2) (4,1)
// lid: 1 3
// bar: 3 4

// 3 < 4:
// query finds (4,1)
// unchanged: (3,2)
// lid: 1 3
// bar: 1 3

// 3 >= 3
// unchanged: (3,2)
// lid: 1
// bar: 1

// 1 >= 1
// unchanged: (3,2)
// lid:
// bar:

// done
// ans: 1