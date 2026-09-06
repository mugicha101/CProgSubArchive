// 2026-08-01 14:14:26 
#include <cmath>
#include <limits>
#include <random>
#include <queue>
#include <array>
#include <thread>
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

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
using lll = __int128_t;
using ulll = unsigned __int128_t;

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

#define EPS 1e-12
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

// knuth morris pratt string matching
struct KMP {
    // returns p where p[i] = length of longest prefix of P that is a proper suffix of P[0..<i] (proper meaning cannot equal P[0..<i])
    static vector<int> prefixFunc(const string &s) {
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
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);
    
    string s;
    getline(cin, s);
    int n; cin >> n;
    cin.ignore(100, '\n');
    vector<KMP> kmps;
    kmps.reserve(n);
    vector<string> src(n);
    vector<string> res(n);
    for (int i = 0; i < n; ++i) {
        string a, b;
        getline(cin, a, '=');
        getline(cin, b);
        kmps.emplace_back(a);
        src[i] = a;
        res[i] = b;
    }
    int steps = 0;
    while (true) {
        bool match = false;
        for (int i = 0; i < n; ++i) {
            int j = kmps[i].match(s);
            if (j == -1) continue;

            match = true;
            s = s.substr(0, j) + res[i] + s.substr(j + src[i].size());
            break;
        }

        if (!match) {
            cout << s << "\n";
            break;
        }
        ++steps;
        if (steps > 5000) {
            cout << "Time Limit Exceeded\n";
            break;
        }
        if (s.size() > 255) {
            cout << "Memory Limit Exceeded\n";
            break;
        }
    }
}
