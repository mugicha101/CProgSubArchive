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

vector<int> convexHull(const vector<P>& S) {
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

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<P> points(n);
        for (P &p : points) cin >> p.x >> p.y;

        vector<int> hull = convexHull(points);
        if (hull.size() == 2LL) {
            cout << points[hull[0]].x << " " << points[hull[0]].y << " " << points[hull[1]].x << " " << points[hull[1]].y << "\n";
            continue;
        }
        auto dist = [&](int a, int b) {
            return (points[hull[b]] - points[hull[a]]).dist2();
        };
        pair<int,int> best = {0,0};
        ll bestDist = 0;
        auto vec = [&](int i) {
            return points[hull[(i+1) % hull.size()]] - points[hull[i]];
        };
        auto check = [&](int i, int j) {
            ll d = dist(i, j);
            if (d <= bestDist) return;

            bestDist = d;
            best = {i, j};
        };
        int j = 1;
        for (int i = 0; i < (int)hull.size(); ++i) {
            // step until cross product is positive or j is i
            P curr = vec(i);
            while (curr.cross(vec(j)) >= 0 && j != i) j = (j+1) % hull.size();

            check(i, j);
            check(i, j == 0 ? (int)hull.size() - 1 : j - 1);
        }
        P a = points[hull[best.first]];
        P b = points[hull[best.second]];
        cout << a.x << " " << a.y << " " << b.x << " " << b.y << "\n";
    }
}
