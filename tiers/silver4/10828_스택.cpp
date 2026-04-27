/*
Silver 4
10828 - 스택
meta: {"problemId": 10828, "titleKo": "스택", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "스택", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 90699, "level": 7, "votedUserCount": 177, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.543100118637085, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "stack", "isMeta": false, "bojTagId": 71, "problemCount": 493, "displayNames": [{"language": "ko", "name": "스택", "short": "스택"}, {"language": "en", "name": "stack", "short": "stack"}, {"language": "ja", "name": "スタック", "short": "スタック"}], "aliases": []}], "metadata": {}}
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

    stack<int> s;
    int n; cin >> n;
    while (n--) {
        string op; cin >> op;
        if (op == "push") {
            int x; cin >> x; s.push(x);
        } else if (op == "pop") {
            if (s.empty()) cout << -1 << "\n";
            else {
                cout << s.top() << "\n";
                s.pop();
            }
        } else if (op == "top") cout << (s.empty() ? -1 : s.top()) << "\n";
        else if (op == "empty") cout << s.empty() << "\n";
        else cout << s.size() << "\n";
    }
}
