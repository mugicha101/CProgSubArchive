// 2025-04-17 17:08:53 
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;

const int MOD = 1000000007;
 
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
// #define endl "\n"

// STANDARD SEG TREE
// array based
// inclusive queries
class MaxSegTree {
    // config
    using T = int; // type
    const T ZRV = -1; // value to return if range is 0
    const T IV = -1; // initial value of elements
    inline T op(T l, T r) const { return max(l, r); } // range query operator
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

    MaxSegTree(int size) {
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
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    while (true) {
        // input
        int n; cin >> n;
        vector<pair<int,int>> years(n); // year, rain
        for (auto &[y, r] : years) cin >> y >> r;
        int m; cin >> m;
        vector<pair<int,int>> rqs(m); // range queries
        for (auto &[b, e] : rqs) cin >> b >> e;
        if (n == 0 && m == 0) break;

        // reassign years to rank
        vector<int> a;
        for (auto &[y, _] : years) a.push_back(y);
        for (int i = 1; i < n; ++i) {
            if (years[i-1].first + 1 < years[i].first) a.push_back(years[i-1].first + 1); // insert gap years to account for unassigned
        }
        for (auto &[b, e] : rqs) {
            a.push_back(b); a.push_back(e);
        }
        sort(a.begin(), a.end());
        a.resize(distance(a.begin(), unique(a.begin(), a.end())));
        unordered_map<int, int> rank;
        int k = a.size();
        for (int i = 0; i < k; ++i) rank[a[i]] = i;
        for (auto &[y, _] : years) y = rank[y];
        for (auto &[b, e] : rqs) {
            b = rank[b];
            e = rank[e];
        }
        // for (int x : a) cout << x << " ";
        // cout << endl;
        
        // query handling
        MaxSegTree maxST(k);
        MaxSegTree unasn(k);
        for (int i = 0; i < k; ++i) {
            unasn.assign(i, 1);
        }
        for (auto &[y, r] : years) {
            maxST.assign(y, r);
            unasn.assign(y, 0);
        }
        for (auto &[b, e] : rqs) {
            // satisfiable iff max(mv) < ev <= bv
            // maybe iff satisfiable and range contains unassigned years
            int bv = maxST.get(b);
            int ev = maxST.get(e);
            if (bv == -1) bv = ev == -1 ? INT_MAX : ev;
            if (ev == -1) ev = bv;
            int mv = maxST.query(b+1, e-1);
            // cout << mv << " " << ev << " " << bv << endl;
            bool sat = ev <= bv && mv < ev;
            bool maybe = sat && unasn.query(b, e);
            if (sat) {
                cout << (maybe ? "maybe" : "true") << "\n";
            } else {
                cout << "false" << "\n";
            }
        }
        cout << "\n";
    }
    cout.flush();
}

// 1985:5782 q1b
// ...
// 1995:3048
// ...
// 2005:4890 q1e q2b
// ...
// 2015:???? q2e