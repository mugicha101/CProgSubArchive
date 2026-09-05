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
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    }
    os << "]";
    return os;
}

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-9
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

inline void madd(int &x, int v) {
    x += v;
    x = x >= MOD ? x - MOD : x;
}

double randDbl() {
    return (double)rand() / (double)RAND_MAX;
}
uint64_t microsecs() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

struct query {
    int key;
    int start;
    int end;
};

inline ll magSqd(pair<ll,ll> p) {
    return p.first * p.first + p.second * p.second;
}

inline ll distSqd(pair<ll,ll> p, pair<ll,ll> q) {
    return magSqd({p.first - q.first, p.second - q.second});
}

inline bool isValid(pair<ll,ll> p, pair<ll,ll> q) {
    return max(magSqd(p), magSqd(q)) < distSqd(p, q);
}

struct M {
    uint32_t m[26][26];
    M() { memset(m, 0x7f, sizeof(m)); }
    inline uint32_t *operator[](size_t i) { return m[i]; }
};

const uint32_t UINF = UINT_MAX >> 2;

M comb(M &a, M &b) {
    M c;
    for (int k = 0; k < 26; ++k) {
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    return c;
}

int main() {
    cin.tie()->sync_with_stdio(0);
    cout << fixed << setprecision(12);
    
    // paladin - try matrix exponentiation shortest path for 26^2 log n
    // edge (x,y) exists iff (x,y) and (y,x) are valid edges in input and has weight of sum of both (x,y) and (y,x) in input
    // need to ensure M[k] stores path transitions of exactly length k
    // M[2^{k+1}] can be calculated from M[2^k]
    // for odd len, try every starting char and find sp of len (k-1)/2
    // for even len, start from (a,a) as center and find sp of len k/2-1 (or (k-1)/2 floored)
    int n, k; cin >> n >> k;

    // get input transitions
    uint32_t imat[26][26];
    memset(imat, 0x7f, sizeof(imat));
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        uint32_t cost; cin >> cost;
        int a = s[0]-'a', b = s[1]-'a';
        imat[a][b] = min(imat[a][b], cost);
    }
    
    // construct M[1]
    M m;
    for (int a = 0; a < 26; ++a) {
        for (int b = a; b < 26; ++b) {
            uint32_t cost = min(imat[a][b] + imat[b][a], UINF);
            m[a][b] = cost;
            m[b][a] = cost;
        }
    }

    // construct M[k] with matrix exponentiation
    int l = (k-1) >> 1;
    M mk; // will be M[k] at end
    for (int i = 0; i < 26; ++i) mk[i][i] = 0;
    while (l) {
        if (l & 1) mk = comb(mk, m);

        // double m
        m = comb(m, m);
        l >>= 1;
    }

    // find min path
    uint32_t best = UINF;
    for (int c = 0; c < 26; ++c) {
        uint32_t icost = k & 1 ? 0 : imat[c][c];
        if (icost >= best) continue;

        for (int d = 0; d < 26; ++d) {
            best = min(best, icost + mk[c][d]);
        }
    }
    cout << (best >= UINF ? -1 : (int)best) << "\n";
}
