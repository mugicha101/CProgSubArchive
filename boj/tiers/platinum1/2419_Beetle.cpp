/*
Platinum 1
2419 - Beetle
meta: {"problemId": 2419, "titleKo": "사수아탕", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "사수아탕", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Beetle", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 846, "level": 20, "votedUserCount": 87, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 3.0213000774383545, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}], "metadata": {}}
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

    int n, m; cin >> n >> m;
    vector<int> pos(n); vcin(pos);
    int ze = find(pos.begin(), pos.end(), 0) != pos.end();
    if (!ze) {
        ++n;
        pos.push_back(0);
    }
    sort(all(pos));

    // n <= 300
    // m <= 10^6
    // given n dewdrops at positions (abs val <= 10^5) with m water each
    // dewdrop positions sorted in input step
    // water evaporates at 1 unit per second
    // beetle starts at 0 and moves 1 unit per second and drinks water instantaneously
    // find max water beetle can drink
    // naive expanding interval dp: dp[t][l][r] = w: w is max water beetle can drink by time t given drank l through r dewdrops
    // max states: O(n^2m) <= 9 * 10^12 with O(1) transitions (too many)
    // pareto front: if dp[t][l][r] > dp[t'>t][l][r] then dp[t][l][r] dominates dp[t'][l][r], only want to store dp[t][l][r] < dp[t'>t][l][r]
    // - want to maximize water for benefit of current state while minimizing time for benefit of future states
    // - sample case shows optimizing just time or water is insufficient
    // each dp[l][r] -> (t, w) where t and w both strict mono increase
    // max states still O(n^2m) but should be sparse
    // when considering adding (t, w) to dp[l][r] need to remove all dominated (t', w')
    // algo:
    // - let (t', w') be the backmost in dp[l][r]
    // - while dp[l][r] not empty and t' >= t and w' < w pop dp[l][r]
    // - push (t, w) if w > w'
    // amortized O(1) per transition since each can only be pushed and popped once
    // when considering dp[l][r] for transitioning, consider all in the pareto front
    // pray it runs in time (it won't)
    // max water <= m * n <= 3 * 10^8 < 2^29 so int32 fine

    using val_t = pair<int,int>; // (min time, max water) pareto value
    using pareto_t = vector<val_t>;
    using dplr_t = array<pareto_t,2>;
    using dpl_t = vector<dplr_t>;
    using dp_t = vector<dpl_t>;
    dp_t dp(n, dpl_t(n));

    auto add = [&](pareto_t &p, val_t v) {
        while (!p.empty() && p.back().first >= v.first && p.back().second < v.second) p.pop_back();
        if (p.empty() || p.back().second < v.second) p.push_back(v);
    };
    
    // first find dewdrops adjacent to 0 and start there
    // can reduce it by treating 0 as a dewdrop with 0 water (or m if dewdrop at 0)
    int zi = (int)distance(pos.begin(), find(pos.begin(), pos.end(), 0));
    add(dp[zi][zi][0], mp(0, ze ? m : 0));
    add(dp[zi][zi][1], mp(0, ze ? m : 0));

    // next do expanding intervals
    for (int di = 0; di < n; ++di) {
        for (int l = 0; l+di < n; ++l) {
            int r = l + di;

            // first transition between l and r
            int d = pos[r] - pos[l];
            for (auto [t, w] : dp[l][r][0]) {
                add(dp[l][r][1], mp(t+d, w));
            }
            for (auto [t, w] : dp[l][r][1]) {
                add(dp[l][r][0], mp(t+d, w));
            }

            // next expand interval to l-1 and r+1
            if (l > 0) {
                d = pos[l] - pos[l-1];
                for (auto [t, w] : dp[l][r][0]) {
                    t += d;
                    add(dp[l-1][r][0], mp(t, w+max(0,m-t)));
                }
            }
            if (r+1 < n) {
                d = pos[r+1] - pos[r];
                for (auto [t, w] : dp[l][r][1]) {
                    t += d;
                    add(dp[l][r+1][1], mp(t, w+max(0,m-t)));
                }
            }
        }
    }

    // solution is max(dp[0][n-1][b][end].w)
    int res = max(dp[0][n-1][0].back().second, dp[0][n-1][1].back().second);
    cout << res << endl;
    // cout << dp[1][1][0] << " | " << dp[1][1][1] << endl;
    // cout << dp[0][n-1][0] << " | " << dp[0][n-1][1] << endl;
}
