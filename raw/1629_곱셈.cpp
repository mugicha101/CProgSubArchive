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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // b = sum{b_k 2^k} where b_k 0 or 1
    // r = a^b mod c
    // a^b mod c = a^sum{b_k 2^k} mod c = prod{a^{b_k 2^k} mod c} mod c = prod{r[i]^b_k} mod c
    // r[i] = a^{2^i} mod c
    // r[i] = r[i-1]^2 mod c

    ll a, b, c;
    cin >> a >> b >> c;
    ll r[32] = {a % c};
    for (int i = 1; i < 32; ++i) r[i] = r[i-1] * r[i-1] % c;
    ll res = 1;
    for (int i = 0; i < 32; ++i) {
        if ((b >> i) & 1) res = (res * r[i]) % c;
    }
    cout << res << endl;
}
