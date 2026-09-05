#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000009
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
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

inline void madd(int &x, int v) {
    x += v;
    x = x >= MOD ? x - MOD : x;
}

int main() {
    cin.tie()->sync_with_stdio(0);
    cout << fixed << setprecision(12);

    ll n, k, rows, cols; cin >> n >> k >> rows >> cols;
    k = k % n;
    vector<ll> s(n); for (ll &x : s) cin >> x;

    // k=0 edge case:
    // find max sum of subarr of length s
    // multiply by d to get ans
    if (k == 0) {
        ll best = LLONG_MIN;
        ll w = 0;
        for (int i = 0; i < cols-1; ++i) w += s[i];
        for (int i = cols-1; i < n; ++i) {
            w += s[i];
            best = max(best, w);
            w -= s[i-cols+1];
        }
        cout << best * rows << "\n";
        return 0;
    }

    // find r[i] = sum of rectangle starting from offset i
    // - can do sliding window of column psums: sum of ith column: sum(j=0, d-1, (i+jk)%n)
    // each rectangle will cycle through positions in their mod k group
    // in order for a r[i] to be valid, must exist at an offset <= n-s, which means i+jk mod n <= n-s for some j <= n-rows
    // each r[i] will cycle along a mod k group, so find the lowest offset in this group and the max rect in this group
    // if lowest offset <= n-s, max rect in this group is a candidate for the answer
    // handle k=0 separately
    // algo - find all mod k groups, figure out the offset of each element in first row in their mod k group
    // can find col sums from this by using group psums
    vector<pair<int,int>> gid(n, mp(-1,-1)); // group of i, offset of i in group
    vector<vector<ll>> gps; // group psums
    vector<vector<int>> groups; // group indices
    for (int i = 0; i < n; ++i) {
        if (gid[i].first != -1) continue;

        gps.emplace_back();
        groups.emplace_back();
        vector<ll> &ps = gps.back();
        vector<int> &g = groups.back();
        ps.push_back(0);
        int curr = i;
        do {
            gid[curr] = mp((int)gps.size()-1, (int)g.size());
            g.push_back(curr);
            ps.push_back(ps.back() + s[curr]);
            curr = (curr + k) % n;
        } while (curr != i);
    }

    // for (auto &ps : gps) {
    //     int l = ps.size();
    //     for (int i = 1; i < l; ++i) {
    //         cout << ps[i] - ps[i-1] << " ";
    //     }
    //     cout << endl;
    // }
    // pause();

    // helper to calc d length psum of col i
    auto cpsum = [&](int i) {
        auto &ps = gps[gid[i].first];
        ll j = gid[i].second;
        ll l = ps.size()-1;
        ll end = j + rows - 1; // ans: ps[end+1] - ps[j], but this assumes ps wraps around
        ll cycles = end / l; // how many full wrap arounds of ps ps[end] contains
        ll res = cycles * ps.back() + ps[end % l + 1] - ps[j];
        // cout << "i=" << i << " end=" << end << " j=" << j << " cycles=" << cycles << " res=" << res << endl; 
        return res;
    };
    // for (int i = 0; i < n; ++i) cout << cpsum(i) << " ";
    // cout << endl;
    vector<ll> r(n);
    for (int i = 0; i < cols; ++i) {
        r[0] += cpsum(i);
    }
    for (int i = 1; i < n; ++i) {
        r[i] = r[i-1] + cpsum((i+cols-1)%n) - cpsum(i-1);
    }
    // for (ll x : r) cout << x << " ";
    // cout << endl;

    // for each rect i, check days 0 to n-rows to see if it has an offset of <= n-cols
    // if so, is valid
    // can use sliding window with a set for this on each group
    ll res = LLONG_MIN;
    int ng = groups.size();
    for (int i = 0; i < ng; ++i) {
        auto &g = groups[i];
        reverse(g.begin(), g.end()); // reversed because k counter clockwise
        ll l = g.size();
        int ws = min(n-rows+1, l);
        multiset<int> w;
        for (int i = 0; i < ws; ++i) {
            w.insert(g[i]);
        }
        for (int i = 0; i < l; ++i) {
            // cout << g[i] << " " << r[g[i]] << ": ";
            // for (int x : w) cout << x << " ";
            // cout << endl;
            if (*w.begin() <= n-cols) res = max(res, r[g[i]]);
            w.insert(g[(i+ws)%l]);
            w.erase(w.find(g[i]));
        }
    }
    cout << res << "\n";

    // brute force
    // vector<vector<ll>> grid(n, vector<ll>(n));
    // for (ll i = 0; i < n; ++i) {
    //     for (ll j = 0; j < n; ++j) {
    //         grid[i][j] = s[(((i - j * k) % n) + n) % n];
    //     }
    // }
    // for (auto &row : grid) {
    //     for (ll x : row) cout << x << " ";
    //     cout << endl;
    // }
    // cout << endl;
    // for (int i = 0; i <= n-rows; ++i) {
    //     for (int j = 0; j <= n-cols; ++j) {
    //         ll sum = 0;
    //         for (int a = 0; a < rows; ++a) {
    //             for (int b = 0; b < cols; ++b) {
    //                 sum += grid[i+a][j+b];
    //             }
    //         }
    //         cout << sum << " ";
    //     }
    //     cout << endl;
    // }
}
