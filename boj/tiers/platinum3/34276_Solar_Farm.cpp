/*
Platinum 3
34276 - Solar Farm
meta: {"problemId": 34276, "titleKo": "Solar Farm", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Solar Farm", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 18, "level": 18, "votedUserCount": 5, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.6110999584198, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "bruteforcing", "isMeta": false, "bojTagId": 125, "problemCount": 2803, "displayNames": [{"language": "ko", "name": "브루트포스 알고리즘", "short": "브루트포스 알고리즘"}, {"language": "en", "name": "bruteforcing", "short": "bruteforce"}, {"language": "ja", "name": "全探索", "short": "全探索"}], "aliases": [{"alias": "완전탐색"}, {"alias": "완전 탐색"}, {"alias": "브루트포스"}, {"alias": "bruteforce"}, {"alias": "brute force"}, {"alias": "완탐"}]}, {"key": "geometry", "isMeta": false, "bojTagId": 100, "problemCount": 2046, "displayNames": [{"language": "ko", "name": "기하학", "short": "기하학"}, {"language": "en", "name": "geometry", "short": "geom"}, {"language": "ja", "name": "幾何学", "short": "幾何"}], "aliases": []}, {"key": "calculus", "isMeta": false, "bojTagId": 111, "problemCount": 169, "displayNames": [{"language": "ko", "name": "미적분학", "short": "미적분학"}, {"language": "en", "name": "calculus", "short": "calculus"}, {"language": "ja", "name": "微積分", "short": "微積分"}], "aliases": [{"alias": "미분"}, {"alias": "적분"}]}, {"key": "pythagoras", "isMeta": false, "bojTagId": 60, "problemCount": 124, "displayNames": [{"language": "ko", "name": "피타고라스 정리", "short": "피타고라스 정리"}, {"language": "en", "name": "pythagoras theorem", "short": "pythagoras thm"}, {"language": "ja", "name": "ピタゴラスの定理", "short": "ピタゴラス"}], "aliases": []}], "metadata": {}}
*/

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

ll solve() {
    ll r, w, h; cin >> r >> w >> h;
    ll rr = r * r;
    ll rr4 = rr * 4;

    // (iw)^2 + (jh)^2 = 4r^2
    // 2l^2 = r^2
    // l = sqrt(r^2/2) = iw/2
    // r^2/2 = (iw)^2/4
    // r^2 = (iw)^2/2 = (jh)^2/2
    // i = sqrt(2r^2)/w = sqrt(2)r/w
    // A = ij
    ll C = 1000;
    ll iMin = (ll)(sqrt(2.L) * (ld)r / (ld)w) - C;
    ll iMax = iMin + C * 2;
    ll jMin = (ll)(sqrt(2.L) * (ld)r / (ld)h) - C;
    ll jMax = jMin + C * 2;

    auto sub = [&](ll i, ll w, ll h) -> ll {
        if (i <= 0) return 0;

        // j varies
        ll jMin = 0;
        ll jMax = r * 2;
        ll iw = i * w;
        if (iw >= r * 2) return 0;

        while (jMin != jMax) {
            ll j = (jMin + jMax + 1) >> 1;
            ll jh = j * h;
            if (jh <= r * 2 && iw * iw + jh * jh <= rr4) {
                jMin = j;
            } else {
                jMax = j - 1;
            }
        }
        return i * jMin;
    };
    ll maxArea = 0;
    for (ll i = iMin; i <= iMax; ++i) {
        maxArea = max(maxArea, sub(i, w, h));
    }
    for (ll j = jMin; j <= jMax; ++j) {
        maxArea = max(maxArea, sub(j, h, w));
    }
    return maxArea;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int tc; cin >> tc;
    while  (tc--) {
        cout << solve() << "\n";
    }
}
