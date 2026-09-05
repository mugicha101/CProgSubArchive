/*
Platinum 5
1214 - 쿨한 물건 구매
meta: {"problemId": 1214, "titleKo": "쿨한 물건 구매", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "쿨한 물건 구매", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 1591, "level": 16, "votedUserCount": 238, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.304200172424316, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "bruteforcing", "isMeta": false, "bojTagId": 125, "problemCount": 2803, "displayNames": [{"language": "ko", "name": "브루트포스 알고리즘", "short": "브루트포스 알고리즘"}, {"language": "en", "name": "bruteforcing", "short": "bruteforce"}, {"language": "ja", "name": "全探索", "short": "全探索"}], "aliases": [{"alias": "완전탐색"}, {"alias": "완전 탐색"}, {"alias": "브루트포스"}, {"alias": "bruteforce"}, {"alias": "brute force"}, {"alias": "완탐"}]}, {"key": "number_theory", "isMeta": false, "bojTagId": 95, "problemCount": 1889, "displayNames": [{"language": "ko", "name": "정수론", "short": "정수론"}, {"language": "en", "name": "number theory", "short": "number theory"}, {"language": "ja", "name": "整数論", "short": "整数論"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    ll a, b, c; cin >> c >> a >> b;
    if (a < b) swap(a, b);
    // find min a * x + b * y >= c
    // want to find best possible (c - a * x) % b (0 is best, max is best if 0 doesn't exist)
    // ax + by can form all values which are multiple of gcd(a, b) assuming x and y can be negative
    // since x and y cannot be negative, we increment x until all mod b repeats, then answer after that is c rounded to gcd(a, b)
    c = max(c, b);
    ll d = gcd(a, b);

    auto round_up = [](ll x, ll m) {
        return x + m - (((x - 1) % m) + 1);
    };

    ll best = min(round_up(c, a), round_up(c, b));
    set<ll> seen;
    for (ll x = 0; a * x <= c; ++x) {
        ll r = c - (a * x);
        ll m = r % b;
        if (!seen.insert(m).second) {
            cout << round_up(c, d) << endl;
            return 0;
        }
        best = min(best, a * x + round_up(r, b));
    }
    cout << best << endl;
}
