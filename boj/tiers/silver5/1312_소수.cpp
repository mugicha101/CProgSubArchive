/*
Silver 5
1312 - 소수
meta: {"problemId": 1312, "titleKo": "소수", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "소수", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 6949, "level": 6, "votedUserCount": 116, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.853600025177002, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}], "metadata": {}}
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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int a, b, n;
    cin >> a >> b >> n;

    // long division
    a = a % b;
    int d = 0;
    for (int i = 0; i < n; ++i) {
        a = a * 10;
        d = a / b;
        a = a - d * b;
    }
    cout << d << endl;
}
