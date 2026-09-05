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

#define EPS 1e-7
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

// calc dist from src to all other nodes
// dijkstras
vector<int> dist(const vector<vector<pair<int,int>>> &adj, int src) {
    vector<int> res(adj.size(), INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    q.emplace(0, src);
    res[src] = 0;
    while (!q.empty()) {
        auto [d, curr] = q.top();
        q.pop();
        if (d > res[curr]) continue;

        for (auto [next, l] : adj[curr]) {
            int nd = d + l;
            if (res[next] <= nd) continue;

            res[next] = nd;
            q.emplace(nd, next);
        }
    }
    return res;
}

void dc(const vector<ll> &f, const vector<ll> &prev, vector<ll> &curr, int l, int r, int optL, int optR) {
    if (l > r) return;

    auto cost = [&](int i, int j) {
        return (f[j+1] - f[i]) * (ll)(j-i);
    };
    int m = (l + r) >> 1;
    
    // calc curr[m] by considering cuts from optL to optR
    int optM = optL;
    for (int k = optL; k <= optR; ++k) {
        ll c = prev[k] + cost(k, m-1);
        if (c >= curr[m]) continue;

        curr[m] = c;
        optM = k;
    }
    dc(f, prev, curr, l, m-1, optL, optM);
    dc(f, prev, curr, m+1, r, optM, optR);
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // h = hq
    // let f(i) = dist(i,h) + dist(h,i)
    // cost(s) = cost of set s of size m
    // = sum{i in s, j in s (i != j), dist(i,h) + dist(h,j)}
    // = sum{i in s, dist(i,h) + dist(h,i)} * (m-1)
    // = sum{i in s, f(i)} * (m-1)
    // want to assign smallest dist to largest set but need to find balance
    // so sort by increasing f(i), dp[i][j] = min sum cost of i sets consisting of first j elements (n^2 states)
    // dp[i][j] = min(dp[i-1][k<j] + cost(k..j-1)) - O(n^3) too large

    // opt[i][j] = optimal place to cut for dp[i][j]
    // monotonic: opt[i][a<j] <= opt[i][j] <= opt[i][b>j]
    // can divide and conquer to reduce dp[i][j] to O(blgb)

    // aliens trick reduces this further to 1D dp + parametric search, but since n^2lgn runs in time, no need (also needs floating points)

    // n <= 5*10^3
    // r <= 5*10^4
    // s <= b < n
    int n, b, s, r; cin >> n >> b >> s >> r;
    vector<vector<pair<int,int>>> adj(n);
    vector<vector<pair<int,int>>> rev(n);
    for (int i = 0; i < r; ++i) {
        int u, v, l; cin >> u >> v >> l; --u; --v;
        adj[u].emplace_back(v, l);
        rev[v].emplace_back(u, l);
    }

    // calculating f(i) for all i is just dijkstras
    // sort f increasing and convert to psum
    vector<int> fwdDist = dist(adj, b);
    vector<int> revDist = dist(rev, b);
    vector<ll> f(b+1);
    for (int i = 0; i < b; ++i) {
        f[i+1] = fwdDist[i] + revDist[i];
    }
    sort(f.begin()+1, f.end());
    for (int i = 1; i <= b; ++i) f[i] += f[i-1];

    // dp[i][j] = min cost to form i segments using first j elements
    // dp[0][0] = 0
    // opt[i][j] = min k s.t. dp[i][j] = dp[i-1][k] + cost(k,j-1)
    // opt[i][j-1] <= opt[i][j]
    vector<ll> prev(b+1, INF); // dp[i-1]
    vector<ll> curr(b+1, INF); // dp[i]
    curr[0] = 0;
    for (int i = 1; i <= s; ++i) {
        swap(prev, curr);
        for (int j = 0; j <= b; ++j) curr[j] = INF;
        dc(f, prev, curr, i, b, i-1, b-1);
    }
    cout << curr.back() << "\n";
}
