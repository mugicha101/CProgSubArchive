/*
Platinum 2
10565 - Salary Inequity
meta: {"problemId": 10565, "titleKo": "Salary Inequity", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Salary Inequity", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 84, "level": 19, "votedUserCount": 16, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.7857000827789307, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "trees", "isMeta": false, "bojTagId": 120, "problemCount": 1920, "displayNames": [{"language": "ko", "name": "트리", "short": "트리"}, {"language": "en", "name": "tree", "short": "tree"}, {"language": "ja", "name": "木", "short": "木"}], "aliases": [{"alias": "trees"}]}, {"key": "segtree", "isMeta": false, "bojTagId": 65, "problemCount": 1714, "displayNames": [{"language": "ko", "name": "세그먼트 트리", "short": "세그먼트 트리"}, {"language": "en", "name": "segment tree", "short": "segtree"}, {"language": "ja", "name": "セグメント木", "short": "セグ木"}], "aliases": [{"alias": "구간트리"}, {"alias": "세그트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "lazyprop", "isMeta": false, "bojTagId": 66, "problemCount": 405, "displayNames": [{"language": "ko", "name": "느리게 갱신되는 세그먼트 트리", "short": "느리게 갱신되는 세그먼트 트리"}, {"language": "en", "name": "segment tree with lazy propagation", "short": "lazyprop"}, {"language": "ja", "name": "遅延評価セグメント木", "short": "遅延評価セグ木"}], "aliases": [{"alias": "레이지"}, {"alias": "레이지프로퍼게이션"}, {"alias": "레이지프로파게이션"}, {"alias": "구간트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "euler_tour_technique", "isMeta": false, "bojTagId": 150, "problemCount": 134, "displayNames": [{"language": "ko", "name": "오일러 경로 테크닉", "short": "오일러 경로 테크닉"}, {"language": "en", "name": "euler tour technique", "short": "ett"}, {"language": "ja", "name": "オイラーツアー", "short": "ett"}], "aliases": [{"alias": "ett"}]}], "metadata": {}}
*/

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;

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

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX >> 2;

void euler(vector<vector<int>> &adj, vector<int> &tour, vector<pair<int,int>> &itvs, int curr) {
    itvs[curr].first = tour.size();
    tour.push_back(curr);
    for (int next : adj[curr]) {
        euler(adj, tour, itvs, next);
    }
    itvs[curr].second = tour.size() - 1;
}

// STANDARD SEG TREE
// array based
// inclusive queries
class SegTree {
    // config
    using T = pair<int,int>; // type
    using L = int; // lazy type (must be numeric)
    const T ZRV = make_pair(INT_MAX, INT_MIN); // value to return if range is 0
    const T IV = make_pair(INT_MAX, INT_MIN); // initial value of elements
    inline T op(T l, T r) const { return make_pair(min(l.first, r.first), max(l.second, r.second)); } // range query operator
    inline T lop(T v, L l) const { return make_pair(v.first + l, v.second + l); } // lazy update operator
    // config end

    vector<L> lazy;
    vector<T> nodes;

    inline void asn(int i) {
        nodes[i] = op(at(left(i)), at(right(i)));
    }

    inline T at(int i) const {
        return lop(nodes[i], lazy[i]);
    }

    inline int left(int i) const {
        return (i << 1) + 1;
    }

    inline int right(int i) const {
        return (i << 1) + 2;
    }

    inline int parent(int i) const {
        return (i - 1) >> 1;
    }

    inline int elem(int i) const {
        return (nodes.size() >> 1) + i;
    }

    inline bool leaf(int i) const {
        return i >= elem(0);
    }

    T update_helper(int index, int size, int first, int last, L value) {
        if (first >= size || last < 0) return ZRV;
        if (first <= 0 && last >= size-1) {
            lazy[index] += value;
            return at(index);
        }
        size >>= 1;
        update_helper(left(index), size, first, last, value);
        update_helper(right(index), size, first - size, last - size, value);
        asn(index);
        return at(index);
    }

    T query_helper(int index, int size, int first, int last) const {
        if (first >= size || last < 0) return ZRV;
        if (first <= 0 && last >= size-1) return at(index);
        size >>= 1;
        return lop(op(query_helper(left(index), size, first, last), query_helper(right(index), size, first - size, last - size)), lazy[index]);
    }

    void dump_helper(int index, int indent) {
        cout << string(indent * 2, ' ') << "(" <<  nodes[index] << " + " << lazy[index] << ")" << endl;
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
        lazy.resize(n * 2 - 1, 0);
        for (int i = n-2; i >= 0; --i) {
            asn(i);
        }
    }

    T get(int index) const {
        return nodes[elem(index)];
    }

    void assign(int index, T value) {
        index = elem(index);
        nodes[index] = value;
        lazy[index] = 0;
        while (index) {
            index = parent(index);
            asn(index);
        }
    }

    void update(int first, int last, L value) {
        update_helper(0, (nodes.size() + 1) >> 1, first, last, value);
    }

    T query(int first, int last) const {
        return query_helper(0, (nodes.size() + 1) >> 1, first, last);
    }

    void dump() {
        dump_helper(0, 0);
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<int> parent(n, -1);
        vector<vector<int>> adj(n);
        vector<int> sal(n);
        vector<multiset<int>> childRanges(n);
        vector<int> raise(n);
        for (int i = 1; i < n; ++i) {
            cin >> parent[i];
            --parent[i];
            adj[parent[i]].push_back(i);
        }
        for (int i = 0; i < n; ++i) {
            cin >> sal[i];
        }

        // euler tour to compress to array
        vector<pair<int,int>> itvs(n);
        vector<int> tour;
        tour.reserve(n);
        euler(adj, tour, itvs, 0);

        // handle queries using min/max lazy-prop segtree
        SegTree st(n);
        for (int i = 0; i < n; ++i) st.assign(i, make_pair(sal[tour[i]], sal[tour[i]]));
        int q;
        cin >> q;
        while (q--) {
            char type;
            int index;
            cin >> type >> index;
            --index;
            pair<int,int> itv = itvs[index];
            if (type == 'Q') {
                pair<int,int> bounds = st.query(itv.first, itv.second);
                cout << bounds.second - bounds.first << endl;
            } else {
                int raise;
                cin >> raise;
                st.update(itv.first, itv.second, raise);
            }
        }
    }
}
