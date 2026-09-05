/*
Silver 4
2164 - 카드2
meta: {"problemId": 2164, "titleKo": "카드2", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "카드2", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 72426, "level": 7, "votedUserCount": 163, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.9456000328063965, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "queue", "isMeta": false, "bojTagId": 72, "problemCount": 74, "displayNames": [{"language": "ko", "name": "큐", "short": "큐"}, {"language": "en", "name": "queue", "short": "queue"}, {"language": "ja", "name": "キュー", "short": "キュー"}], "aliases": []}], "metadata": {}}
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

    int n;
    cin >> n;
    queue<int> q;
    for (int i = 1; i <= n; ++i) q.push(i);
    while (q.size() > 1) {
        q.pop();
        int x = q.front();
        q.pop();
        q.push(x);
    }
    cout << q.front() << endl;
}
