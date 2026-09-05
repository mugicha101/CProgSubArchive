/*
Bronze 1
1259 - Palindrome Numbers
meta: {"problemId": 1259, "titleKo": "팰린드롬수", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "팰린드롬수", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Palindrome Numbers", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 48017, "level": 5, "votedUserCount": 188, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.7558000087738037, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "string", "isMeta": false, "bojTagId": 158, "problemCount": 2964, "displayNames": [{"language": "ko", "name": "문자열", "short": "문자열"}, {"language": "en", "name": "string", "short": "string"}, {"language": "ja", "name": "文字列", "short": "文字列"}], "aliases": [{"alias": "스트링"}]}], "metadata": {}}
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

    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;

        string s = to_string(n);
        bool pal = true;
        for (int i = 0; pal && i * 2 < (int)s.size(); ++i) {
            pal = s[i] == s[(int)s.size() - 1 - i];
        }
        cout << (pal ? "yes" : "no") << endl;
    }
}
