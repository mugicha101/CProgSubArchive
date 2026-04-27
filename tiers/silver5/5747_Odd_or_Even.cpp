/*
Silver 5
5747 - Odd or Even
meta: {"problemId": 5747, "titleKo": "Odd or Even", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Odd or Even", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 125, "level": 6, "votedUserCount": 15, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.1679999828338623, "official": true, "tags": [{"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}, {"key": "parity", "isMeta": false, "bojTagId": 230, "problemCount": 215, "displayNames": [{"language": "ko", "name": "홀짝성", "short": "홀짝성"}, {"language": "en", "name": "parity", "short": "parity"}], "aliases": []}], "metadata": {}}
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

    while (true) {
        int n; cin >> n; if (n == 0) break;
        int mary[2] = {};
        int john[2] = {};
        for (int i = 0; i < n; ++i) {
            int x; cin >> x; ++mary[x&1];
        }
        for (int i = 0; i < n; ++i) {
            int x; cin >> x; ++john[x&1];
        }
        
        // want to maximize odd sums
        // match odd with even
        // match even with odd
        // remaining is guaranteed even
        int d = min(mary[0], john[1]);
        mary[0] -= d;
        john[1] -= d;
        d = min(mary[1], john[0]);
        mary[1] -= d;
        john[0] -= d;
        cout << (mary[0] + mary[1] + john[0] + john[1]) / 2 << endl;  
    }
}
