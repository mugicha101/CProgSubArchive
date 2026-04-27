/*
Silver 3
11659 - 구간 합 구하기 4
meta: {"problemId": 11659, "titleKo": "구간 합 구하기 4", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "구간 합 구하기 4", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 54459, "level": 8, "votedUserCount": 202, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.582900047302246, "official": true, "tags": [{"key": "prefix_sum", "isMeta": false, "bojTagId": 139, "problemCount": 1379, "displayNames": [{"language": "ko", "name": "누적 합", "short": "누적 합"}, {"language": "en", "name": "prefix sum", "short": "prefix sum"}, {"language": "ja", "name": "累積和", "short": "累積和"}], "aliases": [{"alias": "구간합"}, {"alias": "부분합"}, {"alias": "rangesum"}]}], "metadata": {}}
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

    int n, q;
    cin >> n >> q;
    vector<int> psum(n+1);
    for (int i = 0; i < n; ++i) {
        cin >> psum[i+1];
        psum[i+1] += psum[i];
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << psum[r] - psum[l-1] << "\n";
    }
}
