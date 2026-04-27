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

#include <bits/stdc++.h>
using namespace std;

// extended euclidean algorithm
void eeHelper(ll a, ll b, tuple<ll,ll,ll> &res) {
    if (b == 0) {
        res = {a, 1, 0};
        return;
    }
    
    eeHelper(b, a % b, res);
    swap(get<1>(res), get<2>(res));
    get<2>(res) -= get<1>(res) * (a / b);
}
tuple<ll,ll,ll> extendedEuclid(ll a, ll b) {
    tuple<ll,ll,ll> res;
    eeHelper(a, b, res);
    return res;
}

// returns the inverse of a mod m (-1 if none or multiple exist)
ll invMod(ll a, ll m) {
    auto &&[d, x, y] = extendedEuclid(a, m);
    return d == 1 ? ((x % m) + m) % m : -1;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    ll x, m; cin >> x >> m;
    ll im = invMod(x, m);
    cout << (im == -1 ? "No such integer exists." : to_string(im)) << "\n";
}
