/*
Bronze 5
3003 - BIJELE
meta: {"problemId": 3003, "titleKo": "킹, 퀸, 룩, 비숍, 나이트, 폰", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "킹, 퀸, 룩, 비숍, 나이트, 폰", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "BIJELE", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 85771, "level": 1, "votedUserCount": 85, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 1.6527999639511108, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "arithmetic", "isMeta": false, "bojTagId": 121, "problemCount": 1374, "displayNames": [{"language": "ko", "name": "사칙연산", "short": "사칙연산"}, {"language": "en", "name": "arithmetic", "short": "arithmetic"}, {"language": "ja", "name": "算数", "short": "算数"}], "aliases": [{"alias": "덧셈"}, {"alias": "뺄셈"}, {"alias": "곱셈"}, {"alias": "나눗셈"}, {"alias": "더하기"}, {"alias": "빼기"}, {"alias": "곱하기"}, {"alias": "나누기"}]}, {"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

// using namespace __gnu_pbds;
// template <class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000007

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
pair<T,U> operator-(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    }
    os << "]";
    return os;
}

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);
    int c[6] = {1, 1, 2, 2, 2, 8};
    for (int i = 0; i < 6; ++i) {
        int x; cin >> x; cout << c[i] - x << " ";
    }
    cout << "\n";
}
