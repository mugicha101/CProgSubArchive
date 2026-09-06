// 2025-05-17 17:29:18 
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

    int n, tl; cin >> n >> tl;
    vector<int> r(n); // time to read problem
    vector<int> c(n); // time to code problem
    vector<ld> p(n); // chance to solve problem

    for (int i = 0; i < n; ++i) cin >> r[i] >> c[i] >> p[i];
    int mCap = 1 << n;
    vector<vector<ld>> ppick(tl+1, vector<ld>(mCap, 0.L)); // ppick[t][m] = probability that a team can pick a problem at time t given they read the problems in mask m
    vector<vector<ld>> psolv(tl+1, vector<ld>(n, 0.L)); // psolv[t][i] = probability that problem i has been solved by some team by time t
    ppick[0][0] = 1.L;
    for (int t = 0; t < tl; ++t) {
        // accumulate prev psolv
        if (t > 0) for (int i = 0; i < n; ++i) psolv[t][i] += psolv[t-1][i];

        // use all solve masks to update future times
        auto update = [&](int i, int m, ld pprob) {
            assert(((m >> i) & 1) == 0); // problem i should be unread
            // pprob = the probability of problem i being picked given a team is picking a problem at time t with a solve mask m
            int tr = t + r[i];
            int tc = tr + c[i];
            int nm = m | (1 << i);
            ld pstart = ppick[t][m] * pprob; // probability of problem i being picked at time t with a solve mask m
            if (tr <= tl) ppick[tr][nm] += pstart * (1.L - p[i]);
            if (tc <= tl) {
                ppick[tc][nm] += pstart * p[i];
                psolv[tc][i] += pstart * p[i];
            }
        };
        for (int m = 0; m < mCap; ++m) {
            if (ppick[t][m] == 0.L) continue;
            
            ld w = 0.L;
            int unread = 0;
            for (int i = 0; i < n; ++i) {
                if ((m >> i) & 1) continue;

                w += psolv[t][i];
                ++unread;
            }
            w = w == 0.L ? -1.L : 1.L / w;
            for (int i = 0; i < n; ++i) {
                if ((m >> i) & 1) continue;

                update(i, m, w < 0.L ? 1.L / (ld)unread : w * psolv[t][i]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        psolv[tl][i] += psolv[tl-1][i];
        cout << psolv[tl][i] << "\n";
    }
    cout << endl;
}
