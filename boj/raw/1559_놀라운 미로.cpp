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

#define DIJ 1

int dfs(vector<vector<vector<int>>> &keyDist, vector<int> &seq, int i, int used) {
    if (i == (int)seq.size()-1) {
        int t = 0;
        for (int j = 1; j < (int)seq.size(); ++j)
            t += keyDist[seq[j-1]][seq[j]][t & 0b11];
        return t;
    }
    int best = INT_MAX;
    for (int j = 0; j < (int)keyDist.size() - 1; ++j) {
        if ((used >> j) & 1) continue;

        seq[i] = j;
        best = min(best, dfs(keyDist, seq, i + 1, used | (1 << j)));
    }
    return best;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int rows, cols;
    while (cin >> rows >> cols, rows) {
        // init direction (E = 0, S = 1, W = 2, N = 3)
        vector<vector<int>> initDir(rows, vector<int>(cols));
        auto getDir = [&](int r, int c, int t) {
            return (initDir[r][c] + (t & 0b11)) & 0b11;
        };
        // time to travel from (r, c) to desired direction (waits for door to open)
        auto getTravelTime = [&](int r, int c, int t, int dir) {
            return ((dir + 4 - getDir(r, c, t)) & 0b11) + 1;
        };
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                char v; cin >> v;
                initDir[r][c] = v == 'E' ? 0 : v == 'S' ? 1 : v == 'W' ? 2 : 3;
            }
        }
        int k; cin >> k;
        vector<pair<int,int>> keys(k);
        for (auto &[r, c] : keys) {
            cin >> r >> c; --r; --c;
        }
        keys.emplace_back(0, 0); // treat src as a key
        swap(keys[0], keys[k]);
        keys.emplace_back(rows-1, cols-1); // treat dest as a key
        k += 2;

        // compute dist between each key with each starting phase
        // dist[i][j][p] = time to get from key i to key j with starting phase p
        // O(kn^2m^2)
        vector<vector<vector<int>>> keyDist(k, vector<vector<int>>(k, vector<int>(4)));
        vector<vector<int>> dist(rows, vector<int>(cols));
        int id = 0;
        for (int i = 0; i < k; ++i) {
            for (int p = 0; p < 4; ++p) {
                #if DIJ
                for (auto &row : dist) fill(all(row), INT_MAX);
                #else
                for (auto &row : dist) fill(all(row), -1);
                #endif
                ++id;
                #if DIJ
                priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
                auto push = [&](int r, int c, int t) {
                    if (dist[r][c] <= t) return;

                    dist[r][c] = t;
                    pq.emplace(t, r, c);
                };
                push(keys[i].first, keys[i].second, 0);
                while (!pq.empty()) {
                    auto [t, r, c] = pq.top();
                    pq.pop();
                    if (t > dist[r][c]) continue;

                    auto check = [&](int nr, int nc, int dir) {
                        push(nr, nc, t + getTravelTime(r, c, t + p, dir));
                    };
                    if (c+1 < cols) check(r, c+1, 0);
                    if (r+1 < rows) check(r+1, c, 1);
                    if (c) check(r, c-1, 2);
                    if (r) check(r-1, c, 3);
                }
                #else
                vector<pair<int,int>> q;
                int t = 0;
                auto check = [&](int r, int c) {
                    if (dist[r][c] != -1) return;

                    dist[r][c] = t;
                    q.emplace_back(r, c);
                };
                check(keys[i].first, keys[i].second);
                auto allVisited = [&]() {
                    for (int j = 0; j < k; ++j) if (dist[keys[j].first][keys[j].second] == -1) return false;
                    return true;
                };
                while (!allVisited()) {
                    ++t;
                    size_t cap = q.size();
                    for (size_t i = 0; i < cap; ++i) {
                        auto [r, c] = q[i];
                        switch (getDir(r, c, t+p-1)) {
                            case 0: if (c+1 < cols) check(r, c+1); break;
                            case 1: if (r+1 < rows) check(r+1, c); break;
                            case 2: if (c) check(r, c-1); break;
                            case 3: if (r) check(r-1, c); break;
                        }
                    }
                }
                #endif
                for (int j = 0; j < k; ++j) {
                    keyDist[i][j][p] = dist[keys[j].first][keys[j].second];
                }
            }
        }
        /*
        for (auto &a : keyDist) {
            for (auto &b : a) {
                cout << "[" << b[0] << "," << b[1] << "," << b[2] << "," << b[3] << "] ";
            }
            cout << endl;
        }
        */

        // try all sequences to pick up keys
        vector<int> seq(k);
        seq.back() = keyDist.size() - 1;
        int best = dfs(keyDist, seq, 1, 1);
        cout << best << "\n";
    }
}
