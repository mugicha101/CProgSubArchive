// 2025-05-27 04:02:50 
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

    ll n, m, w, h; cin >> n >> m >> w >> h;
    vector<pair<ll,ll>> c(n);
    vector<pair<ll,ll>> f(m);
    for (auto &[x, y] : c) {
        cin >> x >> y;
    }
    for (auto &[x, y] : f) {
        cin >> x >> y;
        y = -y;
    }

    auto sub = [&](vector<pair<ll,ll>> ceil) -> vector<ll> {
        vector<ll> safe(w+1, h);
        for (ll i = 0; i+1 < (ll)ceil.size(); ++i) {
            ll x0 = ceil[i].first;
            ll y0 = ceil[i].second;
            ll x1 = ceil[i+1].first;
            ll y1 = ceil[i+1].second;
            if (x0 == x1) {
                safe[x0] = min({safe[x0], y0 - 1, y1 - 1});
                continue;
            }

            ll dx = x1 - x0;
            ll dy = y1 - y0;
            for (ll x = x0; x <= x1; ++x) {
                // safe[x] = ceil(y0 + dy/dx * (x - x0)) - 1
                ll num = (x - x0) * dy;
                safe[x] = min(safe[x], y0 + num / dx - (num % dx == 0));
            }
        }
        return safe;
    };
    vector<ll> csafe = sub(c);
    vector<ll> fsafe = sub(f);
    ll lo = 0;
    ll hi = 0;
    for (ll x = 0; x <= w; ++x) {
        ll cy = csafe[x];
        ll fy = -fsafe[x];

        lo = max(lo - 1, fy);
        hi = min(hi + 1, cy);

        // ensure valid parity
        lo += (lo + x) & 1;
        hi -= (hi + x) & 1;

        if (lo > hi) {
            cout << "impossible" << endl;
            return 0;
        }
    }
    cout << lo << " " << hi << endl;
}
