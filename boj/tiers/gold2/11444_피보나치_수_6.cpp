/*
Gold 2
11444 - 피보나치 수 6
meta: {"problemId": 11444, "titleKo": "피보나치 수 6", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "피보나치 수 6", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 12673, "level": 14, "votedUserCount": 301, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.080899953842163, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "exponentiation_by_squaring", "isMeta": false, "bojTagId": 39, "problemCount": 354, "displayNames": [{"language": "ko", "name": "분할 정복을 이용한 거듭제곱", "short": "분할 정복을 이용한 거듭제곱"}, {"language": "en", "name": "exponentiation by squaring", "short": "exponentiation by squaring"}, {"language": "ja", "name": "二乗法によるべき乗", "short": "二乗法によるべき乗"}], "aliases": [{"alias": "거듭제곱"}, {"alias": "제곱"}, {"alias": "power"}, {"alias": "square"}]}], "metadata": {}}
*/

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

struct Matrix {
    ll v[4] = {};
    Matrix(ll a = 0, ll b = 0, ll c = 0, ll d = 0) {
        v[0] = a;
        v[1] = b;
        v[2] = c;
        v[3] = d;
    }

    Matrix operator *(Matrix o) {
        return {
            (v[0] * o.v[0] + v[1] * o.v[2]) % MOD, (v[0] * o.v[1] + v[1] * o.v[3]) % MOD,
            (v[2] * o.v[0] + v[3] * o.v[2]) % MOD, (v[2] * o.v[1] + v[3] * o.v[3]) % MOD
        };
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // fib with matrix exponentiation
    Matrix pow = {1, 1, 1, 0};
    Matrix mat = {1, 0, 0, 1};
    ll n; cin >> n;
    for (int i = 0; i < (int)62; ++i) {
        if ((n >> i) & 1) mat = pow * mat;
        pow = pow * pow;
    }
    cout << mat.v[2] << endl;
}
