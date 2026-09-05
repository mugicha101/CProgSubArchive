/*
Platinum 2
2336 - Team Selection
meta: {"problemId": 2336, "titleKo": "굉장한 학생", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "굉장한 학생", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Team Selection", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 1919, "level": 19, "votedUserCount": 254, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.186000108718872, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "segtree", "isMeta": false, "bojTagId": 65, "problemCount": 1714, "displayNames": [{"language": "ko", "name": "세그먼트 트리", "short": "세그먼트 트리"}, {"language": "en", "name": "segment tree", "short": "segtree"}, {"language": "ja", "name": "セグメント木", "short": "セグ木"}], "aliases": [{"alias": "구간트리"}, {"alias": "세그트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}], "metadata": {}}
*/

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
#define endl "\n"

// STANDARD SEG TREE
// array based
// inclusive queries
class SegTree {
    // config
    using T = int; // type
    const T ZRV = INT_MAX; // value to return if range is 0
    const T IV = INT_MAX; // initial value of elements
    inline T op(T l, T r) const { return min(l, r); } // range query operator
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
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<vector<int>> rank(3, vector<int>(n));
    for (vector<int> &comp : rank) {
        for (int i = 0; i < n; ++i) {
            int v; cin >> v;
            comp[v-1] = i;
        }
    }

    // need to find all i s.t. for all j exists c s.t. rank[c][i] > rank[c][j]
    // lower index = better
    // go from low to high index on A
    // store min segtree where index = index in B and value = index in C
    // for each A, check if exists element with lower B index and lower C index (min query on 0 to target's B index), if so is not excellent
    // segtree stores only elements already visited in A
    SegTree seg(n);
    vector<int> order(n);
    iota(all(order), 0);
    sort(all(order), [&](int i, int j) {
        return rank[0][i] < rank[0][j];
    });
    int numExcellent = 0;
    for (int i : order) {
        int minCRank = seg.query(0, rank[1][i]-1);
        numExcellent += minCRank > rank[2][i];

        seg.assign(rank[1][i], rank[2][i]);
    }
    cout << numExcellent << endl;
}
