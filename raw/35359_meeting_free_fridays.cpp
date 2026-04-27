#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define endl "\n"


int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cout << fixed << setprecision(12);

    ll n, t, k; cin >> n >> t >> k;
    vector<pair<ll,ll>> itvs(n);
    for (auto &[a, b] : itvs) {
        cin >> a >> b;
    }
    sort(itvs.begin(), itvs.end());

    // dp[i][j] = k: by ith meeting, j meetings attended, k = max nonmeeting times
    // dp[i][j] -> dp[first meeting not overlapping with ith meeting][j+1]
    // dp[i][j] -> dp[i+1][j] add gap between start of i and i+1
    // dp[0][0] = start of 0
    // sol = max(j where dp[n][j] >= k)
    vector<vector<ll>> dp(n+1, vector<ll>(n+1, LLONG_MIN >> 1));
    dp[0][0] = itvs[0].first;
    for (int i = 0; i < n; ++i) {
        // find next non-overlapping
        int i2 = i+1;
        while (i2 < n && itvs[i2].first < itvs[i].second) ++i2;

        ll skipK = i+1 == n ? t - itvs[i].first : itvs[i+1].first - itvs[i].first;
        ll takeK = i2 == n ? t - itvs[i].second : itvs[i2].first - itvs[i].second;
        // cout << i << " " << i2 << " " << skipK << " " << takeK << endl;
        
        for (int j = 0; j <= n; ++j) {
            dp[i+1][j] = max(dp[i+1][j], dp[i][j] + skipK);
            if (j+1 <= n) dp[i2][j+1] = max(dp[i2][j+1], dp[i][j] + takeK);
        }
    }
    int sol = 0;
    for (int j = 0; j <= n; ++j) {
        if (dp[n][j] >= k) sol = max(sol, j);
    }
    cout << sol << endl;
}
