/*
Gold 1
2433 - The Sound of Silence
meta: {"problemId": 2433, "titleKo": "The Sound of Silence", "titles": [{"language": "en", "languageDisplayName": "en", "title": "The Sound of Silence", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 201, "level": 15, "votedUserCount": 45, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.756200075149536, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "deque", "isMeta": false, "bojTagId": 73, "problemCount": 163, "displayNames": [{"language": "ko", "name": "덱", "short": "덱"}, {"language": "en", "name": "deque", "short": "deque"}, {"language": "ja", "name": "両端キュー", "short": "deque"}], "aliases": []}, {"key": "sliding_window", "isMeta": false, "bojTagId": 68, "problemCount": 134, "displayNames": [{"language": "ko", "name": "슬라이딩 윈도우", "short": "슬라이딩 윈도우"}, {"language": "en", "name": "sliding window", "short": "sliding window"}, {"language": "ja", "name": "スライディングウィンドウ", "short": "スライディングウィンドウ"}], "aliases": [{"alias": "슬라이딩윈도"}]}, {"key": "deque_trick", "isMeta": false, "bojTagId": 216, "problemCount": 67, "displayNames": [{"language": "ko", "name": "덱을 이용한 구간 최댓값 트릭", "short": "덱 트릭"}, {"language": "en", "name": "deque range maximum trick", "short": "deque rmq trick"}, {"language": "ja", "name": "deque range maximum trick", "short": "deque rmq trick"}], "aliases": []}], "metadata": {}}
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
// #define endl "\n"

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int n, m, c; cin >> n >> m >> c;
    vector<int> vals(n); vcin(vals);
    vector<int> res;
    multiset<int> window;
    for (int i = 0; i < n; ++i) {
        window.insert(vals[i]);
        if (i < m-1) continue;
        if (i >= m) window.erase(window.find(vals[i-m]));
        if (*(--window.end()) - *window.begin() <= c) res.push_back(i-m+2);
    }
    if (res.empty()) cout << "NONE";
    else {
        for (int x : res) cout << x << "\n";
    }
}
