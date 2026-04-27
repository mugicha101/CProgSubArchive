#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // reduce to grid equivalent
    // / -> .#
    //      #.
    int n, m;
    cin >> n >> m;
    int rows = n * 2 + 4, cols = m * 2 + 4;
    vector<vector<bool>> grid(rows, vector<bool>(cols));
    for (int r = 2; r < rows-2; r += 2) {
        for (int c = 2; c < cols-2; c += 2) {
            char x; cin >> x;
            switch (x) {
                case '/':
                    grid[r+1][c] = true;
                    grid[r][c+1] = true;
                    break;
                case '\\':
                    grid[r][c] = true;
                    grid[r+1][c+1] = true;
                    break;
            }
        }
    }
    for (int r = 0; r < rows; ++r) {
        grid[r][0] = true;
        grid[r][cols-1] = true;
    }
    for (int c = 0; c < cols; ++c) {
        grid[0][c] = true;
        grid[rows-1][c] = true;
    }

    // find components
    int components = 0;
    queue<pair<int,int>> q;
    for (int r = 1; r < rows-1; ++r) {
        for (int c = 1; c < cols-1; ++c) {
            if (grid[r][c]) continue;

            ++components;
            grid[r][c] = true;
            q.emplace(r, c);
            while (!q.empty()) {
                auto [r,c] = q.front();
                q.pop();
                auto check = [&](int r, int c) {
                    if (grid[r][c]) return;
                    grid[r][c] = true;
                    q.emplace(r, c);
                };
                check(r-1,c);
                check(r,c-1);
                check(r+1,c);
                check(r,c+1);
            }
        }
    }

    // min cost = num components - 1 since MST has # components - 1 edges
    cout << components - 1 << endl;
}
