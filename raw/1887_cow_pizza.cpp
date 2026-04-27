#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;

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

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX >> 2;

#define all(x) x.begin(), x.end()

int dfs(vector<vector<int>> &constraints, vector<bool> &picked, int curr) {
    if (curr == (int)picked.size()) return 1;

    // skip
    int sum = dfs(constraints, picked, curr+1);

    // pick
    picked[curr] = true;
    bool bad = false;
    for (vector<int> &c : constraints) {
        bad = true;
        for (int j = 0; bad && j < (int)c.size(); ++j) {
            bad = picked[c[j]];
        }
        if (bad) break;
    }
    if (!bad) sum += dfs(constraints, picked, curr+1);
    picked[curr] = false;
    return sum;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, k;
    cin >> n >> k;
    vector<vector<int>> constraints(k);
    for (vector<int> &c : constraints) {
        int l;
        cin >> l;
        c.resize(l);
        for (int &x : c) {
            cin >> x;
            --x;
        }
    }

    // brute force counting with pruning
    // each addition, check constraints
    // time: k2^n <= 52 * 2^20 < 10^7
    vector<bool> picked(n);
    cout << dfs(constraints, picked, 0) << endl;
}
