/*
Silver 4
33042 - 이변마작 1
meta: {"problemId": 33042, "titleKo": "이변마작 1", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "이변마작 1", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 376, "level": 7, "votedUserCount": 34, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.3005000352859497, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "set", "isMeta": false, "bojTagId": 225, "problemCount": 1619, "displayNames": [{"language": "ko", "name": "집합과 맵", "short": "집합과 맵"}, {"language": "en", "name": "set / map", "short": "set"}], "aliases": []}, {"key": "hash_set", "isMeta": false, "bojTagId": 136, "problemCount": 789, "displayNames": [{"language": "ko", "name": "해시를 사용한 집합과 맵", "short": "해시를 사용한 집합과 맵"}, {"language": "en", "name": "set / map by hashing", "short": "hashset"}, {"language": "ja", "name": "ハッシュ化によるセット・マップ", "short": "hashset"}], "aliases": [{"alias": "집합"}, {"alias": "맵"}, {"alias": "셋"}, {"alias": "딕셔너리"}, {"alias": "dictionary"}, {"alias": "map"}, {"alias": "set"}, {"alias": "해싱"}, {"alias": "hashing"}, {"alias": "dict"}]}, {"key": "tree_set", "isMeta": false, "bojTagId": 74, "problemCount": 541, "displayNames": [{"language": "ko", "name": "트리를 사용한 집합과 맵", "short": "트리를 사용한 집합과 맵"}, {"language": "en", "name": "set / map by trees", "short": "treeset"}, {"language": "ja", "name": "木によるセット・マップ", "short": "treeset"}], "aliases": [{"alias": "집합"}, {"alias": "맵"}, {"alias": "셋"}, {"alias": "딕셔너리"}, {"alias": "dictionary"}, {"alias": "map"}, {"alias": "set"}, {"alias": "bbst"}, {"alias": "트리"}, {"alias": "tree"}]}], "metadata": {}}
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

    int n; cin >> n;
    unordered_map<string,int> cnt;
    for (int i = 1; i <= n; ++i) {
        string t; cin >> t;
        if (++cnt[t] == 5) {
            cout << i << "\n";
            return 0;
        }
    }
    cout << "0\n";
}
