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

    const int N = 2048;
    vector<vector<bool>> board(N * 2, vector<bool>(N * 2));
    
    queue<pair<int,int>> q;
    int cows = 0;
    auto check = [&](int x, int y) {
        if (!board[x][y]) return;

        int nbs = (int)board[x - 1][y] + (int)board[x + 1][y] + (int)board[x][y - 1] + (int)board[x][y + 1];
        if (nbs != 3) return;

        q.emplace(x - 1, y);
        q.emplace(x + 1, y);
        q.emplace(x, y - 1);
        q.emplace(x, y + 1);
    };

    vector<pair<int,int>> input(n);
    for (auto &[x, y] : input) {
        cin >> x >> y; x += N; y += N;
    }
    for (int i = 0; i < n; ++i) {
        q.push(input[i]);
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            if (board[x][y]) continue;

            board[x][y] = true;
            ++cows;
            check(x, y);
            check(x-1, y);
            check(x+1, y);
            check(x, y-1);
            check(x, y+1);
        }
        int added = cows - (i + 1);
        cout << added << "\n";
    }
}
