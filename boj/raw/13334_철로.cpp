#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned int uint;
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

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

#include <bits/stdc++.h>
using namespace std;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<pair<int,int>> itvs(n);
    vector<pair<int,int>> points;
    points.reserve(n * 2);
    set<int> uniquePoints;
    for (int i = 0; i < (int)itvs.size(); ++i) {
        auto &[s, e] = itvs[i];
        cin >> s >> e;
        points.emplace_back(s, i);
        points.emplace_back(e, i);
        uniquePoints.insert(s);
        uniquePoints.insert(e);
    }
    int d; cin >> d;

    // sliding window on sorted points
    // keep track of how many people have both their points in the window (cover = 2)
    vector<int> cover(n);
    sort(all(points));
    int next = 0;
    int peopleCovered = 0;
    int maxPeopleCovered = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> window;
    for (int x : uniquePoints) {
        // window [x, x+d]
        // remove points from window
        while (!window.empty() && window.top().first < x) {
            peopleCovered -= --cover[window.top().second] == 1;
            window.pop();
        }
        // add points to window
        while (next < (int)points.size() && points[next].first <= x + d) {
            peopleCovered += ++cover[points[next].second] == 2;
            window.push(points[next++]);
        }
        maxPeopleCovered = max(maxPeopleCovered, peopleCovered);
    }
    cout << maxPeopleCovered << "\n";
}
