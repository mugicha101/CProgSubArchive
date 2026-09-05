/*
Silver 2
11053 - 가장 긴 증가하는 부분 수열
meta: {"problemId": 11053, "titleKo": "가장 긴 증가하는 부분 수열", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "가장 긴 증가하는 부분 수열", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 58683, "level": 9, "votedUserCount": 96, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 2.555299997329712, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "lis", "isMeta": false, "bojTagId": 43, "problemCount": 123, "displayNames": [{"language": "ko", "name": "가장 긴 증가하는 부분 수열 문제", "short": "가장 긴 증가하는 부분 수열"}, {"language": "en", "name": "longest increasing sequence problem", "short": "lis"}, {"language": "ja", "name": "longest increasing sequence problem", "short": "lis"}], "aliases": []}], "metadata": {}}
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



int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    
    // lis constructive
    vector<int> lis;
    lis.reserve(n);
    while (n--) {
        int x; cin >> x;
        if (lis.empty() || x > lis.back()) lis.push_back(x);

        // bsearch for item to replace
        int l = 0, r = (int)lis.size() - 1;
        while (l != r) {
            int m = (l + r) >> 1;
            if (lis[m] >= x) r = m;
            else l = m+1;
        }
        lis[l] = x;
    }

    cout << lis.size() << endl;
}
