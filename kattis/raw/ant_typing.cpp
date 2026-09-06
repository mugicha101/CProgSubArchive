// 2024-02-28 13:16:01 
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

int counts[9][9];
int pos[9];
char firstKey;
int bestTime = INT_MAX;

void dfs(char p, int time) {;
    for (char a = 0; a < 9; ++a) {
        if (pos[a] != -1) continue;
        pos[a] = p;
        int nt = time;
        if (a == firstKey) nt += p;
        for (char b = 0; b < 9; ++b)
            nt += pos[b] == -1 ? 0 : (counts[a][b] + counts[b][a]) * (p-pos[b]);
        if (nt < bestTime) {
            if (p == 8) bestTime = min(bestTime, nt);
            else dfs(p+1, nt);
        }
        pos[a] = -1;
    }
}

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    // input
    string seq;
    cin >> seq;
    memset(counts, 0, sizeof(counts));
    memset(pos, -1, sizeof(pos));
    for (int i = 1; i < seq.size(); ++i)
        ++counts[seq[i-1]-'1'][seq[i]-'1'];
    firstKey = seq[0]-'1';
    dfs(0, 0);
    int time = bestTime + seq.size();
    cout << time << endl;
}

