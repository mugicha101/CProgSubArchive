/*
Platinum 4
32816 - Repetitive Routes
meta: {"problemId": 32816, "titleKo": "Repetitive Routes", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Repetitive Routes", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 11, "level": 17, "votedUserCount": 2, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.5455000400543213, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "segtree", "isMeta": false, "bojTagId": 65, "problemCount": 1714, "displayNames": [{"language": "ko", "name": "세그먼트 트리", "short": "세그먼트 트리"}, {"language": "en", "name": "segment tree", "short": "segtree"}, {"language": "ja", "name": "セグメント木", "short": "セグ木"}], "aliases": [{"alias": "구간트리"}, {"alias": "세그트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "set", "isMeta": false, "bojTagId": 225, "problemCount": 1619, "displayNames": [{"language": "ko", "name": "집합과 맵", "short": "집합과 맵"}, {"language": "en", "name": "set / map", "short": "set"}], "aliases": []}, {"key": "offline_queries", "isMeta": false, "bojTagId": 123, "problemCount": 372, "displayNames": [{"language": "ko", "name": "오프라인 쿼리", "short": "오프라인 쿼리"}, {"language": "en", "name": "offline queries", "short": "offline query"}, {"language": "ja", "name": "offline queries", "short": "offline query"}], "aliases": [{"alias": "offlinequery"}]}, {"key": "mo", "isMeta": false, "bojTagId": 50, "problemCount": 51, "displayNames": [{"language": "ko", "name": "mo's", "short": "Mo's"}, {"language": "en", "name": "mo's", "short": "mo's"}, {"language": "ja", "name": "mo's", "short": "mo's"}], "aliases": [{"alias": "squarerootdecomposition"}, {"alias": "sqrtdecomposition"}, {"alias": "평방분할법"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000007
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

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

#define EPS 1e-9
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int n;
    cin >> n;

    unordered_map<int, int> passengers; // passenger -> enter time
    ordered_set<int> enterTimes; // all active enter times
    unordered_map<int, int> locLast; // last time this location was visited
    ll complaints = 0;
    int nextLoc = 1;
    for (int i = 0; i < n * 2; ++i) {
        int c, l;
        cin >> c >> l;
        if (l == nextLoc) {
            // new location
            ++nextLoc;
        } else {
            // duplicate location
            // count passengers who got on before or at last loc (duplicate for them)
            complaints += enterTimes.order_of_key(locLast[l]+1);
        }
        locLast[l] = i;

        if (passengers.count(c)) {
            enterTimes.erase(enterTimes.find(passengers[c]));
            passengers.erase(c);
        } else {
            enterTimes.insert(i);
            passengers[c] = i;
        }
    }
    cout << complaints << endl;
}
