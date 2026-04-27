/*
Platinum 5
1306 - 달려라 홍준
meta: {"problemId": 1306, "titleKo": "달려라 홍준", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "달려라 홍준", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 1735, "level": 16, "votedUserCount": 258, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.202899932861328, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "segtree", "isMeta": false, "bojTagId": 65, "problemCount": 1714, "displayNames": [{"language": "ko", "name": "세그먼트 트리", "short": "세그먼트 트리"}, {"language": "en", "name": "segment tree", "short": "segtree"}, {"language": "ja", "name": "セグメント木", "short": "セグ木"}], "aliases": [{"alias": "구간트리"}, {"alias": "세그트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "sliding_window", "isMeta": false, "bojTagId": 68, "problemCount": 134, "displayNames": [{"language": "ko", "name": "슬라이딩 윈도우", "short": "슬라이딩 윈도우"}, {"language": "en", "name": "sliding window", "short": "sliding window"}, {"language": "ja", "name": "スライディングウィンドウ", "short": "スライディングウィンドウ"}], "aliases": [{"alias": "슬라이딩윈도"}]}], "metadata": {}}
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

    int n, m; cin >> n >> m;
    int w = m * 2 - 1;
    vector<int> vals(n); vcin(vals);
    multiset<int> s;
    if (n < w) return 0;

    for (int i = 0; i < w; ++i) {
        s.insert(vals[i]);
    }
    cout << *(--s.end()) << " ";
    for (int i = w; i < n; ++i) {
        s.insert(vals[i]);
        s.erase(s.find(vals[i-w]));
        cout << *(--s.end()) << " ";
    }
    cout << "\n";
}
