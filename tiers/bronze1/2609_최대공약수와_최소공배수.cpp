/*
Bronze 1
2609 - 최대공약수와 최소공배수
meta: {"problemId": 2609, "titleKo": "최대공약수와 최소공배수", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "최대공약수와 최소공배수", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 70303, "level": 5, "votedUserCount": 189, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.7294000387191772, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "number_theory", "isMeta": false, "bojTagId": 95, "problemCount": 1889, "displayNames": [{"language": "ko", "name": "정수론", "short": "정수론"}, {"language": "en", "name": "number theory", "short": "number theory"}, {"language": "ja", "name": "整数論", "short": "整数論"}], "aliases": []}, {"key": "euclidean", "isMeta": false, "bojTagId": 26, "problemCount": 268, "displayNames": [{"language": "ko", "name": "유클리드 호제법", "short": "유클리드 호제법"}, {"language": "en", "name": "euclidean algorithm", "short": "euclidean algorithm"}, {"language": "ja", "name": "ユークリッドの互除法", "short": "ユークリッドの互除法"}], "aliases": [{"alias": "유클리드알고리즘"}]}], "metadata": {}}
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

    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << "\n" << lcm(a, b) << endl;
}
