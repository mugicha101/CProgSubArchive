// 2026-08-18 19:14:27 
#include <cmath>
#include <limits>
#include <random>
#include <queue>
#include <array>
#include <thread>
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

// using namespace __gnu_pbds;
// template <class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000009
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
using i128 = __int128_t;
using u128 = unsigned __int128_t;

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
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    }
    os << "]";
    return os;
}

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-12
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

inline i128 abs128(i128 x) {
    return x >= 0 ? x : -x;
}

inline pair<i128,i128> fracNorm(pair<i128,i128> f) {
    if (f.second < 0) {
        f.first = -f.first;
        f.second = -f.second;
    }
    return f;
    // i128 d = __gcd(abs128(f.first), abs128(f.second));
    // return {f.first / d, f.second / d};
}

inline bool fracLeq(pair<i128,i128> a, pair<i128,i128> b) {
    return a.first * b.second <= a.second * b.first;
}

inline bool fracLess(pair<i128,i128> a, pair<i128,i128> b) {
    return a.first * b.second < a.second * b.first;
}

inline ld fracLd(pair<i128,i128> x) {
    return (ld)x.first / (ld)x.second;
}

// for each point determine the point for which a line through it evaluated at y=h defines the leftmost point where a guard can see this point
// returns result as fractional value of x (clamped by 0, maxX)
// can do external transformations to reuse for right point
vector<pair<i128,i128>> calcLeftBlockers(const vector<pair<i128,i128>> &pts, int h) {
    int n = pts.size();
    vector<pair<i128,i128>> hull;
    vector<pair<i128,i128>> res;
    res.reserve(n);
    for (const auto &[x,y] : pts) {
        // cout << make_pair((ll)x,(ll)y) << endl;
        while ((int)hull.size() >= 2) {
            pair<i128,i128> &a = hull[hull.size()-2];
            pair<i128,i128> &b = hull[hull.size()-1];
            i128 dx = b.first - a.first;
            i128 dy = b.second - a.second;
            
            // let a, b be last 2 pts on hull (b being last)
            // let dy = b.y - a.y and dx = b.x - a.x
            // ty = dy/dx * (x - b.x) + b.y
            //    = (dy * (x - b.x) + b.y * dx) / dx
            // ty num <= 2 * 10^12
            // ty den <= 10^6
            pair<i128,i128> ty = fracNorm(make_pair(dy * (x - b.first) + b.second * dx, dx));
            // cout << "a=" << make_pair((ll)a.first, (ll)a.second) << " b=" << make_pair((ll)b.first, (ll)b.second) << " ty=" << fracLd(ty) << " [" << (ll)ty.first << "/" << (ll)ty.second << "]" << endl;
            if (fracLeq(ty, make_pair(y,1))) hull.pop_back();
            else break;
        }
        if (hull.size() == 1 && hull.back().second <= y) hull.pop_back();
        
        // cout << "hull: ";
        // for (auto &[hx,hy] : hull) {
        //     cout << make_pair((ll)hx, (ll)hy) << " ";
        // }
        // cout << endl;
        if (hull.empty()) {
            res.emplace_back(0, 1);
        } else {
            // tx = (h - a.y) * (a.x - x) / (a.y - y) + a.x
            //    = ((h - a.y) * (a.x - x) + a.x * (a.y - y)) / (a.y - y)
            pair<i128,i128> &a = hull.back();
            i128 dx = a.first - x;
            i128 dy = a.second - y;
            pair<i128,i128> tx = fracNorm(make_pair(((i128)h - a.second) * dx + a.first * dy, dy));
            res.push_back(tx.first <= 0 ? make_pair((i128)0,(i128)1) : tx);
        }
        hull.emplace_back(x,y);
        // cout << fracLd(res.back()) << endl;
    }
    return res;
}

// draw vector graphic to ensure intervals are accurate
void display(int n, int h, int xs[], int ys[], const vector<pair<i128,i128>> &lb, const vector<pair<i128,i128>> &rb) {
    std::ofstream svg("out.svg");
    int minX = *min_element(xs, xs + n);
    int maxX = *max_element(xs, xs + n);
    int minY = *min_element(ys, ys + n);
    int maxY = h;
    svg << "<svg width=\"100%\" height=\"100%\" viewBox=\"0 0 " << maxX - minX << " " << maxY - minY << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    svg << "<rect width=\"100%\" height=\"100%\" fill=\"#ffffff\"/>";
    svg << "<polygon points=\"";
    for (int i = 0; i < n; ++i) {
        if (i) svg << " ";
        svg << xs[i] - minX << "," << maxY - ys[i] - minY;
    }
    svg << "\" fill=\"#000000\"/>\n";
    for (int i = 0; i < n; ++i) {
        ld lx = fracLd(lb[i]);
        ld rx = fracLd(rb[i]);
        svg << "<polygon points=\"" << xs[i] - minX << "," << maxY - ys[i] - minY << " " << lx - minX << ",0 " << rx - minX << ",0\" fill=\"#ff000010\" stroke=\"#ff0000\" stroke-width=\"0.1%\"/>\n";
    }
    svg << "</svg>\n";
}

int kattis(int n, int h, int xs[], int ys[], int zs[]) {
    // n <= 10^5
    // h, x[i] <= 10^6
    // y[i] < h
    // x[i] < x[i+1]
    // use convex hull monostack trick to figure out which points bound the view from left and right in O(N)
    // from this can calculate interval on road (fractional endpoints to keep integer) for which any guard will see that point
    // greedily find min interval cover by moving as far right without exceeding right endpoint, then adding guard

    int maxX = xs[n-1];
    vector<pair<i128,i128>> pts(n);
    for (int i = 0; i < n; ++i) pts[i] = {xs[i],ys[i]};
    vector<pair<i128,i128>> lb = calcLeftBlockers(pts, h);
    for (int i = 0; i < n; ++i) pts[i] = {maxX-xs[i],ys[i]};
    reverse(all(pts));
    vector<pair<i128,i128>> rb = calcLeftBlockers(pts, h);
    for (int i = 0; i < n; ++i) rb[i].first = (i128)maxX * rb[i].second - rb[i].first;
    reverse(all(rb));
    // for (int i = 0; i < n; ++i) {
    //     cout << "(" << xs[i] << "," << ys[i] << "): " << fracLd(lb[i]) << " - " << fracLd(rb[i]) << endl;
    // }

    // display(n, h, xs, ys, lb, rb);

    vector<int> order(n); iota(all(order), 0);
    sort(all(order), [&](int i, int j) {
        return fracLess(lb[i], lb[j]);
    });

    int guards = 1;
    pair<i128,i128> mr = make_pair((i128)maxX, (i128)1);
    for (int i : order) {
        if (zs[i] == 0) continue;
        
        pair<i128,i128> il = lb[i];
        pair<i128,i128> ir = rb[i];
        if (fracLess(mr, il)) {
            ++guards;
            mr = make_pair((i128)maxX, (i128)1);
        }
        if (fracLess(ir, mr)) mr = ir;
    }

    return guards;
}

// int main() {
//     cin.tie(0)->sync_with_stdio(0);
//     cout << fixed << setprecision(9);

//     int n, h; cin >> n >> h;
//     vector<int> x(n), y(n), z(n);
//     for (int i = 0; i < n; ++i) {
//         cin >> x[i] >> y[i] >> z[i];
//         x[i] *= 10000;
//         y[i] *= 10000;
//     }
//     h *= 10000;
//     cout << kattis(n, h, x.data(), y.data(), z.data()) << endl;
// }
