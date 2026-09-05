/*
Platinum 2
17996 - Interstellar Travel
meta: {"problemId": 17996, "titleKo": "Interstellar Travel", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Interstellar Travel", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 16, "level": 19, "votedUserCount": 4, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.75, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "prefix_sum", "isMeta": false, "bojTagId": 139, "problemCount": 1379, "displayNames": [{"language": "ko", "name": "누적 합", "short": "누적 합"}, {"language": "en", "name": "prefix sum", "short": "prefix sum"}, {"language": "ja", "name": "累積和", "short": "累積和"}], "aliases": [{"alias": "구간합"}, {"alias": "부분합"}, {"alias": "rangesum"}]}, {"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}, {"key": "sweeping", "isMeta": false, "bojTagId": 106, "problemCount": 708, "displayNames": [{"language": "ko", "name": "스위핑", "short": "스위핑"}, {"language": "en", "name": "sweeping", "short": "sweeping"}, {"language": "ja", "name": "平面走査", "short": "平面走査"}], "aliases": [{"alias": "라인 스위핑"}]}], "metadata": {}}
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

#define EPS 1e-9
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Star {
    ld t;
    ld s;
    ld a;

    // t - s * |b-a| = 0
    // |b-a| = t / s
    // b = a +- t / s = a +- t * invS
    inline ld rangeL() const {
        return a - t / s;
    }

    inline ld rangeR() const {
        return a + t / s;
    }

    // calc distance given from point
    // x within [0, 2PI)
    inline ld calc(ld x) const {
        return max(t - s * min({abs(x - a), abs((x - (ld)ROT_FULL) - a), abs((x + (ld)ROT_FULL) - a)}), 0.0L);
    }
};

struct EndPoint {
    int i; // star index
    ld x; // position
    bool t; // 0 if range start, 1 if range end (this way overlaps allowed)

    EndPoint() {};
    EndPoint(int i, ld x, bool t) : i(i), x(x), t(t) {}

    inline bool operator<(EndPoint other) const {
        return x == other.x ? t < other.t : x < other.x;
    }
};
  
int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // n <= 10^5
    // x axis = angle, limited to [0, 2PI)
    // y axis = distance contributed by star
    // can represent each star's distance contribution as a function made up of 4 linear segments
    // want to find x where sum of all active line segments is maximized
    // trivially this is at one of the endpoints of a linear segment
    // worst case - all line segments active at once but at distinct x: O(N^2) naively because need to calc sum at each x
    // solution: can track changes in slope of sum line instead of tracking n lines
    // each linear segment of a star contributes to a change in slope at that point
    // this causes sweepline to be O(N)

    // input
    int n; cin >> n;
    vector<Star> stars(n);
    for (Star &star : stars) {
        cin >> star.t >> star.s >> star.a;
    }

    // find slope changes
    map<ld,ld> slopeChanges;
    for (Star &star : stars) {
        // find linear segment endpoints
        const int N = 7;
        pair<ld,ld> pts[N] = {}; // (x, y)
        pts[0] = {star.rangeL(), 0.0};
        pts[1] = {star.rangeR(), 0.0};
        pts[2] = {star.a, 0.0};
        pts[3] = {star.a + ROT_HALF, 0.0};

        // restrict x to [0, 2PI)
        for (auto &[x, _] : pts) {
            x = fmod(x, ROT_FULL);
            x = x < 0 ? x + ROT_FULL : x;
        }

        // add ends
        pts[4] = {0.0, 0.0};
        pts[5] = {(ld)ROT_FULL, 0.0};
        pts[6] = {(ld)ROT_FULL, 0.0};

        // evaluate ys
        for (int i = 0; i < N; ++i) {
            pts[i].second = star.calc(pts[i].first);
        }

        // sort by x
        sort(pts, pts + N);

        // calc slope changes
        ld prevSlope = 0.0;
        int i = 0;
        for (int j = 1; j < N; ++j) {
            if (pts[i].first == pts[j].first) continue; // ignore duplicate xs

            ld slope = (pts[j].second - pts[i].second) / (pts[j].first - pts[i].first); // slope should be s or -s but this is easier
            slopeChanges[pts[i].first] += slope - prevSlope;
            prevSlope = slope;
            i = j;
        }
    }
    
    // sweepline on slope changes
    ld slope = 0.0;
    ld angle = 0.0;
    ld sum = 0.0;
    for (const Star &star : stars) sum += star.calc(0.0);
    ld maxSum = 0.0;
    for (auto &[x, ds] : slopeChanges) {
        // move angle to x
        sum += slope * (x - angle);
        angle = x;
        maxSum = max(maxSum, sum);

        // update slope
        slope += ds;
    }
    cout << maxSum << endl;
}
