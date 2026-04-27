/*
Platinum 4
10999 - 구간 합 구하기 2
meta: {"problemId": 10999, "titleKo": "구간 합 구하기 2", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "구간 합 구하기 2", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 5322, "level": 17, "votedUserCount": 233, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 3.2040998935699463, "official": true, "tags": [{"key": "segtree", "isMeta": false, "bojTagId": 65, "problemCount": 1714, "displayNames": [{"language": "ko", "name": "세그먼트 트리", "short": "세그먼트 트리"}, {"language": "en", "name": "segment tree", "short": "segtree"}, {"language": "ja", "name": "セグメント木", "short": "セグ木"}], "aliases": [{"alias": "구간트리"}, {"alias": "세그트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "lazyprop", "isMeta": false, "bojTagId": 66, "problemCount": 405, "displayNames": [{"language": "ko", "name": "느리게 갱신되는 세그먼트 트리", "short": "느리게 갱신되는 세그먼트 트리"}, {"language": "en", "name": "segment tree with lazy propagation", "short": "lazyprop"}, {"language": "ja", "name": "遅延評価セグメント木", "short": "遅延評価セグ木"}], "aliases": [{"alias": "레이지"}, {"alias": "레이지프로퍼게이션"}, {"alias": "레이지프로파게이션"}, {"alias": "구간트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}], "metadata": {}}
*/

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

#define MOD 1000000007

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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

// LAZY SEG TREE
// array based
// inclusive queries
class LazySegTree {
    // config
    using T = ll; // type
    using L = ll; // lazy type (must be numeric)
    const T ZRV = 0; // value to return if range is 0
    const T IV = 0; // initial value of elements
    inline T op(T l, T r) const { return l + r; } // range query operator
    inline T lop(T v, L l, int s) const { return v + l * s; } // lazy update operator
    // config end

    vector<L> lazy;
    vector<T> nodes;

    inline void asn(int i, int size) { nodes[i] = op(at(left(i), size >> 1), at(right(i), size >> 1)); }
    inline T at(int i, int size) const { return lop(nodes[i], lazy[i], size); }
    inline int left(int i) const { return (i << 1) + 1; }
    inline int right(int i) const { return (i << 1) + 2; }
    inline int parent(int i) const { return (i - 1) >> 1; }
    inline int elem(int i) const { return (nodes.size() >> 1) + i; }
    inline bool leaf(int i) const { return i >= elem(0); }

    T update_helper(int index, int size, int first, int last, L value) {
        if (first >= size || last < 0) return ZRV;
        if (first <= 0 && last >= size-1) {
            lazy[index] += value;
            return at(index, size);
        }
        update_helper(left(index), size >> 1, first, last, value);
        update_helper(right(index), size >> 1, first - (size >> 1), last - (size >> 1), value);
        asn(index, size);
        return at(index, size);
    }

    T query_helper(int index, int size, int first, int last) const {
        if (first >= size || last < 0) return ZRV;
        if (first <= 0 && last >= size-1) return at(index, size);
        return lop(op(query_helper(left(index), size >> 1, first, last), query_helper(right(index), size >> 1, first - (size >> 1), last - (size >> 1))), lazy[index], min(last, size-1) + 1 - max(first, 0));
    }

    // void dump_helper(int index, int indent, int size) const {
    //     cout << string(indent * 2, ' ') << index << ":l(" <<  nodes[index] << "," << lazy[index] << "," << size << ")=" << lop(nodes[index], lazy[index], size) << endl;
    //     if (leaf(index)) return;
    //     dump_helper(left(index), indent+1, size >> 1);
    //     dump_helper(right(index), indent+1, size >> 1);
    // }

public:
    
    LazySegTree(int size) {
        --size;
        int n = 1;
        while (size) { n <<= 1; size >>= 1; }
        nodes.resize(n * 2 - 1, IV);
        lazy.resize(n * 2 - 1, 0);
        for (int i = n-2; i >= 0; --i) asn(i, 1);
    }

    void assign(int index, L value) { update(index, index, value - query(index, index)); }
    void update(int first, int last, L value) { update_helper(0, (nodes.size() + 1) >> 1, first, last, value); }
    T query(int first, int last) const { return query_helper(0, (nodes.size() + 1) >> 1, first, last); }
    // void dump() const { dump_helper(0, 0, (nodes.size() + 1) >> 1); }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int n, m, k; cin >> n >> m >> k;
    int q = m + k;

    // standard lazy segtree
    LazySegTree st(n);
    for (int i = 0; i < n; ++i) {
        ll x; cin >> x;
        st.assign(i, x);
    }

    // st.dump();
    for (int i = 0; i < q; ++i) {
        int t, a, b; cin >> t >> a >> b; --a; --b;
        if (t == 2) {
            ll x = st.query(a, b);
            cout << x << "\n";
        } else {
            ll v; cin >> v;
            st.update(a, b, v);
        }
        // st.dump();
    }
}
  