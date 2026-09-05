#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;

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

#include <bits/stdc++.h>
using namespace std;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    vector<int> c(n);
    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }

    // n^2 = 1.6 * 10^7 possible sums for a[i], b[j]
    // memory: 3.2 * 10^7 * sizeof(int) = 1.28 * 10^8 bytes = 128 MB for a, b and c, d pairs
    vector<int> ab; ab.reserve(a.size() * b.size());
    vector<int> cd; cd.reserve(c.size() * d.size());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ab.push_back(a[i] + b[j]);
            cd.push_back(c[i] + d[j]);
        }
    }
    sort(all(ab));
    sort(all(cd), greater<int>());
    int i = 0;
    int j = 0;
    ll sum = 0;
    while (i < (int)ab.size()) {
        int v = ab[i];
        int iAmt = 0;
        while (i+iAmt < (int)ab.size() && ab[i+iAmt] == v) ++iAmt;
        i += iAmt;

        while (j < (int)cd.size() && cd[j] > -v) ++j;
        int jAmt = 0;
        while (j+jAmt < (int)cd.size() && cd[j+jAmt] == -v) ++jAmt;
        j += jAmt;
        
        sum += (ll)iAmt * (ll)jAmt;
    }
    cout << sum << endl;
}
