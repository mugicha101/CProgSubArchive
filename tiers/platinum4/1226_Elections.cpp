/*
Platinum 4
1226 - Elections
meta: {"problemId": 1226, "titleKo": "국회", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "국회", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Elections", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 330, "level": 17, "votedUserCount": 71, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.0423998832702637, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}, {"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}, {"key": "knapsack", "isMeta": false, "bojTagId": 148, "problemCount": 345, "displayNames": [{"language": "ko", "name": "배낭 문제", "short": "배낭"}, {"language": "en", "name": "knapsack", "short": "knapsack"}, {"language": "ja", "name": "ナップサック問題", "short": "ナップサック"}], "aliases": [{"alias": "냅색"}]}, {"key": "traceback", "isMeta": false, "bojTagId": 235, "problemCount": 216, "displayNames": [{"language": "ko", "name": "역추적", "short": "역추적"}, {"language": "en", "name": "traceback", "short": "traceback"}], "aliases": []}], "metadata": {}}
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
    // n <= 300
    // P = all parties seats
    // sum(P) <= 10^5
    // find maximal S subset P such that sum(S) - s in S <= sum(P) / 2
    // this equivalent to finding A subset P and p in P such that sum(P)/2-p < sum(A) <= sum(P)/2, p <= min(A)
    // can track all possible sums using dp
    // traverse from largest to smallest party
    // if adding p would go above sum(P)/2 then consider it for maximal party (can store parent in dp transition graph)
    // dp state: sum of parties -> last added element to reach state (-1 if none, use first aka maximal element to prevent invalidating prior solutions)
    vector<int> parties(n); vcin(parties);
    vector<int> order(n); iota(all(order), 0);
    sort(all(order), [&](int i, int j) {
        return parties[i] > parties[j];
    });
    int total = accumulate(all(parties), 0);
    int half = total >> 1;
    vector<int> dp(half+1,-1);
    dp[0] = 0;
    int bestSeats = half;
    int bestSmallestParty = -1;
    for (int i : order) {
        int x = parties[i];
        int last;
        for (last = half; dp[last] == -1 && last >= half-x+1; --last);
        for (int v = half; v >= x; --v) {
            if (dp[v] != -1 || dp[v-x] == -1) continue;
            
            dp[v] = i;
        }
        int ls = last + x;
        if (ls <= bestSeats) continue;

        bestSeats = ls;
        bestSmallestParty = i;
    }
    int curr = bestSeats - parties[bestSmallestParty];
    vector<int> res(1, bestSmallestParty);
    while (curr > 0) {
        res.push_back(dp[curr]);
        curr -= parties[dp[curr]];
    }
    cout << res.size() << "\n";
    for (int x : res) cout << x+1 << " ";
    cout << "\n";
}
