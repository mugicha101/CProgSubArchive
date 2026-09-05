/*
Bronze 1
1546 - 평균
meta: {"problemId": 1546, "titleKo": "평균", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "평균", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 150198, "level": 5, "votedUserCount": 201, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.9673999547958374, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "arithmetic", "isMeta": false, "bojTagId": 121, "problemCount": 1374, "displayNames": [{"language": "ko", "name": "사칙연산", "short": "사칙연산"}, {"language": "en", "name": "arithmetic", "short": "arithmetic"}, {"language": "ja", "name": "算数", "short": "算数"}], "aliases": [{"alias": "덧셈"}, {"alias": "뺄셈"}, {"alias": "곱셈"}, {"alias": "나눗셈"}, {"alias": "더하기"}, {"alias": "빼기"}, {"alias": "곱하기"}, {"alias": "나누기"}]}], "metadata": {}}
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
    vector<int> vals(n);
    for (int &x : vals) cin >> x;
    cout << ((double)accumulate(all(vals), 0) * 100. / (double)n / (double)*max_element(all(vals))) << endl;
}
