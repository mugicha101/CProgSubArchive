/*
Bronze 3
4153 - Egypt
meta: {"problemId": 4153, "titleKo": "직각삼각형", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "직각삼각형", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Egypt", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 60480, "level": 3, "votedUserCount": 177, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.026700019836426, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "geometry", "isMeta": false, "bojTagId": 100, "problemCount": 2046, "displayNames": [{"language": "ko", "name": "기하학", "short": "기하학"}, {"language": "en", "name": "geometry", "short": "geom"}, {"language": "ja", "name": "幾何学", "short": "幾何"}], "aliases": []}, {"key": "pythagoras", "isMeta": false, "bojTagId": 60, "problemCount": 124, "displayNames": [{"language": "ko", "name": "피타고라스 정리", "short": "피타고라스 정리"}, {"language": "en", "name": "pythagoras theorem", "short": "pythagoras thm"}, {"language": "ja", "name": "ピタゴラスの定理", "short": "ピタゴラス"}], "aliases": []}], "metadata": {}}
*/

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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    while (true) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 0 && b == 0 && c == 0) break;
        if (a > c) swap(a, c);
        if (b > c) swap(b, c);

        cout << (a * a + b * b == c * c ? "right" : "wrong") << endl;
    }
}
