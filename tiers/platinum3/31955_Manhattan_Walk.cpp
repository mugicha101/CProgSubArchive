/*
Platinum 3
31955 - Manhattan Walk
meta: {"problemId": 31955, "titleKo": "Manhattan Walk", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Manhattan Walk", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 43, "level": 18, "votedUserCount": 6, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.093000054359436, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "probability", "isMeta": false, "bojTagId": 177, "problemCount": 508, "displayNames": [{"language": "ko", "name": "확률론", "short": "확률론"}, {"language": "en", "name": "probability theory", "short": "probability"}, {"language": "ja", "name": "確率論", "short": "確率論"}], "aliases": [{"alias": "expected value"}, {"alias": "기대값"}, {"alias": "기댓값"}]}], "metadata": {}}
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
#define endl "\n"

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int rows, cols, p; cin >> rows >> cols >> p;
    vector<vector<ld>> et(rows, vector<ld>(cols, INFINITY)); // et[r][c] = min expected wait time for r, c when moving optimally
    // flip around so that going from rows-1, cols-1 to 0, 0 using left/up movements
    // we can treat p as 1 and only multiply it in at the end wlog
    et[0][0] = 0;
    for (int s = 1; s < rows + cols - 1; ++s) {
        for (int r = 0; r < rows; ++r) {
            int c = s - r;
            if (c < 0 || c >= cols) continue;
            
            ld lt = c ? et[r][c-1] : LDBL_MAX; // expected time when moving left immediately
            ld ut = r ? et[r-1][c] : LDBL_MAX; // expected time when moving up immediately
            // expected time given wait time of t and arrow leftward:   l(t) = min(lt, ut + t)
            // expected time given wait time of t and arrow upward:     u(t) = min(ut + t, lt)
            // 50/50 chance of arrow being left or up, timer is uniformly random
            // thus expected wait time w = (int_0^1 l(t) + int_0^1 u(t)) * 0.5
            // f(a, b) = int_0^1 min(a, b + t)
            // let m = min t s.t. a <= b + t
            // f(a, b) = int_0^m(b + t) + int_m^1(a) = (0.5m^2 + bm) + a(1-m)
            // w = 0.5 * (f(lt, ut) + f(ut, lt))
            auto f = [](ld a, ld b) {
                ld m = max(0.0L, min(1.0L, a - b));
                return 0.5 * m * m + b * m + (a * (1 - m));
            };
            et[r][c] = 0.5 * (f(lt, ut) + f(ut, lt));
        }
    }
    cout << et[rows-1][cols-1] * p << endl;
}
