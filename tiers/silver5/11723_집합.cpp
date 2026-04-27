/*
Silver 5
11723 - 집합
meta: {"problemId": 11723, "titleKo": "집합", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "집합", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 38291, "level": 6, "votedUserCount": 195, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.2923998832702637, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "set", "isMeta": false, "bojTagId": 225, "problemCount": 1619, "displayNames": [{"language": "ko", "name": "집합과 맵", "short": "집합과 맵"}, {"language": "en", "name": "set / map", "short": "set"}], "aliases": []}, {"key": "bitmask", "isMeta": false, "bojTagId": 14, "problemCount": 1027, "displayNames": [{"language": "ko", "name": "비트마스킹", "short": "비트마스킹"}, {"language": "en", "name": "bitmask", "short": "bitmask"}, {"language": "ja", "name": "ビット表現", "short": "ビット表現"}], "aliases": [{"alias": "비트필드"}, {"alias": "비트마스크"}]}], "metadata": {}}
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

    int q;
    cin >> q;
    bitset<20> s;
    while (q--) {
        string type;
        cin >> type;
        if (type == "add") {
            int p;
            cin >> p;
            s[p-1] = 1;
        } else if (type == "remove") {
            int p;
            cin >> p;
            s[p-1] = 0;
        } else if (type == "check") {
            int p;
            cin >> p;
            cout << s[p-1] << "\n";
        } else if (type == "toggle") {
            int p;
            cin >> p;
            s[p-1] = !s[p-1];
        } else if (type == "all") {
            for (int p = 0; p < 20; ++p) s[p] = 1;
        } else if (type == "empty") s.reset();
    }
}
