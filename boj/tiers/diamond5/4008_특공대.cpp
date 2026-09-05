/*
Diamond 5
4008 - 특공대
meta: {"problemId": 4008, "titleKo": "특공대", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "특공대", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 1279, "level": 21, "votedUserCount": 225, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.004699945449829, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "prefix_sum", "isMeta": false, "bojTagId": 139, "problemCount": 1379, "displayNames": [{"language": "ko", "name": "누적 합", "short": "누적 합"}, {"language": "en", "name": "prefix sum", "short": "prefix sum"}, {"language": "ja", "name": "累積和", "short": "累積和"}], "aliases": [{"alias": "구간합"}, {"alias": "부분합"}, {"alias": "rangesum"}]}, {"key": "cht", "isMeta": false, "bojTagId": 89, "problemCount": 128, "displayNames": [{"language": "ko", "name": "볼록 껍질을 이용한 최적화", "short": "볼록 껍질을 이용한 최적화"}, {"language": "en", "name": "convex hull trick", "short": "cht"}, {"language": "ja", "name": "convex hull trick", "short": "cht"}], "aliases": [{"alias": "컨벡스헐트릭"}, {"alias": "컨벡스헐최적화"}]}], "metadata": {}}
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

    // array A
    // n <= 10^6, -5 <= a <= -1, |b| <= 10^7, |c| <= 3 * 10^7, 1 <= x_i <= 100
    // partition A into segment S such that sum(f(S)) is maximized
    // f(S): let x = sum(S), then f(S) = ax^2 + bx + c (a < 0)
    // notice: f(S) is convex with increasing x
    // use prefix sum to get sum(S) quickly
    // dp[i] = max power for A[0..<i]
    // dp[i] = max(dp[k<i] + f(A[k..<i]))
    // let P[i] = prefix sum of first i elements
    // x = P[i] - P[k]
    // dp[i] = max(dp[k] + a(P[i] - P[k])^2 + b(P[i] - P[k]) + c)
    //       = max(dp[k] + a(P[i]^2 - 2P[k]P[i] + P[k]^2) + b(P[i] - P[k]) + c)
    //       = max(dp[k] + aP[i]^2 - 2aP[k]P[i] + aP[k]^2 + bP[i] - bP[k] + c)
    //       = max(-2aP[k]P[i] + aP[k]^2 - bP[k] + dp[k]) + aP[i]^2 + bP[i] + c
    // linear form: dp[i] = f(x) + max(Mx + B)
    //     x = P[i]
    //     f(x) = ax^2 + bx + c
    //     M = -2aP[k]
    //     B = aP[k]^2 - bP[k] + dp[k]
    // convex lines formed by -2aP[k]P[i] + aP[k]^2 - bP[k] + dp[k] change which ones highest monotonically
    // let L(k,i) = -2aP[k]P[i] + aP[k]^2 - bP[k] + dp[k]
    // dp[i] = aP[i]^2 + bP[i] + c + max(L(k,i))
    // CHT: increment current k when L(k+1,i) > L(k,i) to track max k in O(n)

    int n; cin >> n;
    ll a, b, c; cin >> a >> b >> c;
    vector<ll> arr(n); for (auto &x : arr) cin >> x;
    vector<ll> P(n+1); for (int i = 0; i < n; ++i) P[i+1] = P[i] + arr[i];
    vector<ll> dp(n+1);
    vector<ll> t(n+1);
    auto M = [&](int k) { return -2 * a * P[k]; };
    auto B = [&](int k) { return a * P[k] * P[k] - b * P[k] + dp[k]; };
    auto L = [&](int k, int i) { return M(k) * P[i] + B(k); };
    auto lineInt = [&](int i, int j) -> pair<ll,ll> {
        // M[i] x + B[i] = M[j] x + B[j]
        // (M[i] - M[j]) x = B[j] - B[i]
        // x = (B[j] - B[i]) / (M[i] - M[j])
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
        // a.first / a.second >= b.first / b.second
        // a.first * b.second >= b.first * a.second
        return a.first * b.second >= b.first * a.second;
    };
    deque<int> cht;
    cht.push_back(0);
    for (int i = 1; i <= n; ++i) {
        while (cht.size() > 1 && L(cht[1],i) >= L(cht[0],i)) cht.pop_front();
        dp[i] = ((a * P[i]) + b) * P[i] + c + L(cht[0],i);

        // given last 2 lines L_a, L_b and new line L_i
        // if L_b < L_a and L_i then pop L_b
        // repeat until false
        while (cht.size() >= 2 && fracGeq(lineInt(cht[cht.size()-2], cht.back()), lineInt(cht[cht.size()-2], i)))
            cht.pop_back();
        cht.push_back(i);
    }
    cout << dp[n] << endl;
}
