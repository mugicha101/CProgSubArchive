/*
Gold 1
2070 - Necklace Decomposition
meta: {"problemId": 2070, "titleKo": "목걸이 수열", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "목걸이 수열", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Necklace Decomposition", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 64, "level": 15, "votedUserCount": 15, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.75, "official": true, "tags": [{"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}, {"key": "string", "isMeta": false, "bojTagId": 158, "problemCount": 2964, "displayNames": [{"language": "ko", "name": "문자열", "short": "문자열"}, {"language": "en", "name": "string", "short": "string"}, {"language": "ja", "name": "文字列", "short": "文字列"}], "aliases": [{"alias": "스트링"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    string s; cin >> s;

    // O(N^2)
    auto isNeck = [](string s) {
        // rotate s to see if a string is less than it
        string t = s;
        for (int i = 1; i < (int)s.size(); ++i) {
            rotate(t.begin(), t.begin() + 1, t.end());
            if (t < s) return false;
        }
        return true;
    };

    // greedily extend each segment as far as possible
    // O(N^2)
    int start = 0;
    while (start < (int)s.size()) {
        int end = (int)s.size();
        while (!isNeck(s.substr(start, end - start))) --end;
        cout << "(" << s.substr(start, end - start) << ")";
        start = end;
    }
}
