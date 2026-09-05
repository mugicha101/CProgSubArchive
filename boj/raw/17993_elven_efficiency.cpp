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
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int n, m; cin >> n >> m;

    // if a divisible by k, increment v and it's guaranteed to not be divisible by k anymore (unless k 1 which it can't be)
    // for each v, figure out its divisors O(sqrt(v)) and register it on them
    // then when divisor seen, will increment all at v and remove v from all its divisors
    // this would be O(msqrt(f(max(v),m))) where f is probably pretty sublinear
    map<int,set<int>> mult; // divisor -> active values
    deque<vector<int>> div; // value -> divisors

    // fill div[x] with divisors of x
    auto fillDiv = [&](int x) {
        while ((int)div.size() <= x) div.emplace_back();
        if (!div[x].empty()) return;

        int cap = sqrt(x);
        div[x].push_back(x);
        for (int j = 2; j <= cap; ++j) {
            if (x % j) continue;

            int k = x / j;
            div[x].push_back(j);
            if (k != j) div[x].push_back(k);
        }
    };

    // add x to active values
    auto addActive = [&](int x) {
        // cout << "ADD ACTIVE " << x << endl;
        fillDiv(x);
        for (int d : div[x]) {
            mult[d].insert(x);
        }
    };

    // remove x from active values
    auto remActive = [&](int x) {
        // cout << "REM ACTIVE " << x << endl;
        for (int d : div[x]) {
            mult[d].erase(x);
        }
    };
    vector<int> cnt; // number of each value
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        while ((int)cnt.size() <= x) cnt.push_back(0);
        ++cnt[x];
    }
    for (int x = 1; x < (int)cnt.size(); ++x) {
        if (cnt[x]) addActive(x);
    }
    // auto debug = [&]() {
    //     cout << res << endl;
    //     for (int x = 0; x < (int)cnt.size(); ++x) {
    //         if (cnt[x]) cout << mp(x, cnt[x]) << " ";
    //     }
    //     cout << endl;
    //     for (int d = 2; d < (int)mult.size(); ++d) {
    //         if (mult[d].empty()) continue;
    //         cout << d << ": ";
    //         for (int x : mult[d]) cout << x << " ";
    //         cout << endl;
    //     }
    // };
    // debug();
    for (int i = 0; i < m; ++i) {
        int k; cin >> k;
        // cout << "k=" << k << endl;
        while (k >= (int)cnt.size()) cnt.push_back(0);

        vector<int> m(mult[k].begin(), mult[k].end());
        for (int i = (int)m.size()-1; i >= 0; --i) {
            int v = m[i];
            while (v+1 >= (int)cnt.size()) cnt.push_back(0);
            if (cnt[v] == 0) {
                m[i] = -1;
                continue;
            }
            // cout << "BUMP " << v << " " << cnt[v] << endl;
            
            res += cnt[v];
            m[i] = cnt[v+1] ? -1 : v+1;
            cnt[v+1] += cnt[v];
            cnt[v] = 0;
            remActive(v);
        }
        for (int v : m) {
            if (v == -1) continue;
            addActive(v);
        }
        // debug();
    }
    cout << res << "\n";
}
