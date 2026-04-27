/*
Platinum 5
1177 - Cattle Bruisers
meta: {"problemId": 1177, "titleKo": "조쌤포스", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "조쌤포스", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Cattle Bruisers", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 96, "level": 16, "votedUserCount": 23, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.4375, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "geometry", "isMeta": false, "bojTagId": 100, "problemCount": 2046, "displayNames": [{"language": "ko", "name": "기하학", "short": "기하학"}, {"language": "en", "name": "geometry", "short": "geom"}, {"language": "ja", "name": "幾何学", "short": "幾何"}], "aliases": []}, {"key": "case_work", "isMeta": false, "bojTagId": 137, "problemCount": 1205, "displayNames": [{"language": "ko", "name": "많은 조건 분기", "short": "많은 조건 분기"}, {"language": "en", "name": "case work", "short": "case work"}, {"language": "ja", "name": "ケースワーク", "short": "ケースワーク"}], "aliases": [{"alias": "케이스"}, {"alias": "케이스워크"}, {"alias": "케이스 워크"}]}, {"key": "sweeping", "isMeta": false, "bojTagId": 106, "problemCount": 708, "displayNames": [{"language": "ko", "name": "스위핑", "short": "스위핑"}, {"language": "en", "name": "sweeping", "short": "sweeping"}, {"language": "ja", "name": "平面走査", "short": "平面走査"}], "aliases": [{"alias": "라인 스위핑"}]}], "metadata": {}}
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
// #define endl "\n"

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // track bruisers relative to bessie
    // track times bruisers enter and exit bessie's range (secant line)
    // max overlapping intervals on enter/exit times
    int n;
    ll r;
    ll bx, by, bvx, bvy;
    cin >> n >> r >> bx >> by >> bvx >> bvy;
    vector<pair<pair<ll,ll>,pair<ll,ll>>> bruisers(n);
    for (auto &[pos, velo] : bruisers) {
        cin >> pos.first >> pos.second >> velo.first >> velo.second;
        pos.first -= bx;
        pos.second -= by;
        velo.first -= bvx;
        velo.second -= bvy;
    }
    int base = 0; // points always with bessie
    vector<pair<ld,ld>> itvs; // time intervals where a bruiser is in range of bessie
    for (int i = 0; i < n; ++i) {
        auto [px, py] = bruisers[i].first;
        auto [vx, vy] = bruisers[i].second;
        // cout << bruisers[i].first << " " << bruisers[i].second << endl;

        // edge case where bruiser doesn't move relative to bessie
        if (vx == 0 && vy == 0) {
            base += px * px + py * py <= r * r;
            // cout << "add base: " << (px * px + py * py <= r * r) << endl;
            continue;
        }

        // quadratic formula for circle/line intersection
        // px + vx * t = x
        // py * vy * t = y
        // x^2 + y^2 = r^2
        // since values <= 1000, can do this with standard long longs to avoid error propagation
        ll a = vx * vx + vy * vy;
        ll b = 2 * px * vx + 2 * py * vy;
        ll c = px * px + py * py - r * r;
        ll disc = b * b - 4 * a * c;
        // cout << "a: " << a << " b: " << b << " c: " << c << " disc: " << disc << endl;
        if (disc < 0) continue; // if discriminant is negative, no solutions

        // compute times of intersection (using long doubles to mitigate precision issues)
        ld t1 = (-(ld)b - sqrt((ld)disc)) / ((ld)a * 2.L);
        ld t2 = (-(ld)b + sqrt((ld)disc)) / ((ld)a * 2.L);
        // cout << "t1=" << t1 << " t2=" << t2 << endl;

        // ignore times before 0
        if (t2 < 0) continue;
        t1 = max(t1, 0.L);

        itvs.emplace_back(t1, t2);
    }
    sort(all(itvs));
    // cout << "base: " << base << endl;
    priority_queue<ld, vector<ld>, greater<ld>> ends;
    int res = 0;
    for (auto &itv : itvs) {
        while (!ends.empty() && ends.top() < itv.first) ends.pop();
        ends.push(itv.second);
        res = max(res, (int)ends.size());
    }
    res += base;
    cout << res << "\n";
}
