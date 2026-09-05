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

int main() {
    cin.tie()->sync_with_stdio(0);
    cout << fixed << setprecision(12);

    // el brute
    int n; cin >> n;
    n = 1 << n;
    vector<vector<int>> grid(n, vector<int>(n)); for (auto &row : grid) vcin(row);

    // max size: 2^20 ~= 10^6
    // ensure 3 of each color and 1 0
    int k = ((n * n - 1) / 3) + 1;
    vector<int> cnt(k);
    vector<int> sat(k);
    bool res = true;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            ++cnt[grid[r][c]];
            if (grid[r][c] == 0) continue;

            bool bu = r && grid[r-1][c] == grid[r][c];
            bool bd = r+1 < n && grid[r+1][c] == grid[r][c];
            bool bl = c && grid[r][c-1] == grid[r][c];
            bool br = c+1 < n && grid[r][c+1] == grid[r][c];
            sat[grid[r][c]] = sat[grid[r][c]] || (bu && bl) || (bl && bd) || (bd && br) || (br && bu);
        }
    }
    res = res && cnt[0] == 1;
    for (int i = 1; i < k; ++i) res = res && (cnt[i] == 3 && sat[i]);
    cout << res << endl;
}
