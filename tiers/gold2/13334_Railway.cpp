/*
Gold 2
13334 - Railway
meta: {"problemId": 13334, "titleKo": "철로", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "철로", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Railway", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 4377, "level": 14, "votedUserCount": 291, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.5278000831604004, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}, {"key": "sweeping", "isMeta": false, "bojTagId": 106, "problemCount": 708, "displayNames": [{"language": "ko", "name": "스위핑", "short": "스위핑"}, {"language": "en", "name": "sweeping", "short": "sweeping"}, {"language": "ja", "name": "平面走査", "short": "平面走査"}], "aliases": [{"alias": "라인 스위핑"}]}, {"key": "priority_queue", "isMeta": false, "bojTagId": 59, "problemCount": 575, "displayNames": [{"language": "ko", "name": "우선순위 큐", "short": "우선순위 큐"}, {"language": "en", "name": "priority queue", "short": "priority queue"}, {"language": "ja", "name": "優先度付きキュー", "short": "優先度付きキュー"}], "aliases": [{"alias": "heap"}, {"alias": "힙"}]}], "metadata": {}}
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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<pair<int,int>> itvs(n);
    vector<pair<int,int>> points;
    points.reserve(n * 2);
    set<int> uniquePoints;
    for (int i = 0; i < (int)itvs.size(); ++i) {
        auto &[s, e] = itvs[i];
        cin >> s >> e;
        points.emplace_back(s, i);
        points.emplace_back(e, i);
        uniquePoints.insert(s);
        uniquePoints.insert(e);
    }
    int d; cin >> d;

    // sliding window on sorted points
    // keep track of how many people have both their points in the window (cover = 2)
    vector<int> cover(n);
    sort(all(points));
    int next = 0;
    int peopleCovered = 0;
    int maxPeopleCovered = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> window;
    for (int x : uniquePoints) {
        // window [x, x+d]
        // remove points from window
        while (!window.empty() && window.top().first < x) {
            peopleCovered -= --cover[window.top().second] == 1;
            window.pop();
        }
        // add points to window
        while (next < (int)points.size() && points[next].first <= x + d) {
            peopleCovered += ++cover[points[next].second] == 2;
            window.push(points[next++]);
        }
        maxPeopleCovered = max(maxPeopleCovered, peopleCovered);
    }
    cout << maxPeopleCovered << "\n";
}
