/*
Gold 2
12015 - 가장 긴 증가하는 부분 수열 2
meta: {"problemId": 12015, "titleKo": "가장 긴 증가하는 부분 수열 2", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "가장 긴 증가하는 부분 수열 2", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 21214, "level": 14, "votedUserCount": 349, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.336699962615967, "official": true, "tags": [{"key": "binary_search", "isMeta": false, "bojTagId": 12, "problemCount": 1665, "displayNames": [{"language": "ko", "name": "이분 탐색", "short": "이분 탐색"}, {"language": "en", "name": "binary search", "short": "binary search"}, {"language": "ja", "name": "二分探索", "short": "二分探索"}], "aliases": [{"alias": "이분탐색"}, {"alias": "이진탐색"}]}, {"key": "lis", "isMeta": false, "bojTagId": 43, "problemCount": 123, "displayNames": [{"language": "ko", "name": "가장 긴 증가하는 부분 수열 문제", "short": "가장 긴 증가하는 부분 수열"}, {"language": "en", "name": "longest increasing sequence problem", "short": "lis"}, {"language": "ja", "name": "longest increasing sequence problem", "short": "lis"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned int uint;
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
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

#include <bits/stdc++.h>
using namespace std;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // lis constructive
    int n; cin >> n;
    vector<int> vals(n); vcin(vals);
    vector<int> s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x = vals[i];
        if (s.empty() || s.back() < x) {
            s.push_back(x);
            continue;
        }

        *lower_bound(s.begin(), s.end(), x) = x;
    }
    cout << s.size() << endl;
}
