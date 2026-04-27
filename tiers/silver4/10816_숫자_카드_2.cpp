/*
Silver 4
10816 - 숫자 카드 2
meta: {"problemId": 10816, "titleKo": "숫자 카드 2", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "숫자 카드 2", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 61003, "level": 7, "votedUserCount": 173, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.514400005340576, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}, {"key": "binary_search", "isMeta": false, "bojTagId": 12, "problemCount": 1665, "displayNames": [{"language": "ko", "name": "이분 탐색", "short": "이분 탐색"}, {"language": "en", "name": "binary search", "short": "binary search"}, {"language": "ja", "name": "二分探索", "short": "二分探索"}], "aliases": [{"alias": "이분탐색"}, {"alias": "이진탐색"}]}, {"key": "set", "isMeta": false, "bojTagId": 225, "problemCount": 1619, "displayNames": [{"language": "ko", "name": "집합과 맵", "short": "집합과 맵"}, {"language": "en", "name": "set / map", "short": "set"}], "aliases": []}, {"key": "hash_set", "isMeta": false, "bojTagId": 136, "problemCount": 789, "displayNames": [{"language": "ko", "name": "해시를 사용한 집합과 맵", "short": "해시를 사용한 집합과 맵"}, {"language": "en", "name": "set / map by hashing", "short": "hashset"}, {"language": "ja", "name": "ハッシュ化によるセット・マップ", "short": "hashset"}], "aliases": [{"alias": "집합"}, {"alias": "맵"}, {"alias": "셋"}, {"alias": "딕셔너리"}, {"alias": "dictionary"}, {"alias": "map"}, {"alias": "set"}, {"alias": "해싱"}, {"alias": "hashing"}, {"alias": "dict"}]}], "metadata": {}}
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
    unordered_map<int, int> count;
    while (n--) {
        int x; cin >> x; ++count[x];
    }
    cin >> n;
    while (n--) {
        int x; cin >> x; cout << count[x] << " ";
    }
    cout << endl;
}
