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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int rows, cols;
    cin >> rows >> cols;
    short psum[51][51] = {};

    for (int r = 0; r < rows; ++r) {
        string s;
        cin >> s;
        for (int c = 0; c < cols; ++c) {
            psum[r+1][c+1] = psum[r][c+1] + psum[r+1][c] - psum[r][c] + (short)(s[c] == ((r + c) & 1 ? 'B' : 'W'));
        }
    }

    short best = 50 * 50;
    for (int sr = 0; sr <= rows - 8; ++sr) {
        for (int sc = 0; sc <= cols - 8; ++sc) {
            short amt = psum[sr + 8][sc + 8] - psum[sr][sc + 8] - psum[sr + 8][sc] + psum[sr][sc];
            best = min(best, min(amt, (short)(64 - amt)));
        }
    }
    cout << best << endl;
}
