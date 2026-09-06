// 2025-09-30 22:43:19 
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;

#define MOD 1000000007

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

const int N = 90;

using mat_t = array<array<ll,N>,N>;

using vec_t = array<ll,N>;

// a * b
mat_t matmul(const mat_t &a, const mat_t &b) {
    mat_t res = {};
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            for (int k = 0; k < N; ++k) {
                res[r][c] = (res[r][c] + a[r][k] * b[k][c]) % MOD;
            }
        }
    }
    return res;
}

// m * v
vec_t vecmul(const mat_t &m, const vec_t &v) {
    vec_t res = {};
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            res[r] = (res[r] + m[r][c] * v[c]) % MOD;
        }
    }
    return res;
}

// m^p
mat_t matpow(const mat_t &m, ll p) {
    // matrix exp to find M^n: M^{sum(a_i * 2^i)} = prod(M^{a_i * 2^i})
    mat_t mp2i = m; // M^{2^i}
    mat_t mpn = {}; // M^n (starts at identity)
    for (int i = 0; i < N; ++i) mpn[i][i] = 1;
    for (int i = 0; i < 63; ++i) {
        if ((p >> i) & 1) mpn = matmul(mp2i, mpn);
        mp2i = matmul(mp2i, mp2i);
    }
    return mpn;
}

void debug(mat_t m) {
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            cout << m[r][c] << " ";
        }
        cout << endl;
    }
}
void debug(vec_t v) {
    for (int m9 = 0; m9 < 9; ++m9) {
        for (int d = 0; d < 10; ++d) {
            cout << v[m9 * 10 + d] << " ";
        }
        cout << endl;
    }
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);
    
    ll n;
    int k;
    cin >> n >> k;

    // case n == 1: brute force
    if (n == 1) {
        int res = k > 0 && k < 10;
        cout << res << endl;
        return 0;
    }

    // case n > 2

    // digit dp: (dig index, prev dig, mod9, mod25) -> count of nums with no matching neighboring at this state
    // can use CRT to derive the number modulo 225
    // however, dig index can be 10^18, thus we instead define a matrix transition from dp[i][...] to dp[i+1][...] and use matrix exponentiation

    // 225 = 3^2 * 5^2 = 9 * 25
    // k_1 = k % 9, k_2 = k % 25
    // x = k_1 mod 9
    // x = k_2 mod 25
    // M = 25 * 9 = 225
    // M_1 = M / 9 = 25
    // M_2 = M / 25 = 9
    // M_1 % 9 = 25 % 9 = 7, 7^{-1} mod 9 = 4, y_1 = 4
    // M_2 % 25 = 9 % 25 = 9, 9^{-1} mod 25 = 14, y_2 = 14
    // CRT:
    //  - x mod 225 = a mod 5
    //  - x mod 225 = b mod 9
    //  - x mod 225 = k_1 * M_1 * y_1 + k_2 * M_2 * y_2 = k_1 * 25 * 4 + k_2 * 9 * 14 = k_1 * 100 + k_2 * 126
    // mod 25 can be done with last 2 digs, so can handle that separately at the end
    // since no tight bound, can use matrix exponentiation for mod9
    // new dp state: (dig index, mod 9, last dig) -> count of nums matching this state with no neighboring matching digs
    // dp[d] size: 9 * 10 = 90
    // transition matrix M size: 90^2 < 10^4 (multiply in 10^6)
    // after finding dp[n-2] can try all last 2 digs to get all numbers x % 25 and x % 9

    // start at last dig 0, n % 9 == 0
    vec_t dp0 = {};
    dp0[0] = 1;

    // transition matrix M s.t. dp[d+1] = M * dp[d]
    mat_t m = {};
    for (int m9 = 0; m9 < 9; ++m9) {
        for (int d = 0; d < 10; ++d) {
            for (int nd = 0; nd < 10; ++nd) {
                if (d == nd) continue;

                int nm9 = (m9 * 10 + nd) % 9;
                ++m[nm9 * 10 + nd][m9 * 10 + d];
            }
        }
    }

    // raise to n-2
    mat_t p = matpow(m, n-2);
    vec_t dpl = vecmul(p, dp0);
    // cout << "m" << endl;
    // debug(m);
    // cout << "p" << endl;
    // debug(p);
    // cout << "dp0" << endl;
    // debug(dp0);
    // cout << "dpl" << endl;
    // debug(dpl);

    // try all last 2 digs
    ll res = 0;
    for (int m9 = 0; m9 < 9; ++m9) {
        for (int d = 0; d < 10; ++d) {
            ll t = dpl[m9 * 10 + d];
            for (int l1 = 0; l1 < 10; ++l1) {
                if (l1 == d) continue;
                for (int l2 = 0; l2 < 10; ++l2) {
                    if (l2 == l1) continue;
                    int l = l1 * 10 + l2;
                    int r9 = (m9 * 100 + l) % 9;
                    int r25 = l % 25;
                    
                    // crt
                    if (((r9 * 100 + r25 * 126) % 225) == k) res = (res + t) % MOD;
                }
            }
        }
    }

    cout << res << endl;

    // // brute force
    // int cap = 1;
    // res = 0;
    // for (int i = 0; i < n; ++i) cap *= 10;
    // int x = cap / 10;
    // while ((x % 225) != k) ++x;
    // for (; x < cap; x += 225) {
    //     string s = to_string(x);
    //     bool valid = true;
    //     for (int i = 1; valid && i < (int)s.size(); ++i) {
    //         valid = s[i] != s[i-1];
    //     }
    //     if (!valid) continue;

    //     ++res;
    // }
    // cout << res << endl;
}
