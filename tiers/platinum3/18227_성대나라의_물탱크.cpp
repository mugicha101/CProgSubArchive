/*
Platinum 3
18227 - 성대나라의 물탱크
meta: {"problemId": 18227, "titleKo": "성대나라의 물탱크", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "성대나라의 물탱크", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 898, "level": 18, "votedUserCount": 155, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.449899911880493, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "trees", "isMeta": false, "bojTagId": 120, "problemCount": 1920, "displayNames": [{"language": "ko", "name": "트리", "short": "트리"}, {"language": "en", "name": "tree", "short": "tree"}, {"language": "ja", "name": "木", "short": "木"}], "aliases": [{"alias": "trees"}]}, {"key": "segtree", "isMeta": false, "bojTagId": 65, "problemCount": 1714, "displayNames": [{"language": "ko", "name": "세그먼트 트리", "short": "세그먼트 트리"}, {"language": "en", "name": "segment tree", "short": "segtree"}, {"language": "ja", "name": "セグメント木", "short": "セグ木"}], "aliases": [{"alias": "구간트리"}, {"alias": "세그트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "euler_tour_technique", "isMeta": false, "bojTagId": 150, "problemCount": 134, "displayNames": [{"language": "ko", "name": "오일러 경로 테크닉", "short": "오일러 경로 테크닉"}, {"language": "en", "name": "euler tour technique", "short": "ett"}, {"language": "ja", "name": "オイラーツアー", "short": "ett"}], "aliases": [{"alias": "ett"}]}], "metadata": {}}
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
// #define endl "\n"

// STANDARD SEG TREE
// array based
// inclusive queries
class SegTree {
    // config
    using T = int; // type
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

int t = -1;
void euler(vector<vector<int>> &adj, vector<pair<int,int>> &tour, vector<int> &depth, vector<int> &parent, int curr) {
    tour[curr].first = ++t;
    for (int next : adj[curr]) {
        if (next == parent[curr]) continue;

        parent[next] = curr;
        depth[next] = depth[curr] + 1;
        euler(adj, tour, depth, parent, next);
    }
    tour[curr].second = t;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // d[i] = depth of i
    // s[i] = number of times a node in i's subtree has been filled
    // answer to query 2 i:  s[i] * d[i]
    // can use euler tour + segtree to do in O(nlgn)

    // input
    int n, root; cin >> n >> root; --root;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // euler tour
    vector<pair<int,int>> tour(n);
    vector<int> depth(n);
    vector<int> parent(n, -1);
    euler(adj, tour, depth, parent, root);

    // queries
    SegTree st(n);
    // vector<ll> brute(n);
    int k; cin >> k;
    while (k--) {
        int type, x; cin >> type >> x; --x;
        if (type == 1) {
            st.assign(tour[x].first, st.get(tour[x].first) + 1);
            /*
            while (x != -1) {
                brute[x] += depth[x] + 1;
                x = parent[x];
            }
            */
        } else {
            auto [start, end] = tour[x];
            cout << st.query(start, end) * (ll)(depth[x] + 1) << "\n";
            // cout << brute[x] << "\n";
        }
    }
    // st.dump();
}
