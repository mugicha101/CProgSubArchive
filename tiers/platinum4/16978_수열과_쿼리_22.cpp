/*
Platinum 4
16978 - 수열과 쿼리 22
meta: {"problemId": 16978, "titleKo": "수열과 쿼리 22", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "수열과 쿼리 22", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 1906, "level": 17, "votedUserCount": 306, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.981600046157837, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "segtree", "isMeta": false, "bojTagId": 65, "problemCount": 1714, "displayNames": [{"language": "ko", "name": "세그먼트 트리", "short": "세그먼트 트리"}, {"language": "en", "name": "segment tree", "short": "segtree"}, {"language": "ja", "name": "セグメント木", "short": "セグ木"}], "aliases": [{"alias": "구간트리"}, {"alias": "세그트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "offline_queries", "isMeta": false, "bojTagId": 123, "problemCount": 372, "displayNames": [{"language": "ko", "name": "오프라인 쿼리", "short": "오프라인 쿼리"}, {"language": "en", "name": "offline queries", "short": "offline query"}, {"language": "ja", "name": "offline queries", "short": "offline query"}], "aliases": [{"alias": "offlinequery"}]}], "metadata": {}}
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

// STANDARD SEG TREE
// array based
// inclusive queries
class SegTree {
    // config
    using T = ll; // type
    const T ZRV = 0; // value to return if range is 0
    const T IV = 0; // initial value of elements
    inline T op(T l, T r) const { return l + r; } // range query operator
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
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int n; cin >> n;
    SegTree st(n);
    vector<pair<int,int>> q1s; // index, value
    vector<tuple<int,int,int>> q2s; // num query applied, first index, last index
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        st.assign(i, x);
    }
    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        int t; cin >> t;
        if (t == 1) {
            int ti, v; cin >> ti >> v; --ti;
            q1s.emplace_back(ti, v);
        } else {
            int nq, a, b; cin >> nq >> a >> b; --a; --b;
            q2s.emplace_back(nq, a, b);
        }
    }

    // handle q2s in q1 order using segtree
    vector<ll> q2res(q2s.size());
    vector<int> q2order(q2s.size());
    iota(all(q2order), 0);
    sort(all(q2order), [&](int i, int j) {
        return q2s[i] < q2s[j];
    });
    int q1i = 0;
    for (int q2i : q2order) {
        auto [nq, a, b] = q2s[q2i];
        while (q1i < nq) {
            auto [ti, v] = q1s[q1i++];
            st.assign(ti, v);
        }
        q2res[q2i] = st.query(a, b);
    }
    for (ll r : q2res) cout << r << "\n";
}
