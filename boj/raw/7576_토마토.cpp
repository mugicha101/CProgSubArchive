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
    cin >> cols >> rows;
    int remaining = 0;
    vector<vector<int8_t>> grid(rows, vector<int8_t>(cols, 0));
    queue<pair<int,int>> q;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int x; cin >> x;
            grid[r][c] = (int8_t)x;
            if (x == 1) q.emplace(r, c);
            remaining += x != -1;
        }
    }
    int days = -1;
    while (!q.empty()) {
        ++days;
        for (int qi = (int)q.size(); qi > 0; --qi) {
            auto [r, c] = q.front();
            q.pop();
            --remaining;
            auto check = [&](int r, int c) {
                if (grid[r][c] != 0) return;

                grid[r][c] = 1;
                q.emplace(r, c);
            };
            if (r) check(r-1, c);
            if (c) check(r, c-1);
            if (r+1 < rows) check(r+1, c);
            if (c+1 < cols) check(r, c+1);
        }
    }
    cout << (remaining ? -1 : max(days, 0)) << endl;
}
