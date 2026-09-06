// 2024-11-12 19:05:18 
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

#include <bits/extc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX >> 2;

int dfs(vector<int> &teams, int i, int m) {
    if (i == (int)teams.size()) return 0;

    int res = 0;
    
    // pick if no overlap with already chosen
    if ((teams[i] & m) == 0) {
        res = dfs(teams, i+1, m | teams[i]) + 1;
    }

    // skip
    res = max(res, dfs(teams, i+1, m));

    return res;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, x, y, days;
    cin >> n >> x >> y >> days;
    --x; --y;

    // p[d][x][y] = movements such that neither bear interacts by the ith day and the bears are at x and y respectively
    // total movements by day d is is 4^d <= 4^31 = 2^62 which fits in long long
    // p[d][x][x] = 0 (can ignore even if actual value is diff)
    vector<vector<vector<ll>>> p(days + 1, vector<vector<ll>>(n, vector<ll>(n)));
    auto left = [&](int x) {
        return x - (x > 0);
    };
    auto right = [&](int x) {
        return x + (x + 1 < n);
    };
    p[0][x][y] = 1;
    for (int d = 0; d < days; ++d) {
        auto &curr = p[d];
        auto &next = p[d+1];
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                if (x == y) continue;

                ll v = curr[x][y];
                next[left(x)][left(y)] += v;
                next[left(x)][right(y)] += v;
                next[right(x)][left(y)] += v;
                next[right(x)][right(y)] += v;
            }
        }
    }

    // find ans
    ll total = 1LL << (days * 2);
    ll ways = total;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            if (x == y) continue;

            ways -= p[days][x][y];
        }
    }
    if (ways == 0) {
        cout << "0/1" << endl;
        return 0;
    }
    ll d = gcd(ways, total);
    ways /= d;
    total /= d;
    cout << ways << "/" << total << endl;
}
