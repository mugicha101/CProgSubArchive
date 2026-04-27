#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

vector<vector<int>> adj;
vector<char> seq;
vector<char> pstack;

int dfs(int p, int i) {
    int sum = 0;
    auto next = [&]() {
        for (int j : adj[i]) {
            if (j == p) continue;
            sum += dfs(i, j);
        }
    };
    if (seq[i] & 0b100) {
        if (pstack.empty() || pstack.back() != seq[i])
            return 0;
        char t = pstack.back();
        pstack.pop_back();
        sum += pstack.empty();
        next();
        pstack.push_back(t);
    } else {
        pstack.push_back(seq[i] | 0b100);
        next();
        pstack.pop_back();
    }
    return sum;
}

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    int n;
    cin >> n;
    string str;
    cin >> str;
    seq.resize(n);
    for (int i = 0; i < n; ++i) {
        switch (str[i]) {
            case '(': seq[i] = 0b001; break;
            case '[': seq[i] = 0b010; break;
            case '{': seq[i] = 0b011; break;
            case ')': seq[i] = 0b101; break;
            case ']': seq[i] = 0b110; break;
            case '}': seq[i] = 0b111; break;
        }
    }
    adj.resize(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
        count += dfs(-1, i);
    }
    cout << count << endl;
}

