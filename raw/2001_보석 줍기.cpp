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

    int n, m, k; cin >> n >> m >> k;
    vector<int> bales(n, -1);
    for (int i = 0; i < k; ++i) {
        int x; cin >> x; --x;
        bales[x] = i;
    }
    vector<vector<pair<int,int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int a, b, w; cin >> a >> b >> w; --a; --b;
        adj[a].emplace_back(b, w);
        adj[b].emplace_back(a, w);
    }

    // construct multi-layer graph - bales used to travel between layers
    // 2^14 = ~16k layers (1 for each bale mask)
    // total size: 2^14 * 100
    vector<vector<bool>> visited(1 << k, vector<bool>(n, false));
    queue<tuple<int,int,int>> q; // mask, pos, fatness
    auto check = [&](int mask, int pos, int fat) {
        if (visited[mask][pos]) return;

        visited[mask][pos] = true;
        q.emplace(mask, pos, fat);
    };
    check(0, 0, 0);
    int maxFatness = 0;
    while (!q.empty()) {
        auto [mask, pos, fat] = q.front();
        q.pop();

        if (pos == 0) maxFatness = max(maxFatness, fat);

        // take bale
        if (bales[pos] != -1 && ((mask >> bales[pos]) & 1) == 0) check(mask | (1 << bales[pos]), pos, fat + 1);

        // travel to adjacent position
        for (auto &[next, width] : adj[pos]) {
            if (width < fat) continue;

            check(mask, next, fat);
        }
    }
    cout << maxFatness << "\n";
}
