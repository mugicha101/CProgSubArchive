#include <bits/stdc++.h>
 
using namespace std;
 
/*
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;
*/

int main(int argc, char **argv) {
    // env setup
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    // cout << fixed << setprecision(12);

    int n, c;
    cin >> n >> c;
    int sum = c;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int x = (s[0]-'0') * 60 + (s[2]-'0') * 10 + (s[3]-'0');
        sum += x - c;
    }

    int secs = sum % 60;
    int mins = (sum / 60) % 60;
    int hours = sum / 3600;

    auto num = [&](int v) {
        string s = "00";
        s[0] += v / 10;
        s[1] += v % 10;
        return s;
    };
    cout << num(hours) << ":" << num(mins) << ":" << num(secs) << endl;

    return 0;
}