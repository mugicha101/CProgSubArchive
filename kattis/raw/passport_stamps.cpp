// 2025-05-08 23:10:55 
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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
// #define endl "\n"

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    ll n, p; cin >> n >> p;
    vector<ll> trips(n);
    for (auto &c : trips) cin >> c;

    // possible to fail trip[i] = c iff can remove all gaps of size c with prior trips
    // let z be the number of pages to insert a segment of length c at
    // z starts at p - (c-1)
    // each prior trip can invalidate its own pages plus c-1 pages before it
    // thus z can be reduced to p - (c-1) - sum(trip[0..<i]) - i * (c-1)
    // if z > 0, cannot invalidate this trip no matter what actions are taken
    // otherwise, this greedy method of spacing trips with gaps of c-1 between will invalidate trip[i]
    // worst case i * (c-1) = 10^5 * 10^18 = 10^23 > 2^64
    // thus need to use __int128_t

    ll psum = 0;
    for (ll i = 0; i < n; ++i) {
        ll c = trips[i];
        __int128_t z = (__int128_t)p - (__int128_t)(c - 1) - psum - (__int128_t)i * (__int128_t)(c - 1);
        if (z <= 0) {
            cout << i << endl;
            return 0;
        }
        psum += c;
    }
    cout << n << endl;
}
