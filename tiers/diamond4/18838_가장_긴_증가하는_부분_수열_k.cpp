/*
Diamond 4
18838 - 가장 긴 증가하는 부분 수열 k
meta: {"problemId": 18838, "titleKo": "가장 긴 증가하는 부분 수열 k", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "가장 긴 증가하는 부분 수열 k", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 115, "level": 22, "votedUserCount": 36, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.808700084686279, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "segtree", "isMeta": false, "bojTagId": 65, "problemCount": 1714, "displayNames": [{"language": "ko", "name": "세그먼트 트리", "short": "세그먼트 트리"}, {"language": "en", "name": "segment tree", "short": "segtree"}, {"language": "ja", "name": "セグメント木", "short": "セグ木"}], "aliases": [{"alias": "구간트리"}, {"alias": "세그트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "traceback", "isMeta": false, "bojTagId": 235, "problemCount": 216, "displayNames": [{"language": "ko", "name": "역추적", "short": "역추적"}, {"language": "en", "name": "traceback", "short": "traceback"}], "aliases": []}, {"key": "lis", "isMeta": false, "bojTagId": 43, "problemCount": 123, "displayNames": [{"language": "ko", "name": "가장 긴 증가하는 부분 수열 문제", "short": "가장 긴 증가하는 부분 수열"}, {"language": "en", "name": "longest increasing sequence problem", "short": "lis"}, {"language": "ja", "name": "longest increasing sequence problem", "short": "lis"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

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

const ll K = 1e18;

class SegTree {
    // config
    using T = pair<int,ll>; // type
    const T ZRV = {0,0}; // value to return if range is 0
    const T IV = {0,0}; // initial value of elements
    inline T op(T l, T r) const {
        return l.first == r.first ? make_pair(l.first, min(l.second + r.second, K)) : max(l, r); } // range query operator
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
    
    // 18838 - reverse, count LDS w/ segtrees (cap count at k+1), reverse, lexographical construction for kth LIS
    int n; ll k; cin >> n >> k;
    vector<int> nums(n);
    for (int &x : nums) {
        cin >> x; --x;
    }

    vector<int> idx(n); // idx[x] = index of x in nums
    for (int i = 0; i < n; ++i) idx[nums[i]] = i;
    
    // suff[i] = (len of lis starting at i, # lis starting at i)
    vector<pair<int,ll>> suff(n);
    SegTree st(n);
    for (int i = (int)nums.size() - 1; i >= 0; --i) {
        int x = nums[i];
        auto [len, count] = st.query(x+1, n-1);
        st.assign(x, make_pair(len + 1, count + (len == 0)));
    }
    for (int x = 0; x < n; ++x) {
        suff[idx[x]] = st.get(x);
    }

    auto lisLen = max_element(suff.begin(), suff.end())->first;
    ll lisCount = st.query(0, n-1).second;
    if (lisCount < k) {
        cout << -1 << endl;
        return 0;
    }

    vector<vector<pair<int,ll>>> lis(lisLen + 1); // lis[l] = list of (index with lis starting from them of length l sorted by rank, count of such lis)
    for (int x = 0; x < n; ++x) {
        int i = idx[x];
        lis[suff[i].first].emplace_back(i, suff[i].second);
    }
    int curr = -1;
    int currV = -1;
    vector<int> res(lisLen);
    for (int l = lisLen; l >= 1; --l) {
        int next = 0;
        auto step = [&]() {
            while (lis[l][next].first <= curr || nums[lis[l][next].first] < currV) ++next;
        };
        step();
        while (k > lis[l][next].second) {
            k -= lis[l][next].second;
            ++next;
            step();
        }
        curr = lis[l][next].first;
        currV = nums[curr];
        res[lisLen-l] = currV + 1;
    }
    for (int x : res) cout << x << " ";
    cout << endl;
}
