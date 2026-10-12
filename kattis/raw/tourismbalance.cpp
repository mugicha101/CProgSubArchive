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

#define EPS 1e-9
#define each(i, x) for (auto &i : x)
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)
#define getx(a) a.first
#define gety(a) a.second

bool findCycle(vector<vector<int>> &adj, vector<int> &anc, vector<int> &cycle, vector<bool> &isAnc, int curr, int parent) {
    if (isAnc[curr]) {
        // cycle found
        cycle.push_back(curr);
        while (anc.back() != curr) {
            cycle.push_back(anc.back());
            anc.pop_back();
        }
        return true;
    }
    anc.push_back(curr);
    isAnc[curr] = true;
    for (auto next : adj[curr]) {
        if (next == parent) continue;

        if (findCycle(adj, anc, cycle, isAnc, next, curr)) return true;
    }
    anc.pop_back();
    isAnc[curr] = false;

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    // 1 unique cycle
    int n, k; cin >> n >> k;
    vector<int> v(n); cin >> v;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // find cycle
    vector<int> anc;
    vector<int> cycle;
    vector<bool> isAnc(n);
    assert(findCycle(adj, anc, cycle, isAnc, 0, -1));

    vector<bool> inCycle(n);
    for (int x : cycle) inCycle[x] = true;
    // cout << cycle << endl;

    // find components
    vector<int> comp(n, -1);
    for (int x : cycle) comp[x] = x;
    for (int x : cycle) {
        queue<int> q;
        q.push(x);
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            for (int next : adj[curr]) {
                if (comp[next] != -1) continue;
                comp[next] = x;
                q.push(next);
            }
        }
    }
    // cout << comp << endl;

    // intercomponent
    map<int,int> vm; // value -> amt
    map<pair<int,int>,int> vcm; // (value, comp) -> amt
    for (int i = 0; i < n; ++i) {
        ++vm[v[i]];
        ++vcm[make_pair(v[i], comp[i])];
    }
    ll res = 0;
    for (auto &[key,acnt] : vcm) {
        auto [a,comp] = key;
        int b = a + k;
        auto it = vm.find(b);
        if (it == vm.end()) continue;

        int bcntAll = it->second;
        auto it2 = vcm.find(make_pair(b,comp));
        int bcntComp = it2 == vcm.end() ? 0 : it2->second;

        res += ((ll)bcntAll * 2 - (ll)bcntComp) * (ll)acnt;
    }
    cout << res << "\n";
}
