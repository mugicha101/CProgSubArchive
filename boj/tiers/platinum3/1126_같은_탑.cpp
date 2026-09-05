/*
Platinum 3
1126 - 같은 탑
meta: {"problemId": 1126, "titleKo": "같은 탑", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "같은 탑", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 2316, "level": 18, "votedUserCount": 271, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.4249000549316406, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}], "metadata": {}}
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

    // given set of values S of size n
    // want to find largest h such that can choose 2 disjoint subsets in S that sum to h
    // n <= 50
    // sum of S <= 500,000 = 5 * 10^5

    // naive dp
    // dp state: (index, height of A, height of B) -> reachable
    // at block b, can either add b to A, add b to B, skip i
    // too many states: 10^11
\
    // alt dp
    // dp state: (index, sum(A) - sum(B)) -> sum(A) (note: sum(A) > sum(B))
    // up to 50 * 5 * 10^5 states = 2.5 * 10^7
    // let h = height of block i-1
    // transition: dp[i][d] = max(
    //                              dp[i-1][d]                  dont add h
    //                    if d >= h: dp[i-1][d-h] + h           add h to a (a stays a)
    //                    if d < h: dp[i-1][h-d] + d            add h to b (b becomes a)
    //                              dp[i-1][d+h]                add h to b (b stays b)
    const int H = 500001;
    vector<int> curr(H * 2, INT_MIN);
    vector<int> next(H * 2, INT_MIN);
    curr[0] = 0;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int h; cin >> h;
        for (int d = 0; d < H; ++d) {
            next[d] = max({curr[d], curr[d+h], d >= h ? curr[d-h] + h : curr[h-d] + d});
        }
        swap(curr, next);
    }
    cout << (curr[0] - (curr[0] == 0)) << endl;
}
