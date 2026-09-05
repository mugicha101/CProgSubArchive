/*
Platinum 4
2618 - 경찰차
meta: {"problemId": 2618, "titleKo": "경찰차", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "경찰차", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 5591, "level": 17, "votedUserCount": 421, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.773200035095215, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "traceback", "isMeta": false, "bojTagId": 235, "problemCount": 216, "displayNames": [{"language": "ko", "name": "역추적", "short": "역추적"}, {"language": "en", "name": "traceback", "short": "traceback"}], "aliases": []}], "metadata": {}}
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
#define endl "\n"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int k, n; cin >> k >> n;
    n += 2;
    vector<pair<int,int>> points(n);
    points[0] = make_pair(1, 1);
    points[1] = make_pair(k, k);
    for (int i = 2; i < n; ++i) cin >> points[i].first >> points[i].second;
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    vector<vector<pair<int,int>>> src(n, vector<pair<int,int>>(n, make_pair(-1, -1)));
    dp[1][0] = 0;
    auto dist = [&](int i, int j) {
        return abs(points[i].first - points[j].first) + abs(points[i].second - points[j].second);
    };
    for (int i = 1; i+1 < n; ++i) {
        for (int j = 0; j < i; ++j) {
            auto trans = [&](int i2, int j2, int v) {
                if (dp[i2][j2] <= v) return;

                src[i2][j2] = { i, j };
                dp[i2][j2] = v;
            };
            trans(i+1, i, dp[i][j] + dist(j, i+1));
            trans(i+1, j, dp[i][j] + dist(i, i+1));
        }
    }
    int best = distance(dp.back().begin(), min_element(all(dp.back())));
    vector<int> assigned(n, -1);
    int car1 = n-1;
    int car2 = best;
    assigned[car1] = 1;
    assigned[car2] = 2;
    int i = n-1;
    int j = best;
    for (int _ = 2; _ < n; ++_) {
        auto [i2, j2] = src[i][j];
        i = i2; j = j2;
        if (i == car1) car2 = j;
        if (i == car2) car1 = j;
        if (j == car1) car2 = i;
        if (j == car2) car1 = i;
        assigned[car1] = 1;
        assigned[car2] = 2;
    }
    if (assigned[0] == 2) {
        for (int &x : assigned) x = 3 - x;
    }
    cout << dp.back()[best] << endl;
    for (int i = 2; i < n; ++i) {
        cout << assigned[i] << endl;
    }
}
