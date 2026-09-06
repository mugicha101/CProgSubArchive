// 2026-08-09 23:23:51 
/*
Platinum 4
31049 - Great Fireball
meta: {"problemId": 31049, "titleKo": "Great Fireball", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Great Fireball", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 4, "level": 17, "votedUserCount": 1, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.25, "official": true, "tags": [{"key": "geometry", "isMeta": false, "bojTagId": 100, "problemCount": 2046, "displayNames": [{"language": "ko", "name": "기하학", "short": "기하학"}, {"language": "en", "name": "geometry", "short": "geom"}, {"language": "ja", "name": "幾何学", "short": "幾何"}], "aliases": []}, {"key": "sweeping", "isMeta": false, "bojTagId": 106, "problemCount": 708, "displayNames": [{"language": "ko", "name": "스위핑", "short": "스위핑"}, {"language": "en", "name": "sweeping", "short": "sweeping"}, {"language": "ja", "name": "平面走査", "short": "平面走査"}], "aliases": [{"alias": "라인 스위핑"}]}, {"key": "parametric_search", "isMeta": false, "bojTagId": 170, "problemCount": 544, "displayNames": [{"language": "ko", "name": "매개 변수 탐색", "short": "매개 변수 탐색"}, {"language": "en", "name": "parametric search", "short": "parametric search"}, {"language": "ja", "name": "parametric search", "short": "parametric search"}], "aliases": [{"alias": "파라메트릭"}]}], "metadata": {}}
*/

#include <cmath>
#include <limits>
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

// using namespace __gnu_pbds;
// template <class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000009
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
pair<T,U> operator-(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    }
    os << "]";
    return os;
}

// const ll INF = LLONG_MAX >> 2;

#define EPS 1e-12
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

inline void madd(int &x, int v) {
    x += v;
    x = x >= MOD ? x - MOD : x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(12);
    
    // larger circle always can capture more points (since contains smaller circle within)
    // bsearch on radius r
    // try each point as the leftmost point and sliding window
    // to check if even possible, ensure k points on one side
    // first need to find center of circle q based on point p = (x,y)
    // d = dist between (0,0) and p = x^2 + y^2
    // form triangle (0,0) - q - p
    // u = angle q - (0,0) - p
    // q - p = (0,0) - q = r
    // by law of cosines, r^2 = r^2 + d^2 - 2rdcos(u)
    //              2rdcos(u) = d^2
    //                      u = acos(d/(2r))
    // starting at (0,0) can get q by rotating u from dir to p and moving r forward

    // figure out locations of circle center for each point (both sides) denoted as (ra, la)
    // sort by circle centers to left of the point
    // sliding window on circle angle a, point in circle when ra <= a <= la
    // instead of storing circle centers, only need to store angle

    // for infinite sized circle, angle is +- pi/2 (quarter rot)

    using ft = ld;
    const ft INF = numeric_limits<ft>::max();

    // normalizes angle to [-PI, PI)
    auto angleNorm = [&](ft t) -> ft {
        t = fmod(t + ROT_HALF, ROT_FULL);
        return (t < 0 ? t + ROT_FULL : t) - ROT_HALF;
    };

    // auto rad2deg = [&](ft rad) {
    //     return rad * ((ft)180 / (ft)ROT_HALF);
    // };

    // returns (ra, la-ra)
    // returns {INF,INF} if invalid
    auto circAngles = [&](ft r, ft pdir, ft pdist) -> pair<ft,ft> {
        ft a = acos(pdist/(r + r));
        return isnan(a) ? make_pair(INF, INF) : make_pair(angleNorm(pdir - a), a * (ft)2);
    };
    struct orc { 
        ft x = 0, y = 0, dist = 0, dir = 0;
    };
    int n, k; cin >> n >> k;
    vector<orc> orcs(n);
    for (auto &o : orcs) {
        cin >> o.x >> o.y;
        o.dist = sqrt(o.x * o.x + o.y * o.y);
        o.dir = atan2(o.y, o.x);
    };
    vector<pair<ld,ld>> cas(n);
    vector<int> order(n);
    iota(all(order), 0);
    auto check = [&](ft r) -> bool {
        for (int i = 0; i < n; ++i) {
            cas[i] = circAngles(r, orcs[i].dir, orcs[i].dist);
        }

        // sort by ra
        sort(all(order), [&](int i, int j) {
            return cas[i].first < cas[j].first;
        });
        // cout << order << endl;
        // for (int i : order) {
        //     if (cas[i].first == INF) cout << "INF ";
        //     else cout << "(" << rad2deg(cas[i].first) << "," << rad2deg(cas[i].second) << ") ";
        // }
        // cout << endl;
        
        // loop circle twice to account for circular array
        priority_queue<ld, vector<ld>, greater<ld>> las;
        ft o = 0;
        for (int c = 0; c < 2; ++c) {
            for (int i : order) {
                ft ra = cas[i].first + o;
                if (ra == INF) break;

                while (!las.empty() && las.top() < ra) las.pop();
                las.push(ra + cas[i].second);
                // cout << (int)orcs[i].x << " " << (int)orcs[i].y << " " << rad2deg(ra) << " " << rad2deg(ra + cas[i].second) << " " << las.size() << endl;

                if ((int)las.size() >= k) {
                    // cout << "TRUE\n";
                    return true;
                }
            }
            o += ROT_FULL;
        }

        return false;
        // cout << "FALSE\n";
    };

    const ft RLIM = (ft)(1LL << 32);
    if (!check(RLIM)) {
        cout << -1 << "\n";
        return 0;
    }
    ft rMin = 0.L;
    ft rMax = 1.L;
    while (!check(rMax)) {
        rMin = rMax;
        rMax *= 2.L;
    }
    for (int i = 0; i < 100; ++i) {
        ft r = rMax * (ft)0.5 + rMin * (ft)0.5;
        if (check(r)) {
            rMax = r;
        } else {
            rMin = r;
        }
    }

    cout << rMax << "\n";
}