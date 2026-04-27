/*
Silver 2
1927 - 최소 힙
meta: {"problemId": 1927, "titleKo": "최소 힙", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "최소 힙", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 46479, "level": 9, "votedUserCount": 219, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.9961999654769897, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "priority_queue", "isMeta": false, "bojTagId": 59, "problemCount": 575, "displayNames": [{"language": "ko", "name": "우선순위 큐", "short": "우선순위 큐"}, {"language": "en", "name": "priority queue", "short": "priority queue"}, {"language": "ja", "name": "優先度付きキュー", "short": "優先度付きキュー"}], "aliases": [{"alias": "heap"}, {"alias": "힙"}]}], "metadata": {}}
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
    priority_queue<int, vector<int>, greater<int>> pq;
    while (n--) {
        int x; cin >> x;
        if (x) {
            pq.push(x);
        } else if (pq.empty()) {
            cout << 0 << "\n";
        } else {
            cout << pq.top() << "\n";
            pq.pop();
        }
    }
}
