/*
Bronze 2
6930 - Mod Inverse
meta: {"problemId": 6930, "titleKo": "Mod Inverse", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Mod Inverse", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 190, "level": 4, "votedUserCount": 21, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.2999999523162842, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "bruteforcing", "isMeta": false, "bojTagId": 125, "problemCount": 2803, "displayNames": [{"language": "ko", "name": "브루트포스 알고리즘", "short": "브루트포스 알고리즘"}, {"language": "en", "name": "bruteforcing", "short": "bruteforce"}, {"language": "ja", "name": "全探索", "short": "全探索"}], "aliases": [{"alias": "완전탐색"}, {"alias": "완전 탐색"}, {"alias": "브루트포스"}, {"alias": "bruteforce"}, {"alias": "brute force"}, {"alias": "완탐"}]}, {"key": "number_theory", "isMeta": false, "bojTagId": 95, "problemCount": 1889, "displayNames": [{"language": "ko", "name": "정수론", "short": "정수론"}, {"language": "en", "name": "number theory", "short": "number theory"}, {"language": "ja", "name": "整数論", "short": "整数論"}], "aliases": []}, {"key": "modular_multiplicative_inverse", "isMeta": false, "bojTagId": 164, "problemCount": 204, "displayNames": [{"language": "ko", "name": "모듈로 곱셈 역원", "short": "모듈로 곱셈 역원"}, {"language": "en", "name": "modular multiplicative inverse", "short": "modular multiplicative inverse"}, {"language": "ja", "name": "モジュラ逆数", "short": "モジュラ逆数"}], "aliases": [{"alias": "modinv"}]}], "metadata": {}}
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
