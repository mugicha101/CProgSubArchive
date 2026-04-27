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
#define endl "\n"

#include <bits/stdc++.h>

using namespace std;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    const int k = 3;
    int n; cin >> n;
    vector<pair<int,int>> points(n);
    set<pair<int,int>> t;
    for (auto &[x, y] : points) {
        /*
        do {
            x = (rand() % 20001) - 10000;
            y = (rand() % 20001) - 10000;
        } while (!t.emplace(x, y).second);
        */
       cin >> x >> y;
    }
    /*
    cout << "A" << endl;
    cout.flush();
    */

    // get x and y orderings
    vector<int> xOrder(n);
    iota(all(xOrder), 0);
    vector<int> yOrder = xOrder;
    sort(all(xOrder), [&](int i, int j) { return points[i].first < points[j].first; });
    sort(all(yOrder), [&](int i, int j) { return points[i].second < points[j].second; });

    // split each axis into n^{1/k} (forms n^{2/k} regions)
    int s = max((int)ceil(pow((double)n, 1. / (double)k)), 2);
    vector<vector<vector<pair<int,int>>>> regions(s, vector<vector<pair<int,int>>>(s));
    vector<pair<int,int>> region(n);
    int d = (n + s - 1) / s; // tiles per region
    for (int i = 0; i < n; ++i) {
        region[xOrder[i]].first = i / d;
        region[yOrder[i]].second = i / d;
    }
    for (int i = 0; i < n; ++i) {
        regions[region[i].first][region[i].second].push_back(points[i]);
    }

    // compare nearby regions
    int minDist = INT_MAX;
    auto comparePoints = [&](pair<int,int> &p1, pair<int,int> &p2) {
        int dx = p2.first - p1.first;
        int dy = p2.second - p1.second;
        minDist = min(minDist, dx * dx + dy * dy);
    };
    auto checkRegion = [&](int x1, int y1) {
        // compare within self
        vector<pair<int,int>> &r1 = regions[x1][y1];
        for (int i = 0; i < (int)r1.size(); ++i) {
            for (int j = 0; j < (int)r1.size(); ++j) {
                if (i != j) comparePoints(r1[i], r1[j]);
            }
        }

        // compare neighbors
        // only 4 neighbors, others will be checked by the neighbor
        auto checkNeighbor = [&](int x2, int y2) {
            if (x2 < 0 || y2 < 0 || x2 >= s || y2 >= s) return;

            vector<pair<int,int>> r2 = regions[x2][y2];
            for (pair<int,int> &p1 : r1) {
                for (pair<int,int> &p2 : r2) {
                    comparePoints(p1, p2);
                }
            }
        };
        checkNeighbor(x1+1, y1);
        checkNeighbor(x1+1, y1+1);
        checkNeighbor(x1, y1+1);
        checkNeighbor(x1-1, y1+1);
    };
    for (int x = 0; x < s; ++x) {
        for (int y = 0; y < s; ++y) {
            checkRegion(x, y);
        }
    }
    cout << minDist << endl;
}
