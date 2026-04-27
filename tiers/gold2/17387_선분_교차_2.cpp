/*
Gold 2
17387 - 선분 교차 2
meta: {"problemId": 17387, "titleKo": "선분 교차 2", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "선분 교차 2", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 6318, "level": 14, "votedUserCount": 311, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.716200113296509, "official": true, "tags": [{"key": "geometry", "isMeta": false, "bojTagId": 100, "problemCount": 2046, "displayNames": [{"language": "ko", "name": "기하학", "short": "기하학"}, {"language": "en", "name": "geometry", "short": "geom"}, {"language": "ja", "name": "幾何学", "short": "幾何"}], "aliases": []}, {"key": "case_work", "isMeta": false, "bojTagId": 137, "problemCount": 1205, "displayNames": [{"language": "ko", "name": "많은 조건 분기", "short": "많은 조건 분기"}, {"language": "en", "name": "case work", "short": "case work"}, {"language": "ja", "name": "ケースワーク", "short": "ケースワーク"}], "aliases": [{"alias": "케이스"}, {"alias": "케이스워크"}, {"alias": "케이스 워크"}]}, {"key": "line_intersection", "isMeta": false, "bojTagId": 42, "problemCount": 177, "displayNames": [{"language": "ko", "name": "선분 교차 판정", "short": "선분 교차 판정"}, {"language": "en", "name": "line segment intersection check", "short": "line segment intersection check"}, {"language": "ja", "name": "直線の交点", "short": "直線の交点"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned int uint;
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
#define mp(a,b) make_pair(a,b)

#include <bits/stdc++.h>
using namespace std;

struct Vec {
    ll x, y;
    Vec(ll x = 0, ll y = 0) : x(x), y(y) {}
    ll dot(Vec o) { return x * o.x + y * o.y; }
    Vec operator*(ll m) { return { x * m, y * m }; }
    Vec operator+(Vec o) { return { x + o.x, y + o.y }; }
    Vec operator-() { return { -x, -y }; }
    Vec operator-(Vec o) { return { x - o.x, y - o.y }; }
    Vec perp() { return { y, -x }; }
    ll magSqd() { return x * x + y * y; }
};
ostream& operator<<(ostream &os, const Vec &v) { return os << '<' << v.x << ", " << v.y << '>'; }

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);
    Vec a1, a2, b1, b2;
    cin >> a1.x >> a1.y >> a2.x >> a2.y >> b1.x >> b1.y >> b2.x >> b2.y;

    // SAT - project endpoints of b onto line parallel to a, see if b contains a's projection
    // do same for line parallel to b
    // if any have separation, then no collision
    auto satCheck = [&](Vec axis) {
        pair<ll,ll> aSpan = { axis.dot(a1), axis.dot(a2) };
        pair<ll,ll> bSpan = { axis.dot(b1), axis.dot(b2) };
        if (aSpan.first > aSpan.second) swap(aSpan.first, aSpan.second);
        if (bSpan.first > bSpan.second) swap(bSpan.first, bSpan.second);
        // cout << "axis: " << axis << " aSpan: " << aSpan << " bSpan: " << bSpan << endl;
        return aSpan.second < bSpan.first || bSpan.second < aSpan.first;
    };
    cout << !(
        satCheck((a2 - a1).perp())
        || satCheck((b2 - b1).perp())
        || satCheck(a2 - a1) // edge case for parallel lines
    ) << "\n";
}
