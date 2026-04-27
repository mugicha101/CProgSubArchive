#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    string s;
    cin >> s;
    int counts[3] = {0,0,0};
    int maxSeq = 0;
    for (char x : s) {
        ++counts[x-'A'];
        int minV = min(min(counts[0], counts[1]), counts[2]);
        for (int i = 0; i < 3; ++i) counts[i] -= minV;
        int maxV = max(max(counts[0], counts[1]), counts[2]);
        maxSeq = max(maxSeq, maxV);
    }
    cout << maxSeq << "\n";
}
