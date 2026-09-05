#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<ll> vals(n); vcin(vals);
    
    // try all pairs, bsearch for middle
    sort(all(vals));
    ll best = LLONG_MAX;
    ll bestIdx[3] = {};
    for (int i = 0; i <= n-3; ++i) {
        for (int j = i+2; j <= n-1; ++j) {
            int l = i+1;
            int r = j-1;

            // find first element s.t. l + h >= 0
            while (l != r) {
                int m = (l + r) >> 1;
                if (vals[i] + vals[j] + vals[m] >= 0) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }

            ll diff = abs(vals[i] + vals[j] + vals[l]);
            ll t = abs(vals[i] + vals[j] + vals[l-1]);
            if (l > i+1 && t < diff) {
                diff = t;
                --l;
            }
            if (diff >= best) continue;

            best = diff;
            bestIdx[0] = i;
            bestIdx[1] = l;
            bestIdx[2] = j;
        }
    }
    cout << vals[bestIdx[0]] << " " << vals[bestIdx[1]] << " " << vals[bestIdx[2]] << endl;
}
