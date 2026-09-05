/*
Gold 4
1806 - Subsequence
meta: {"problemId": 1806, "titleKo": "부분합", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "부분합", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Subsequence", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 28910, "level": 12, "votedUserCount": 372, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.6568000316619873, "official": true, "tags": [{"key": "prefix_sum", "isMeta": false, "bojTagId": 139, "problemCount": 1379, "displayNames": [{"language": "ko", "name": "누적 합", "short": "누적 합"}, {"language": "en", "name": "prefix sum", "short": "prefix sum"}, {"language": "ja", "name": "累積和", "short": "累積和"}], "aliases": [{"alias": "구간합"}, {"alias": "부분합"}, {"alias": "rangesum"}]}, {"key": "two_pointer", "isMeta": false, "bojTagId": 80, "problemCount": 490, "displayNames": [{"language": "ko", "name": "두 포인터", "short": "두 포인터"}, {"language": "en", "name": "two-pointer", "short": "two-pointer"}, {"language": "ja", "name": "尺取り法", "short": "尺取り"}], "aliases": [{"alias": "투포인터"}, {"alias": "인치웜"}, {"alias": "inchworm"}, {"alias": "twopointer"}]}], "metadata": {}}
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

    int n, k; cin >> n >> k;
    vector<int> arr(n);
    for (int &x : arr) cin >> x;
    int j = 0;
    int sum = 0;
    int best = INT_MAX;
    for (int i = 0; i < (int)arr.size(); ++i) {
        sum += arr[i];
        while (sum >= k) {
            best = min(best, i + 1 - j);
            sum -= arr[j++];
        }
    }
    cout << (best == INT_MAX ? 0 : best) << endl;
}
