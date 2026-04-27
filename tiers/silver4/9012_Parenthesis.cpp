/*
Silver 4
9012 - Parenthesis
meta: {"problemId": 9012, "titleKo": "괄호", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "괄호", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Parenthesis", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 95668, "level": 7, "votedUserCount": 161, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.108799934387207, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "string", "isMeta": false, "bojTagId": 158, "problemCount": 2964, "displayNames": [{"language": "ko", "name": "문자열", "short": "문자열"}, {"language": "en", "name": "string", "short": "string"}, {"language": "ja", "name": "文字列", "short": "文字列"}], "aliases": [{"alias": "스트링"}]}, {"key": "stack", "isMeta": false, "bojTagId": 71, "problemCount": 493, "displayNames": [{"language": "ko", "name": "스택", "short": "스택"}, {"language": "en", "name": "stack", "short": "stack"}, {"language": "ja", "name": "スタック", "short": "スタック"}], "aliases": []}], "metadata": {}}
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
    while (n--) {
        string s;
        cin >> s;
        int bal = 0;
        for (int i = 0; bal >= 0 && i < (int)s.size(); ++i) {
            bal += s[i] == '(' ? 1 : -1;
        }
        cout << (bal ? "NO" : "YES") << endl;
    }
}
