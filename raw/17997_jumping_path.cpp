#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

// #define MOD 1000000007
#define MOD 11092019

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

class SegTree {
    // config
    using T = pair<int,int>; // type
    const T ZRV = {0,0}; // value to return if range is 0
    const T IV = {0,0}; // initial value of elements
    inline T op(T l, T r) const { return l.first == r.first ? make_pair(l.first, (l.second + r.second) % MOD) : max(l, r); } // range query operator
    // config end

    vector<T> nodes;
    vector<pair<int,pair<int,int>>> hist;

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
        hist.emplace_back(index, make_pair(0,0));
        index = elem(index);
        hist.back().second = nodes[index];
        nodes[index] = value;
        while (index) {
            index = parent(index);
            asn(index);
        }
    }

    void undo() {
        assign(hist.back().first, hist.back().second);
        hist.pop_back();
        hist.pop_back();
    }
};

pair<int,int> dfs(vector<vector<int>> &adj, vector<int> &label, SegTree &st, int curr) {
    int x = label[curr];
    auto [ql, qc] = st.query(0, x);
    auto res = make_pair(ql + 1, (qc + (ql == 0)) % MOD);
    st.assign(x, res);
    for (int next : adj[curr]) {
        auto dres = dfs(adj, label, st, next);
        if (res.first == dres.first) res.second = (res.second + dres.second) % MOD;
        else res = max(res, dres);
    }
    st.undo();
    return res;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // LIS with counts using segtree
    // st[v] = (l, c)
    // v = value
    // l = length of LIS with last value v
    // c = number of LIS with last value v
    // st.query(i,j) = (length of LIS ending within [i,j], number of such LIS)
    // for each index i
    // (ql, qc) = st.query(0, v)
    // st[v] = (ql + 1, qc)
    // allow segtree to be undoable
    int n; cin >> n;
    vector<int> label(n);
    for (int i = 0; i < n; ++i) cin >> label[i];
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int p; cin >> p; --p;
        adj[p].push_back(i);
    }
    int mv = *max_element(label.begin(), label.end());
    SegTree st(mv + 1);
    auto [l, c] = dfs(adj, label, st, 0);
    cout << l << " " << c << endl;
}
