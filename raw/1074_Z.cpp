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

#define EPS 1e-7
#define all(x) x.begin(), x.end()

bool dfs(int n, int dr, int dc, int tr, int tc, int &steps) {
    // base case
    if (n == 0) {
        ++steps;
        // cout << "step " << steps << ": " << dr << " " << dc << endl;
        return dr == tr && dc == tc;
    }
    int d = 1 << n;

    // check if region even has tr, tc
    if (tr < dr || dr >= dr + d || tc < dc || tc >= dc + d) {
        // cout << "skip " << dr << " " << dc << " " << d << endl;
        steps += d * d;
        return false;
    }

    // Z shape
    d >>= 1;
    --n;
    return dfs(n, dr, dc, tr, tc, steps) || dfs(n, dr, dc + d, tr, tc, steps) || dfs(n, dr + d, dc, tr, tc, steps) || dfs(n, dr + d, dc + d, tr, tc, steps);
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, tr, tc;
    cin >> n >> tr >> tc;
    int steps = -1;
    dfs(n, 0, 0, tr, tc, steps);
    cout << steps << endl;
}
