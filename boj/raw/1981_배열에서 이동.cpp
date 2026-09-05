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
// #define endl "\n"

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            cin >> grid[r][c];
        }
    }
    
    // fix min height, minimize max height (dijkstras in O(n^2lgn))
    // O(kn^2lgn)
    int startH = grid[0][0];
    int endH = grid[n-1][n-1];
    int maxMinH = min(startH, endH);
    vector<vector<int>> minMaxH(n, vector<int>(n));
    int best = 1000;
    for (int minH = 0; minH <= maxMinH; ++minH) {
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
        for (auto &row : minMaxH) {
            fill(all(row), 1000);
        }
        auto check = [&](int h, int r, int c) {
            h = max(h, grid[r][c]);
            if (grid[r][c] < minH || minMaxH[r][c] <= h) return;

            minMaxH[r][c] = h;
            pq.emplace(h, r, c);
        };
        check(0, 0, 0);

        while (!pq.empty()) {
            auto [h, r, c] = pq.top();
            pq.pop();
            if (r) check(h, r-1, c);
            if (c) check(h, r, c-1);
            if (r+1 < n) check(h, r+1, c);
            if (c+1 < n) check(h, r, c+1);
        }
        best = min(best, minMaxH[n-1][n-1] - minH);
    }
    cout << best << "\n";
}
