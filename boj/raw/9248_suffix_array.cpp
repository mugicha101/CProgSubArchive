#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;

const int MOD = 1000000007;
 
typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define endl "\n"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct SuffixArray {
    vector<vector<int>> c; // suffix equivalence classes
    vector<int> p; // final level permutation
    int lvls = 0;
    SuffixArray(string s) {
        int ogSize = (int)s.size();
        while ((1 << lvls) <= ogSize) ++lvls;
        s += '\0';
        int n = s.size();
        p.resize(n);
        c.resize(lvls + 1, vector<int>(n));

        // sort single characters
        iota(all(p), 0);
        sort(all(p), [&](int i, int j) {
            return s[i] < s[j];
        });
        c[0][p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            c[0][p[i]] = c[0][p[i-1]] + (s[p[i-1]] != s[p[i]]);
        }

        // build up to full suffixes
        auto modIdx = [&](int i) {
            return i >= n ? i - n : i;
        };
        for (int l = 1; l <= lvls; ++l) {
            int k = 1 << (l - 1);
            auto cmp = [&](int i, int j) {
                return c[l-1][i] == c[l-1][j] ? c[l-1][modIdx(i + k)] < c[l-1][modIdx(j + k)] : c[l-1][i] < c[l-1][j];
            };
            sort(all(p), cmp);
            c[l][p[0]] = 0;
            for (int i = 1; i < n; ++i) {
                c[l][p[i]] = c[l][p[i-1]] + cmp(p[i-1], p[i]);
            }
        }
    }

    // lcp (lazy version, no lcp array)
    int lcp(int i, int j) {
        int ans = 0;
        int n = p.size();
        for (int l = lvls; l >= 0; --l) {
            if (c[l][i % n] == c[l][j % n]) {
                int k = 1 << l;
                ans += k;
                i += k;
                j += k;
            }
        }
        return ans;
    }

    // get kth suffix (start index) in alphabetical order
    int kthSuffix(int k) {
        return p[k + 1];
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);
    
    // suffix array
    string s; cin >> s;
    SuffixArray sa(s);
    int n = s.size();
    for (int i = 0; i < n; ++i) cout << sa.kthSuffix(i) + 1 << " ";
    cout << endl << "x ";
    for (int i = 1; i < n; ++i)
        cout << sa.lcp(sa.kthSuffix(i-1), sa.kthSuffix(i)) << " ";
    cout << endl;
}
