/*
Silver 3
1463 - 1로 만들기
meta: {"problemId": 1463, "titleKo": "1로 만들기", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "1로 만들기", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 87994, "level": 8, "votedUserCount": 127, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 2.9260001182556152, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}], "metadata": {}}
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

    int x; cin >> x;
    
    // start from 1, find min dist to x using dp
    // ops: x2, x3, +1
    vector<int> minDist(x+1, INT_MAX);
    minDist[1] = 0;
    for (int v = 1; v < x; ++v) {
        auto update = [&](int nv) {
            if (nv <= x) minDist[nv] = min(minDist[nv], minDist[v] + 1);
        };
        update(v + 1);
        update(v * 2);
        update(v * 3);
    }
    cout << minDist[x] << endl;
}
