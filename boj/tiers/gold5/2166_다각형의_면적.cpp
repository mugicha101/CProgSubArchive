/*
Gold 5
2166 - 다각형의 면적
meta: {"problemId": 2166, "titleKo": "다각형의 면적", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "다각형의 면적", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 13102, "level": 11, "votedUserCount": 323, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.2112998962402344, "official": true, "tags": [{"key": "geometry", "isMeta": false, "bojTagId": 100, "problemCount": 2046, "displayNames": [{"language": "ko", "name": "기하학", "short": "기하학"}, {"language": "en", "name": "geometry", "short": "geom"}, {"language": "ja", "name": "幾何学", "short": "幾何"}], "aliases": []}, {"key": "polygon_area", "isMeta": false, "bojTagId": 3, "problemCount": 100, "displayNames": [{"language": "ko", "name": "다각형의 넓이", "short": "다각형의 넓이"}, {"language": "en", "name": "area of a polygon", "short": "area of a polygon"}, {"language": "ja", "name": "多角形の面積", "short": "多角形の面積"}], "aliases": [{"alias": "넓이"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
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
#define sz(x) ((int)x.size())

int n;
int cost[16][16];
int memo[16][1 << 16];
int dfs(int curr, int visited) {
    if (visited + 1 == (1 << n)) return cost[curr][0];

    int &r = memo[curr][visited];
    if (r != -1) return r;

    int best = INT_MAX >> 4;
    for (int next = 0; next < n; ++next) {
        if ((visited >> next) & 1) continue;

        best = min(best, cost[curr][next] + dfs(next, visited | (1 << next)));
    }
    
    r = best;
    return best;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    cin >> n;
    vector<pair<ll,ll>> pts(n);
    for (auto &[x, y] : pts) cin >> x >> y;
    pts.push_back(pts.front());

    // shoelace
    ll sum = 0;
    for (int i = 1; i < (int)pts.size(); ++i) {
        sum += pts[i-1].first * pts[i].second - pts[i-1].second * pts[i].first;
    }
    sum = abs(sum);
    cout << (sum >> 1) << "." << ((sum & 1) * 5) << endl;
}
