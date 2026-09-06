// 2025-05-08 17:08:26 
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;

const int MOD = 1000000007;
 
typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
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
// #define endl "\n"

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // variant of multicore scheduling with per-core WCETs for each task
    // n <= 50, k <= 10^5 (k = max WCET)
    // sum time <= 5 * 10^6

    // naive 2D:
    // dp state: tasks processed, intern a time, intern b time -> reachable
    // this blows up to 1.250 * 10^15

    // optimized 1D:
    // dp state: tasks processed, intern a time -> minimal intern b time
    // dp transition: dp[i][a][b] -> dp[i-1][a+t[i][a]][b-t[i][b]]
    // this consists of 2.5 * 10^8 states, each being visited O(1) times

    int n; cin >> n;
    vector<pair<int,int>> tasks(n);
    int asum = 0, bsum = 0;
    for (auto &[a, b] : tasks) {
        cin >> a >> b;
        asum += a;
        bsum += b;
    }
    
    vector<int> dp(asum + 1, bsum + 1);
    dp[0] = bsum;
    for (auto &[ta, tb] : tasks) {
        for (int a = asum; a >= ta; --a) {
            dp[a] = min(dp[a], dp[a - ta] - tb);
        }
    }

    int best = INT_MAX;
    for (int a = 0; a <= asum; ++a) {
        best = min(best, max(a, dp[a]));
    }
    cout << best << endl;
}
