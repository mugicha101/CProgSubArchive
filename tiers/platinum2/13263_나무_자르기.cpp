/*
Platinum 2
13263 - 나무 자르기
meta: {"problemId": 13263, "titleKo": "나무 자르기", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "나무 자르기", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 1293, "level": 19, "votedUserCount": 172, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.4547998905181885, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "cht", "isMeta": false, "bojTagId": 89, "problemCount": 128, "displayNames": [{"language": "ko", "name": "볼록 껍질을 이용한 최적화", "short": "볼록 껍질을 이용한 최적화"}, {"language": "en", "name": "convex hull trick", "short": "cht"}, {"language": "ja", "name": "convex hull trick", "short": "cht"}], "aliases": [{"alias": "컨벡스헐트릭"}, {"alias": "컨벡스헐최적화"}]}], "metadata": {}}
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

    // a_i = height of tree i (a_1 = 1)
    // a_i is strict mono increasing
    // since cannot charge without downed tree, always start with 0 charge and first tree cut
    // b_i = cost to cut a piece given max cut tree is i
    // b_i is strict mono decreasing
    // always optimal to cut down a tree all at once
    // given max cut tree is j, cost to cut tree i is b_j * a_i
    // since b_i mono decreasing, but a_i mono increasing, need to choose next tree to cut such that cost to cut pays off by making future trees easier to cut
    // since in the end the nth tree will be cut, cost to cut all trees in between is the sum heights of them * b_{n-1}
    // dp[i] = max cost to cut up to ith tree
    // dp[0] = 0
    // let aps[i] = sum of first i elements in a
    // dp[i>0] = min(dp[k] + a[i] * b[k] + (aps[i] - aps[k+1]) * b[n-1], 0 <= k < i)
    //         = aps[i] * b[n-1] + min(dp[k] + a[i] * b[k] - aps[k+1] * b[n-1])
    // convex hull trick (min)
    // L(k,i) = m(k) * x(i) + b(k)
    // f(i) = aps[i] * b[n-1]
    // m(k) = b[k]
    // x(i) = a[i]
    // b(k) = dp[k] - aps[k+1] * b[n-1]
    // dp[i] = f(i) + min(L(k,i))
    // max to min - flip m(x) and b(k)
    int n; cin >> n;
    vector<ll> a(n); for (auto &x : a) cin >> x;
    vector<ll> aps(n+1);
    for (int i = 0; i < n; ++i) aps[i+1] = aps[i] + a[i];
    vector<ll> b(n); for (auto &x : b) cin >> x;
    vector<ll> dp(n+1);
    auto F = [&](int i) { return aps[i] * b[n-1]; };
    auto M = [&](int k) { return -b[k]; };
    auto X = [&](int i) { return a[i]; };
    auto B = [&](int k) { return -(dp[k] - aps[k+1] * b[n-1]); };
    auto L = [&](int k, int i) { return M(k) * X(i) + B(k); };
    // get intersection of lines i and j in fraction form
    auto lineInt = [&](int i, int j) -> pair<ll,ll> {
        pair<ll,ll> ret = make_pair(B(j) - B(i), M(i) - M(j));
        if (ret.second < 0) {
            ret.first = -ret.first;
            ret.second = -ret.second;
        }
        ll d = gcd(abs(ret.first), abs(ret.second));
        ret.first /= d;
        ret.second /= d;
        return ret;
    };
    auto fracGeq = [](pair<ll,ll> a, pair<ll,ll> b) {
        return (__int128_t)a.first * (__int128_t)b.second >= (__int128_t)b.first * (__int128_t)a.second;
    };
    deque<int> cht;
    cht.push_back(0);
    for (int i = 1; i < n; ++i) {
        while (cht.size() > 1 && L(cht[1],i) >= L(cht[0],i)) cht.pop_front();
        dp[i] = F(i) - L(cht[0],i);

        // given last 2 lines L_a, L_b and new line L_i
        // if L_b < L_a and L_i then pop L_b
        // repeat until false
        while (cht.size() >= 2 && fracGeq(lineInt(cht[cht.size()-2], cht.back()), lineInt(cht[cht.size()-2], i)))
            cht.pop_back();
        cht.push_back(i);
    }
    cout << dp[n-1] << endl;
}
