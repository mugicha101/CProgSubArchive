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

#define MOD 998244353
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

ostream& operator<<(ostream& os, i128 x) {
    if (x < 0) {
        x = -x;
        os << '-';
    }
    static char s[40];
    int i = 0;
    while (x) {
        s[i++] = '0' + x % 10;
        x /= 10;
    }
    if (i == 0) s[i++] = '0';
    while (i) os << s[--i];
    return os;
}

istream& operator>>(istream& is, i128 &x) {
    static string s; is >> s;
    x = 0;
    bool neg = s[0] == '-';
    for (int i = 0; i < s.size(); ++i) {
        x = x * 10 + (s[i] - '0');
    }
    if (neg) x = -x;
    return is;
}


ostream& operator<<(ostream& os, u128 x) {
    static char s[40];
    int i = 0;
    while (x) {
        s[i++] = '0' + x % 10;
        x /= 10;
    }
    if (i == 0) s[i++] = '0';
    while (i) os << s[--i];
    return os;
}

istream& operator>>(istream& is, u128 &x) {
    static string s; is >> s;
    x = 0;
    bool neg = s[0] == '-';
    for (int i = 0; i < s.size(); ++i) {
        x = x * 10 + (s[i] - '0');
    }
    if (neg) x = -x;
    return is;
}

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
pair<T,U> operator-(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}

template <typename T, typename U>
istream& operator>>(istream& is, pair<T, U>& p) {
    return is >> p.first >> p.second;
}

template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

template <typename... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t) {
    os << "(";
    apply([&os](const auto&... args) {
        size_t n = 0;
        ((os << (n++ ? ", " : "") << args), ...);
    }, t);
    return os << ")";
}

template <typename... Args>
istream& operator>>(istream& is, tuple<Args...>& t) {
    apply([&is](auto&... args) {
        ((is >> args), ...);
    }, t);
    return is;
}

template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) {
    os << '{';
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << '}';
}
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream& operator>>(istream &is, T_container &v) {
    for (T &x : v) is >> x;
    return is;
}

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

const ll INF = LLONG_MAX >> 2;

// all primes necessary for the prime factorization of a number <= 100,000
const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 
    53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 
    137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 
    227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313};

bool prime(ll a) { if (a==1) return 0; ll cap = sqrt(a); for (int i=2;i<=cap;++i) if (a%i==0) return 0; return 1; }

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ hash<T2>{}(p.second); }
};

class LazySegTree {
    // config
    using T = ll; // type
    using L = ll; // lazy type (must be numeric)
    const T ZRV = 0; // value to return if range is 0
    const T IV = 0; // initial value of elements
    inline T op(T l, T r) const { return max(l,r); } // range query operator
    inline T lop(T v, L l, int s) const { return max(v, l); } // lazy update operator
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
            lazy[index] = op(lazy[index], value);
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

    void dump_helper(int index, int indent, int size) const {
        cout << string(indent * 2, ' ') << index << ":l(" <<  nodes[index] << "," << lazy[index] << "," << size << ")=" << lop(nodes[index], lazy[index], size) << endl;
        if (leaf(index)) return;
        dump_helper(left(index), indent+1, size >> 1);
        dump_helper(right(index), indent+1, size >> 1);
    }

public:
    
    LazySegTree(int size) {
        --size;
        int n = 1;
        while (size) { n <<= 1; size >>= 1; }
        nodes.resize(n * 2 - 1, IV);
        lazy.resize(n * 2 - 1, 0);
        for (int i = n-2; i >= 0; --i) asn(i, IV);
    }

    void update(int first, int last, L value) { update_helper(0, (nodes.size() + 1) >> 1, first, last, value); }
    T query(int first, int last) const { return query_helper(0, (nodes.size() + 1) >> 1, first, last); }
    void dump() const { dump_helper(0, 0, (nodes.size() + 1) >> 1); }
};

#define EPS 1e-9
#define each(i, x) for (auto &i : x)
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)
#define getx(a) a.first
#define gety(a) a.second

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    // to determine y level of a block, need to find max over interval
    // lazy segtree: range assignment, range max query
    // needs x coord compression
    int n; cin >> n;
    vector<pair<int,int>> queries(n); cin >> queries;
    vector<int> xs(n * 2);
    for (int i = 0; i < n; ++i) {
        auto [x,s] = queries[i];
        xs[i * 2] = x;
        xs[i * 2 + 1] = x + s - 1;
    }
    sort(all(xs));
    xs.resize(distance(xs.begin(), unique(all(xs))));
    // cout << xs << endl;
    unordered_map<int,int> xrank;
    for (int i = 0; i < xs.size(); ++i) xrank[xs[i]] = i;

    LazySegTree st(xs.size());
    // st.dump();
    ll maxY = 0;
    for (auto [x,s] : queries) {
        // cout << x << " " << s << endl;
        int a = xrank[x];
        int b = xrank[x+s-1];
        // cout << a << " " << b << " " << st.query(a, b) << endl;
        ll y = st.query(a, b) + s;
        st.update(a, b, y);
        maxY = max(maxY, y);
        cout << maxY << "\n";
    }
}