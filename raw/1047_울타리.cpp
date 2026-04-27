#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

#define MOD 1000000007

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
pair<T,U> operator-(const pair<T,U> & l,const pair<T,U> & r) {   
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
#define pause() this_thread::sleep_for(10ms)

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);
    
    int n; cin >> n; // n <= 40
    vector<tuple<int,int,int>> pts(n);
    int sum = 0;
    for (auto &[x, y, c] : pts) {
        cin >> x >> y >> c;
        sum += c;
    }
    sort(pts.begin(), pts.end(), [&](auto &a, auto &b) {
        return get<2>(a) < get<2>(b);
    });

    // maximize trees in rectangle while sum of tree values outside rectangle >= rectangle perimeter
    // if tree values outside rect < rect perimeter, cut down largest trees within perimeter until >=
    // brute force: try all tuples of (x1, y1, x2, y2): n^4 <= 3 * 10^6 such tuples
    // for each tuple, O(N) to evaluate
    // total: n^5 <= 102,400,000 ~= 10^8

    vector<int> ux(n);
    vector<int> uy(n);
    for (int i = 0; i < n; ++i) {
        ux[i] = get<0>(pts[i]);
        uy[i] = get<1>(pts[i]);
    }
    sort(ux.begin(), ux.end());
    ux.resize(distance(ux.begin(), unique(ux.begin(), ux.end())));
    sort(uy.begin(), uy.end());
    uy.resize(distance(uy.begin(), unique(uy.begin(), uy.end())));
    int best = INT_MAX;
    int w[40] = {};
    for (int iax = 0; iax < (int)ux.size(); ++iax) {
        int ax = ux[iax];
        for (int iay = 0; iay < (int)uy.size(); ++iay) {
            int ay = uy[iay];
            for (int ibx = iax; ibx < (int)ux.size(); ++ibx) {
                int bx = ux[ibx];
                for (int iby = iay; iby < (int)uy.size(); ++iby) {
                    int by = uy[iby];
                    int p = ((bx - ax) + (by - ay)) * 2;
                    if (sum < p) continue;

                    int q = 0;
                    int cut = 0;
                    int wc = 0;
                    for (auto &[px, py, pc] : pts) {
                        if (px >= ax && px <= bx && py >= ay && py <= by) {
                            w[wc++] = pc;
                        } else {
                            q += pc;
                            ++cut;
                        }
                    }
                    while (q < p) {
                        q += w[--wc];
                        ++cut;
                    }
                    best = min(best, cut);
                }
            }
        }
    }
    cout << best << endl;
}
