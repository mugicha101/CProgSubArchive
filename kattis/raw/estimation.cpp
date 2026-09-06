// 2024-02-29 22:14:09 
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    // input
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int &x : arr) cin >> x;

    // psum
    vector<int> psum(n+1);
    for (int i = 0; i < n; ++i)
        psum[i+1] = psum[i] + arr[i];
    
    // optimal error for each interval
    // O(n^2log(n))
    static int err[2000][2000]; // err[i][j] = error for range [i,j]
    for (int i = 0; i < n; ++i) {
        int lowerSum = 0, upperSum = 0;
        vector<int> lower(1, INT_MIN), upper(1, INT_MAX);
        auto pushLower = [&](int x) {
            lower.push_back(x);
            push_heap(lower.begin(), lower.end());
            lowerSum += x;
        };
        auto popLower = [&]() {
            pop_heap(lower.begin(), lower.end());
            int x = lower.back();
            lower.pop_back();
            lowerSum -= x;
            return x;
        };
        auto pushUpper = [&](int x) {
            upper.push_back(x);
            push_heap(upper.begin(), upper.end(), greater<int>());
            upperSum += x;
        };
        auto popUpper = [&]() {
            pop_heap(upper.begin(), upper.end(), greater<int>());
            int x = upper.back();
            upper.pop_back();
            upperSum -= x;
            return x;
        };
        for (int j = i; j < n; ++j) {
            if (arr[j] < lower.front()) pushLower(arr[j]);
            else pushUpper(arr[j]);
            if (lower.size()-1 >= upper.size()+1)
                pushUpper(popLower());
            if (lower.size() < upper.size())
                pushLower(popUpper());
            err[i][j] = ((int)lower.size() - (int)upper.size()) * lower.front() + upperSum - lowerSum;
        }
    }

    // dp to find sequences with min err
    // O(n^2k)
    const int INF = INT_MAX >> 1;
    vector<int> dp(n+1, INF); // dp[rem (remaining seqs)][ss (seq start)] = min error to approx rest of array
    dp[n] = 0;
    vector<int> dpOld(n+1);
    for (int rem = 0; rem < k; ++rem) {
        swap(dpOld, dp);
        for (int ss = 0; ss < n; ++ss) {
            dp[ss] = INF;
            for (int se = ss+1; se <= n; ++se)
                dp[ss] = min(dp[ss], err[ss][se-1] + dpOld[se]);
        }
    }
    cout << dp[0] << endl;
}

