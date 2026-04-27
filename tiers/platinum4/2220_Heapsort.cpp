/*
Platinum 4
2220 - Heapsort
meta: {"problemId": 2220, "titleKo": "힙 정렬", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "힙 정렬", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Heapsort", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 692, "level": 17, "votedUserCount": 58, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.7818000316619873, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}], "metadata": {}}
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

    // go reverse:
    // push x at h[end]
    // swap(h[0], h[end])
    // bubble h[end] up
    int n; cin >> n;
    vector<int> h;
    for (int x = 1; x < n; ++x) {
        h.push_back(x);
        swap(h[0], h.back());
        int i = (int)h.size()-1;
        while (i) {
            int p = (i-1) >> 1;
            swap(h[i], h[p]);
            i = p;
        }
    }
    h.push_back(n);
    swap(h[0], h.back());
    for (int x : h) cout << x << " ";
    cout << "\n";

    // 6:
    // 6 5 3 2 4 1
    // 1 5 3 2 4
    // 5 1 3 2 4
    // 5 4 3 2 1
    // 1 4 3 2
    // 4 1 3 2
    // 4 3 1 2
    // 2 3 1
    // 3 2 1
    // 1 2
    // 2 1
    // 1

    // 6 5 3 2 4 1
    // 1 5 3 2 4
    // 5 1 3 2 4
    // 5 4 3 2 1
    // 1 4 3 2
    // 4 1 3 2
    // 4 3 1 2
    // 2 3 1
    // 3 2 1
    // 1 2
    // 2 1
    // 1
}
