/*
Gold 2
1918 - 후위 표기식
meta: {"problemId": 1918, "titleKo": "후위 표기식", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "후위 표기식", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 19117, "level": 14, "votedUserCount": 382, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.514899969100952, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "stack", "isMeta": false, "bojTagId": 71, "problemCount": 493, "displayNames": [{"language": "ko", "name": "스택", "short": "스택"}, {"language": "en", "name": "stack", "short": "stack"}, {"language": "ja", "name": "スタック", "short": "スタック"}], "aliases": []}], "metadata": {}}
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

// E = T ( ( + | - ) T )*
// T = A ( ( * | / ) A )*
// A = literal | LParen E RParen

void parseE(string &s, string &t, size_t &i);

void parseA(string &s, string &t, size_t &i) {
    if (s[i] == '(') {
        parseE(s, t, ++i);
        assert(s[i++] == ')');
    }

    if (s[i] >= 'A' && s[i] <= 'Z') {
        t += s[i++];
    }
}

void parseT(string &s, string &t, size_t &i) {
    parseA(s, t, i);

    while (s[i] == '*' || s[i] == '/') {
        char op = s[i++];
        parseA(s, t, i);
        t += op;
    }
}

void parseE(string &s, string &t, size_t &i) {
    parseT(s, t, i);

    while (s[i] == '+' || s[i] == '-') {
        char op = s[i++];
        parseT(s, t, i);
        t += op;
    }
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    string s; cin >> s;
    s = "(" + s + ")";
    
    // recursive descent parsing
    string t;
    size_t i = 0;
    parseE(s, t, i);
    cout << t << endl;
}
