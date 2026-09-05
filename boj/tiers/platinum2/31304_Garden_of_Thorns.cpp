/*
Platinum 2
31304 - Garden of Thorns
meta: {"problemId": 31304, "titleKo": "Garden of Thorns", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Garden of Thorns", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 22, "level": 19, "votedUserCount": 2, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.3181999921798706, "official": true, "tags": [{"key": "calculus", "isMeta": false, "bojTagId": 111, "problemCount": 169, "displayNames": [{"language": "ko", "name": "미적분학", "short": "미적분학"}, {"language": "en", "name": "calculus", "short": "calculus"}, {"language": "ja", "name": "微積分", "short": "微積分"}], "aliases": [{"alias": "미분"}, {"alias": "적분"}]}, {"key": "geometric_boolean_operations", "isMeta": false, "bojTagId": 202, "problemCount": 23, "displayNames": [{"language": "ko", "name": "도형에서의 불 연산", "short": "도형에서의 불 연산"}, {"language": "en", "name": "boolean operations on geometric objects", "short": "geometric boolean operations"}, {"language": "ja", "name": "図形のブール演算", "short": "図形のブール演算"}], "aliases": [{"alias": "병합"}, {"alias": "교집합"}, {"alias": "합집합"}, {"alias": "union"}, {"alias": "intersect"}]}, {"key": "geometry", "isMeta": false, "bojTagId": 100, "problemCount": 2046, "displayNames": [{"language": "ko", "name": "기하학", "short": "기하학"}, {"language": "en", "name": "geometry", "short": "geom"}, {"language": "ja", "name": "幾何学", "short": "幾何"}], "aliases": []}, {"key": "green", "isMeta": false, "bojTagId": 183, "problemCount": 16, "displayNames": [{"language": "ko", "name": "그린 정리", "short": "그린"}, {"language": "en", "name": "green's theorem", "short": "green's thm"}, {"language": "ja", "name": "グリーンの定理", "short": "グリーン"}], "aliases": []}, {"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}], "metadata": {}}
*/

#include <bits/stdc++.h>

using namespace std;
#define INPUT false
typedef long long ll;
typedef long double ld;

ld integral(ld a, ld b) {
    ld angleA = acos(a);
    ld angleB = acos(b);
    ld ya = sin(angleA);
    ld yb = sin(angleB);

    // area 1 (pizza slice)
    ld area1 = (angleA - angleB) * 0.5;

    // area 2 (bottom triangle)
    ld area2 = b * sqrt(1-b*b) * 0.5;
    
    // area 3 (left triangle)
    ld area3 = a * sqrt(1-a*a) * 0.5;
    
    return area1 + area2 - area3;
}

ld circOverlap(ld left, ld bottom, ld right, ld top) {
    ld hi, vi, area = 0.0;

    auto calc = [](ld w, ld h) {
        ld a = h < 1 ? cos(asin(h)) : 0;
        ld b = w < 1 ? w : 1.0;
        if (b <= a) return w * h;
        return integral(a, b) + a * h;
    };
    area += calc(right, top);
    area += calc(left, top);
    area += calc(right, bottom);
    area += calc(left, bottom);
    return area;
}

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(false);
    cout << setprecision(12);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif
    
    // input
    int n;
    ld r, w, h;
    cin >> n >> r >> w >> h;
    ld invR = 1.0 / r;
    w *= invR;
    h *= invR;
    ld invArea = 1.0 / (w * h);
    ld ev = 0.0;
    for (int i = 0; i < n; ++i) {
        ld x, y, v;
        cin >> x >> y >> v;
        x *= invR;
        y *= invR;
        ev += circOverlap(x, y, w-x, h-y) * invArea * v;
    }
    cout << ev << endl;
}
