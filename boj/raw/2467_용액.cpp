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
#define fill(x) for (auto &_e : x) cin >> _e;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<ll> vals(n); fill(vals);

    // find two values whose sum is closest to 0

    set<ll> lower;
    lower.insert(INF);
    lower.insert(-INF);

    ll best = LLONG_MAX;
    ll bestVals[2] = {-1,-1};
    for (ll x : vals) {
        ll geq = *lower.lower_bound(-x); // first >= -x
        ll leq = *(--lower.upper_bound(-x)); // first <= -x
        auto check = [&](ll v) {
            ll diff = abs(v + x);
            if (diff >= best) return;

            best = diff;
            bestVals[0] = v;
            bestVals[1] = x;
        };
        check(geq);
        check(leq);
        lower.insert(x);
    }
    cout << bestVals[0] << " " << bestVals[1] << endl;
}
