/*
Silver 4
1764 - 듣보잡
meta: {"problemId": 1764, "titleKo": "듣보잡", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "듣보잡", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 55647, "level": 7, "votedUserCount": 202, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.3345000743865967, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "string", "isMeta": false, "bojTagId": 158, "problemCount": 2964, "displayNames": [{"language": "ko", "name": "문자열", "short": "문자열"}, {"language": "en", "name": "string", "short": "string"}, {"language": "ja", "name": "文字列", "short": "文字列"}], "aliases": [{"alias": "스트링"}]}, {"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}, {"key": "set", "isMeta": false, "bojTagId": 225, "problemCount": 1619, "displayNames": [{"language": "ko", "name": "집합과 맵", "short": "집합과 맵"}, {"language": "en", "name": "set / map", "short": "set"}], "aliases": []}, {"key": "hash_set", "isMeta": false, "bojTagId": 136, "problemCount": 789, "displayNames": [{"language": "ko", "name": "해시를 사용한 집합과 맵", "short": "해시를 사용한 집합과 맵"}, {"language": "en", "name": "set / map by hashing", "short": "hashset"}, {"language": "ja", "name": "ハッシュ化によるセット・マップ", "short": "hashset"}], "aliases": [{"alias": "집합"}, {"alias": "맵"}, {"alias": "셋"}, {"alias": "딕셔너리"}, {"alias": "dictionary"}, {"alias": "map"}, {"alias": "set"}, {"alias": "해싱"}, {"alias": "hashing"}, {"alias": "dict"}]}], "metadata": {}}
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

    int n, q; cin >> n >> q;
    unordered_map<string, int> count;
    while (n--) {
        string s; cin >> s; ++count[s];
    }
    while (q--) {
        string s; cin >> s; ++count[s];
    }
    vector<string> out;
    for (auto &[name, c] : count) if (c == 2) out.push_back(name);
    cout << out.size() << endl;
    sort(all(out));
    for (string &s : out) cout << s << endl;
}
