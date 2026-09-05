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
    
    // only need to find the max between days cause that maintains optimal into next day
    // for a given day, can knapsack on the stocks
    // dp[i][j] = max tomorrow gain from stock i onwards with j money remaining today
    // O(M * s * d) = 5 * 10^5 * 50 * 10 = 2500 * 10^5 < 3 * 10^8
    // dp[i][j] = max(dp[i+1][j], dp[i][j-cost[i]] + gain[i])
    // can compress to 1D: dp[j] = max(dp[j], dp[j-cost[i]] + gain[i])

    int s, d, m; cin >> s >> d >> m;
    const int M = 500001;
    vector<vector<int>> price(s, vector<int>(d)); // p[i][j] = price of stock i on day j
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < d; ++j) {
            cin >> price[i][j];
        }
    }
    for (int day = 1; day < d; ++day) {
        // 0/n knapsack
        vector<int> dp(M);
        for (int i = 0; i < s; ++i) {
            int cost = price[i][day-1];
            int gain = price[i][day] - cost;
            if (gain <= 0) continue;

            for (int j = cost; j < M; ++j) {
                dp[j] = max(dp[j], dp[j-cost] + gain);
            }
        }
        int nm = 0;
        for (int j = 0; j <= m; ++j) {
            nm = max(nm, dp[j] + j);
        }
        m = nm;
    }
    cout << m << endl;
}
