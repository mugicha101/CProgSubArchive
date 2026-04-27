/*
Bronze 1
11050 - 이항 계수 1
meta: {"problemId": 11050, "titleKo": "이항 계수 1", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "이항 계수 1", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 53476, "level": 5, "votedUserCount": 139, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.5437999963760376, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "combinatorics", "isMeta": false, "bojTagId": 6, "problemCount": 1292, "displayNames": [{"language": "ko", "name": "조합론", "short": "조합론"}, {"language": "en", "name": "combinatorics", "short": "combinatorics"}, {"language": "ja", "name": "組み合わせ", "short": "組み合わせ"}], "aliases": [{"alias": "combination"}, {"alias": "permutation"}, {"alias": "probability"}, {"alias": "확률"}, {"alias": "순열"}]}], "metadata": {}}
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

    int n, k;
    cin >> n >> k;

    auto fac = [](int x) {
        if (x <= 1) return 1;
        int m = x;
        while (--x > 1) m *= x;
        return m;
    };
    cout << fac(n) / fac(k) /  fac(n - k) << endl;
}
