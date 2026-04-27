/*
Platinum 5
1708 - 볼록 껍질
meta: {"problemId": 1708, "titleKo": "볼록 껍질", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "볼록 껍질", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 5441, "level": 16, "votedUserCount": 388, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.5448999404907227, "official": true, "tags": [{"key": "geometry", "isMeta": false, "bojTagId": 100, "problemCount": 2046, "displayNames": [{"language": "ko", "name": "기하학", "short": "기하학"}, {"language": "en", "name": "geometry", "short": "geom"}, {"language": "ja", "name": "幾何学", "short": "幾何"}], "aliases": []}, {"key": "convex_hull", "isMeta": false, "bojTagId": 20, "problemCount": 245, "displayNames": [{"language": "ko", "name": "볼록 껍질", "short": "볼록 껍질"}, {"language": "en", "name": "convex hull", "short": "convex hull"}, {"language": "ja", "name": "凸包", "short": "凸包"}], "aliases": [{"alias": "컨벡스헐"}]}, {"key": "angle_sorting", "isMeta": false, "bojTagId": 240, "problemCount": 60, "displayNames": [{"language": "ko", "name": "각도 정렬", "short": "각도 정렬"}, {"language": "en", "name": "angle sorting", "short": "angle sorting"}], "aliases": []}], "metadata": {}}
*/

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
#define endl "\n"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<pair<int,int>> convexHull(vector<pair<int,int>> points, bool colinear = false) {
    // remove duplicates
    sort(points.begin(), points.end());
    points.resize(distance(points.begin(), unique(points.begin(), points.end())));
    if (points.size() <= 2) return points;

    auto distSqd = [](pair<int,int> p1, pair<int,int> p2) {
        ll dx = p2.first - p1.first;
        ll dy = p2.second - p1.second;
        return dx * dx + dy * dy;
    };

    // determines whether p2 -> p3 is right-turn (+) or left-turn (-) away from p1 -> p2
    auto orientation = [](pair<int,int> p1, pair<int,int> p2, pair<int,int> p3) {
        ll v = p1.first * (p2.second - p3.second) + p2.first * (p3.second - p1.second) + p3.first * (p1.second - p2.second);
        return v < 0 ? -1 : v > 0 ? 1 : 0;
    };
    
    // find bottom most point, move to 0
    for (int i = 1; i < (int)points.size(); ++i) {
        if (points[i].second < points[0].second || (points[i].second == points[0].second && points[i].first < points[0].first)) swap(points[i], points[0]);
    }

    // sort rest according to bottom most
    sort(points.begin() + 1, points.end(), [&](auto &a, auto &b) {
        int o = orientation(points[0], b, a);
        if (o != 0) return o < 0;

        return distSqd(points[0], a) < distSqd(points[0], b);
    });
    int j = (int)points.size() - 1;
    while (j > 1 && orientation(points[0], points.back(), points[j-1]) == 0) --j;
    reverse(points.begin() + j, points.end());

    // grahm scan
    vector<pair<int,int>> hull;
    for (pair<int,int> p : points) {
        auto hullCmp = [&]() {
            if (hull.size() < 2) return false;
            return orientation(hull[hull.size() - 2], hull.back(), p) < 0;
        };
        while (hullCmp()) hull.pop_back();
        hull.push_back(p);
    }
    if (colinear) return hull;

    // remove colinear points
    while (hull.size() > 2 && orientation(hull[0], hull.back(), hull[hull.size() - 2]) == 0)
        hull.pop_back();
    j = 1;
    for (int i = 2; i < (int)hull.size(); ++i) {
        if (orientation(hull[j-1], hull[j], hull[i]) == 0) hull[j] = hull[i];
        else hull[++j] = hull[i];
    }
    hull.resize(j+1);
    return hull;
}

template <class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};

typedef Point<ll> P;
pair<vector<int>, vector<int>> ulHull(const vector<P>& S) {
	vector<int> Q(S.size()), U, L;
	iota(Q.begin(), Q.end(), 0);                                                                                                                                                                         
	sort(Q.begin(), Q.end(), [&S](int a, int b){ return S[a] < S[b]; }); 
	for (auto &it : Q) {
    #define ADDP(C, cmp) while (C.size() > 1 && S[C[C.size()-2]].cross(S[it], S[C.back()]) cmp 0) C.pop_back(); C.push_back(it);
		ADDP(U, <=); ADDP(L, >=);
	}
	return {U, L}; 
}

vector<int> kactlConvexHull(const vector<P>& S) {
	vector<int> u, l; tie(u, l) = ulHull(S);
	if (S.size() <= 1) return u;
	if (S[u[0]] == S[u[1]]) return {0};
	l.insert(l.end(), u.rbegin()+1, u.rend()-1);
	return l;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<P> points(n);
    for (auto &p : points) {
        cin >> p.x >> p.y;
    }
    cout << kactlConvexHull(points).size() << endl;
}
