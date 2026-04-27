/*
Platinum 5
32501 - Ellipse Eclipse
meta: {"problemId": 32501, "titleKo": "Ellipse Eclipse", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Ellipse Eclipse", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 54, "level": 16, "votedUserCount": 13, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.5741000175476074, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "geometry", "isMeta": false, "bojTagId": 100, "problemCount": 2046, "displayNames": [{"language": "ko", "name": "기하학", "short": "기하학"}, {"language": "en", "name": "geometry", "short": "geom"}, {"language": "ja", "name": "幾何学", "short": "幾何"}], "aliases": []}, {"key": "binary_search", "isMeta": false, "bojTagId": 12, "problemCount": 1665, "displayNames": [{"language": "ko", "name": "이분 탐색", "short": "이분 탐색"}, {"language": "en", "name": "binary search", "short": "binary search"}, {"language": "ja", "name": "二分探索", "short": "二分探索"}], "aliases": [{"alias": "이분탐색"}, {"alias": "이진탐색"}]}, {"key": "ternary_search", "isMeta": false, "bojTagId": 101, "problemCount": 135, "displayNames": [{"language": "ko", "name": "삼분 탐색", "short": "삼분 탐색"}, {"language": "en", "name": "ternary search", "short": "ternary search"}, {"language": "ja", "name": "三分探索", "short": "三分探索"}], "aliases": []}], "metadata": {}}
*/

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    ld x1, y1, x2, y2, a;
    cin >> x1 >> y1 >> x2 >> y2 >> a;

    auto dist = [](ld ax, ld ay, ld bx, ld by) {
        ld dx = bx - ax;
        ld dy = by - ay;
        return sqrt(dx * dx + dy * dy);
    };

        auto calcMaxX = [&dist](ld x1, ld y1, ld x2, ld y2, ld a) {
        const ld EPS = 1L / 10e10L;
        const ld PI = 3.141592653589793238462643383279502884L;

        auto inEllipse = [&](ld x, ld y) {
            // check if (x, y) is within ellipse
            return dist(x1, y1, x, y) + dist(x2, y2, x, y) <= a;
        };

        auto calcD = [&](ld t) {
            // find distance d s.t. line from (x1, y1) to (x1 + dcos(t), y1 + dsin(t)) is on ellipse
            ld minD = 0;
            ld maxD = a;

            // bsearch
            while (maxD - minD > EPS) {
                ld d = minD * 0.5L + maxD * 0.5L;
                if (inEllipse(x1 + d * cos(t), y1 + d * sin(t))) {
                    minD = d;
                } else {
                    maxD = d;
                }
            }
            return minD;
        };

        auto calcX = [&](ld t) {
            return x1 + calcD(t) * cos(t);
        };

        auto calcY = [&](ld t) {
            return x1 + calcD(t) * sin(t);
        };

        // find max x
        ld minT = PI * -0.5L;
        ld maxT = PI * 0.5L;
        ld minTx = calcX(minT);
        ld maxTx = calcX(maxT);
        while (maxT - minT > EPS) {
            ld ta = minT + (maxT - minT) * (1.L / 3.L);
            ld tb = minT + (maxT - minT) * (2.L / 3.L);
            ld xa = calcX(ta);
            ld xb = calcX(tb);
            if (xa > xb) {
                maxT = tb;
                maxTx = xb;
            } else {
                minT = ta;
                minTx = xa;
            }
        }
        return calcX(minT);
    };

    cout << -calcMaxX(-x1, -y1, -x2, -y2, a) << " ";
    cout << -calcMaxX(-y1, -x1, -y2, -x2, a) << " ";
    cout << calcMaxX(x1, y1, x2, y2, a) << " ";
    cout << calcMaxX(y1, x1, y2, x2, a) << "\n";
}
