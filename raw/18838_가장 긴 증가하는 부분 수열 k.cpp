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
