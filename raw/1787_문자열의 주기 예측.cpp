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

double randDbl() {
    return (double)rand() / (double)RAND_MAX;
}
uint64_t microsecs() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

// z algorithm
vector<int> zarr(string s) {
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i >= r) {
            l = i;
            r = i;
            while (r < n && s[r] == s[r-l])
                ++r;
            z[i] = r - l;
        } else if (i + z[i-l] >= r) {
            l = i;
            while (r < n && s[r] == s[r-l])
                ++r;
            z[i] = r-l;
        } else
            z[i] = z[i-l];
    }
    return z;
}

// knuth morris pratt string matching
struct KMP {
    // returns p where p[i] = length of longest prefix of P that is a proper suffix of P[0..<i] (proper meaning cannot equal P[0..<i])
    vector<int> prefixFunc(const string &s) {
        vector<int> p(s.size());
        int k = 0;
        for (int q = 1; q < (int)s.size(); ++q) {
            while (k > 0 && s[k] != s[q]) k = p[k-1];
            k += s[k] == s[q];
            p[q] = k;
        }
        return p;
    }

    string pat;
    vector<int> pref;
    KMP(string pattern) : pat(pattern), pref(prefixFunc(pattern)) {
        pat += (char)0;
    }

    // finds first instance of pattern in s
    int match(const string &s) {
        int m = (int)pref.size();
        int q = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            while (q > 0 && pat[q] != s[i]) q = pref[q-1];
            q += pat[q] == s[i];
            if (q == m) return i-m+1;
        }
        return -1;
    }

    // finds all instances of pattern in s
    vector<int> matchAll(const string &s) {
        int m = (int)pref.size();
        int q = 0;
        vector<int> matches;
        for (int i = 0; i < (int)s.size(); ++i) {
            while (q > 0 && pat[q] != s[i]) q = pref[q-1];
            q += pat[q] == s[i];
            if (q == m) matches.push_back(i-m+1);
        }
        return matches;
    }

    // count number of matches
    int matchCount(const string &s) {
        int m = (int)pat.size();
        int q = 0;
        int matches = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            while (q > 0 && pat[q] != s[i]) q = pref[q-1];
            q += pat[q] == s[i];
            matches += q == m;
        }
        return matches;
    }
};

int main() {
    cin.tie()->sync_with_stdio(0);
    cout << fixed << setprecision(12);

    // given S
    // Q is a period of S iff Q proper prefix of S and S prefix of QQ
    // find sum of all max periods of prefixes of S
    int n; cin >> n;
    string s; cin >> s;
    auto z = zarr(s);
    // cout << z << endl;
    vector<pair<int,int>> itvs; // start (q+1), end, q length
    for (int i = 1; i < n; i += 1) {
        if (z[i] == 0) continue;

        // consider S[<i] as a candidate Q
        // z[i] valid for prefixes of length i+1 to i+z[i]
        int minP = i+1;
        int maxP = i+z[i];
        // cout << s.substr(0, i) << " " << mp(minP, maxP) << endl;

        itvs.emplace_back(minP, maxP);
    }

    // sweepline
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> ends; // (end, q)
    multiset<int> activeQs;
    activeQs.insert(0);
    int next = 0;
    ll res = 0;
    for (int p = 1; p <= n; ++p) {
        while (next < (int)itvs.size() && itvs[next].first == p) {
            int q = itvs[next].first-1;
            activeQs.insert(q);
            ends.emplace(itvs[next++].second, q);
        }
        while (!ends.empty() && ends.top().first < p) {
            activeQs.erase(ends.top().second);
            ends.pop();
        }
        // cout << p << " " << *activeQs.rbegin() << endl;
        res += *activeQs.rbegin();
    }
    cout << res << "\n";
}
