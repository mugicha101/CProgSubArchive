/*
Silver 4
11866 - 요세푸스 문제 0
meta: {"problemId": 11866, "titleKo": "요세푸스 문제 0", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "요세푸스 문제 0", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 54458, "level": 7, "votedUserCount": 180, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.7467000484466553, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "queue", "isMeta": false, "bojTagId": 72, "problemCount": 74, "displayNames": [{"language": "ko", "name": "큐", "short": "큐"}, {"language": "en", "name": "queue", "short": "queue"}, {"language": "ja", "name": "キュー", "short": "キュー"}], "aliases": []}], "metadata": {}}
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

    int n, k; cin >> n >> k;
    int pos = n-1;
    vector<bool> circle(n, true);
    cout << "<";
    for (int i = 0; i < n; ++i) {
        int t = k;
        while (t > 0) {
            pos = (pos + 1) % n;
            t -= circle[pos];
        }
        circle[pos] = false;
        cout << (pos + 1);
        if (i+1 < n) cout << ", ";
    }
    cout << ">\n";
}
