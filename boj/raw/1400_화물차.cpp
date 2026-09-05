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

struct Light {
    int nsOffset; // first time ns is on
    int nsPeriod; // length of period spent with ns on (period always starts ns on)
    int totalPeriod; // total length of period

    void set(int ewPeriod, int nsPeriod, bool nsFirst) {
        nsOffset = nsFirst ? 1 : 1 + ewPeriod;
        this->nsPeriod = nsPeriod;
        totalPeriod = nsPeriod + ewPeriod;
    }

    inline bool nsOn(int turn) const { return ((((turn - nsOffset) % totalPeriod) + totalPeriod) % totalPeriod) < nsPeriod; }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    while (true) {
        int rows, cols;
        cin >> rows >> cols;
        if (rows == 0 && cols == 0) break;

        vector<string> grid(rows);
        vector<Light> lights;
        pair<int,int> src;
        pair<int,int> dst;
        for (int r = 0; r < rows; ++r) {
            cin >> grid[r];
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] >= '0' && grid[r][c] <= '9') lights.emplace_back();
                else if (grid[r][c] == 'A') src = make_pair(r, c);
                else if (grid[r][c] == 'B') dst = make_pair(r, c);
            }
        }
        for (Light &l : lights) {
            int idx, ewPeriod, nsPeriod;
            char first;
            cin >> idx >> first >> ewPeriod >> nsPeriod;
            l.set(ewPeriod, nsPeriod, first == '|');
        }
        int turn = 0;
        grid[dst.first][dst.second] = '#';

        queue<pair<int,int>> q;
        q.push(src);
        while (!q.empty() && grid[dst.first][dst.second] == '#') {
            ++turn;
            for (int qi = q.size(); qi > 0; --qi) {
                auto [r, c] = q.front();
                q.pop();
                bool offLight = false;

                auto check = [&](int r, int c, bool ns) {
                    if (grid[r][c] == 'A' || grid[r][c] == '.') return;
                    if (grid[r][c] != '#' && lights[grid[r][c]-'0'].nsOn(turn) ^ ns) {
                        offLight = true;
                        return;
                    }

                    grid[r][c] = 'A';
                    q.emplace(r, c);
                };

                if (r) check(r-1, c, true);
                if (c) check(r, c-1, false);
                if (r+1 < rows) check(r+1, c, true);
                if (c+1 < cols) check(r, c+1, false);
                if (offLight) q.emplace(r, c);
            }
        }
        cout << (grid[dst.first][dst.second] == 'A' ? to_string(turn) : "impossible") << endl;
    }
}
