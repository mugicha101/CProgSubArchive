/*
Gold 2
7453 - 4 Values whose Sum is 0
meta: {"problemId": 7453, "titleKo": "합이 0인 네 정수", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "합이 0인 네 정수", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "4 Values whose Sum is 0", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 9026, "level": 14, "votedUserCount": 333, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.251299858093262, "official": true, "tags": [{"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}, {"key": "binary_search", "isMeta": false, "bojTagId": 12, "problemCount": 1665, "displayNames": [{"language": "ko", "name": "이분 탐색", "short": "이분 탐색"}, {"language": "en", "name": "binary search", "short": "binary search"}, {"language": "ja", "name": "二分探索", "short": "二分探索"}], "aliases": [{"alias": "이분탐색"}, {"alias": "이진탐색"}]}, {"key": "two_pointer", "isMeta": false, "bojTagId": 80, "problemCount": 490, "displayNames": [{"language": "ko", "name": "두 포인터", "short": "두 포인터"}, {"language": "en", "name": "two-pointer", "short": "two-pointer"}, {"language": "ja", "name": "尺取り法", "short": "尺取り"}], "aliases": [{"alias": "투포인터"}, {"alias": "인치웜"}, {"alias": "inchworm"}, {"alias": "twopointer"}]}, {"key": "mitm", "isMeta": false, "bojTagId": 46, "problemCount": 124, "displayNames": [{"language": "ko", "name": "중간에서 만나기", "short": "중간에서 만나기"}, {"language": "en", "name": "meet in the middle", "short": "meet in the middle"}, {"language": "ja", "name": "半分全列挙", "short": "半分全列挙"}], "aliases": []}], "metadata": {}}
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

#include <bits/stdc++.h>
using namespace std;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    vector<int> c(n);
    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }

    // n^2 = 1.6 * 10^7 possible sums for a[i], b[j]
    // memory: 3.2 * 10^7 * sizeof(int) = 1.28 * 10^8 bytes = 128 MB for a, b and c, d pairs
    vector<int> ab; ab.reserve(a.size() * b.size());
    vector<int> cd; cd.reserve(c.size() * d.size());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ab.push_back(a[i] + b[j]);
            cd.push_back(c[i] + d[j]);
        }
    }
    sort(all(ab));
    sort(all(cd), greater<int>());
    int i = 0;
    int j = 0;
    ll sum = 0;
    while (i < (int)ab.size()) {
        int v = ab[i];
        int iAmt = 0;
        while (i+iAmt < (int)ab.size() && ab[i+iAmt] == v) ++iAmt;
        i += iAmt;

        while (j < (int)cd.size() && cd[j] > -v) ++j;
        int jAmt = 0;
        while (j+jAmt < (int)cd.size() && cd[j+jAmt] == -v) ++jAmt;
        j += jAmt;
        
        sum += (ll)iAmt * (ll)jAmt;
    }
    cout << sum << endl;
}
