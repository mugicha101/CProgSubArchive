/*
Gold 5
1931 - 회의실 배정
meta: {"problemId": 1931, "titleKo": "회의실 배정", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "회의실 배정", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 66356, "level": 11, "votedUserCount": 355, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.088099956512451, "official": true, "tags": [{"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}, {"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}], "metadata": {}}
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

    int n;
    cin >> n;
    vector<pair<int,int>> itvs(n);
    for (auto &[start, end] : itvs) cin >> start >> end;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> ends; // end, chain len
    sort(all(itvs));
    int chain = 0;
    for (auto &[start, end] : itvs) {
        while (!ends.empty() && ends.top().first <= start) {
            chain = max(chain, ends.top().second);
            ends.pop();
        }
        ends.emplace(end, chain + 1);
    }
    while (!ends.empty()) {
        chain = max(chain, ends.top().second);
        ends.pop();
    }
    cout << chain << endl;
}
