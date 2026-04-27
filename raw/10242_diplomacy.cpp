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
    while (true) {
        // want to flip friends of opposite parties (frenemies)
        // greedy: pick node that would reduce components by most
        int n, m; cin >> n >> m;
        if (n == 0 && m == 0) break;

        vector<int> colors(n); for (auto &x : colors) {
            cin >> x; ++x;
        }
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; ++i) {
            int a, b; cin >> a >> b; --a; --b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        auto numComps = [&adj, n](vector<int> &colors) {
            queue<int> q;
            int comps = 0;
            for (int root = 0; root < n; ++root) {
                if (colors[root] < 0) continue;

                ++comps;
                int c = colors[root];
                colors[root] = -c;
                q.emplace(root);
                while (!q.empty()) {
                    int curr = q.front();
                    q.pop();
                    for (int next : adj[curr]) {
                        if (colors[next] != c) continue;
    
                        colors[next] = -c;
                        q.push(next);
                    }
                }
            }

            for (int &c : colors) c = -c;
            return comps;
        };

        auto flip = [&adj, n](vector<int> &colors, int target) {
            queue<int> q;
            int c = colors[target];
            colors[target] = 3 - c;
            q.push(target);
            while (!q.empty()) {
                int curr = q.front();
                q.pop();
                for (int next : adj[curr]) {
                    if (colors[next] != c) continue;

                    colors[next] = 3 - c;
                    q.push(next);
                }
            }
        };
        
        // theory: optimal solution can be done by flipping same tile repeatedly
        int best = INT_MAX;
        for (int i = 0; i < n; ++i) {
            int days = 0;
            vector<int> t = colors;
            while (numComps(t) > 1) {
                ++days;
                flip(t, i);
            }
            best = min(best, days);
        }
        cout << best << "\n";
    }
}

/*
1(0) - 2(1) - 4(0)
        |
       3(0)



*/