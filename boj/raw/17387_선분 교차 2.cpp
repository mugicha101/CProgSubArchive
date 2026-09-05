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

struct Vec {
    ll x, y;
    Vec(ll x = 0, ll y = 0) : x(x), y(y) {}
    ll dot(Vec o) { return x * o.x + y * o.y; }
    Vec operator*(ll m) { return { x * m, y * m }; }
    Vec operator+(Vec o) { return { x + o.x, y + o.y }; }
    Vec operator-() { return { -x, -y }; }
    Vec operator-(Vec o) { return { x - o.x, y - o.y }; }
    Vec perp() { return { y, -x }; }
    ll magSqd() { return x * x + y * y; }
};
ostream& operator<<(ostream &os, const Vec &v) { return os << '<' << v.x << ", " << v.y << '>'; }

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);
    Vec a1, a2, b1, b2;
    cin >> a1.x >> a1.y >> a2.x >> a2.y >> b1.x >> b1.y >> b2.x >> b2.y;

    // SAT - project endpoints of b onto line parallel to a, see if b contains a's projection
    // do same for line parallel to b
    // if any have separation, then no collision
    auto satCheck = [&](Vec axis) {
        pair<ll,ll> aSpan = { axis.dot(a1), axis.dot(a2) };
        pair<ll,ll> bSpan = { axis.dot(b1), axis.dot(b2) };
        if (aSpan.first > aSpan.second) swap(aSpan.first, aSpan.second);
        if (bSpan.first > bSpan.second) swap(bSpan.first, bSpan.second);
        // cout << "axis: " << axis << " aSpan: " << aSpan << " bSpan: " << bSpan << endl;
        return aSpan.second < bSpan.first || bSpan.second < aSpan.first;
    };
    cout << !(
        satCheck((a2 - a1).perp())
        || satCheck((b2 - b1).perp())
        || satCheck(a2 - a1) // edge case for parallel lines
    ) << "\n";
}
