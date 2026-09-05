/*
Bronze 2
1978 - 소수 찾기
meta: {"problemId": 1978, "titleKo": "소수 찾기", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "소수 찾기", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 105531, "level": 4, "votedUserCount": 150, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 2.095400094985962, "official": true, "tags": [{"key": "primality_test", "isMeta": false, "bojTagId": 9, "problemCount": 398, "displayNames": [{"language": "ko", "name": "소수 판정", "short": "소수 판정"}, {"language": "en", "name": "primality test", "short": "primality test"}, {"language": "ja", "name": "素数性テスト", "short": "素数性テスト"}], "aliases": [{"alias": "소수"}, {"alias": "소수판별"}, {"alias": "소수판정"}, {"alias": "prime"}]}, {"key": "number_theory", "isMeta": false, "bojTagId": 95, "problemCount": 1889, "displayNames": [{"language": "ko", "name": "정수론", "short": "정수론"}, {"language": "en", "name": "number theory", "short": "number theory"}, {"language": "ja", "name": "整数論", "short": "整数論"}], "aliases": []}, {"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}], "metadata": {}}
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
    int res = 0;
    while (n--) {
        int x;
        cin >> x;
        int cap = sqrt(x);
        bool prime = x > 1;
        for (int d = 2; prime && d <= cap; ++d)
            prime = x % d;
        res += prime;
    }
    cout << res << endl;
}
