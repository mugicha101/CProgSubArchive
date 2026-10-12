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

#define MOD 998244353
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

ostream& operator<<(ostream& os, i128 x) {
    if (x < 0) {
        x = -x;
        os << '-';
    }
    static char s[40];
    int i = 0;
    while (x) {
        s[i++] = '0' + x % 10;
        x /= 10;
    }
    if (i == 0) s[i++] = '0';
    while (i) os << s[--i];
    return os;
}

istream& operator>>(istream& is, i128 &x) {
    static string s; is >> s;
    x = 0;
    bool neg = s[0] == '-';
    for (int i = 0; i < s.size(); ++i) {
        x = x * 10 + (s[i] - '0');
    }
    if (neg) x = -x;
    return is;
}


ostream& operator<<(ostream& os, u128 x) {
    static char s[40];
    int i = 0;
    while (x) {
        s[i++] = '0' + x % 10;
        x /= 10;
    }
    if (i == 0) s[i++] = '0';
    while (i) os << s[--i];
    return os;
}

istream& operator>>(istream& is, u128 &x) {
    static string s; is >> s;
    x = 0;
    bool neg = s[0] == '-';
    for (int i = 0; i < s.size(); ++i) {
        x = x * 10 + (s[i] - '0');
    }
    if (neg) x = -x;
    return is;
}

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
pair<T,U> operator-(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}

template <typename T, typename U>
istream& operator>>(istream& is, pair<T, U>& p) {
    return is >> p.first >> p.second;
}

template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

template <typename... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t) {
    os << "(";
    apply([&os](const auto&... args) {
        size_t n = 0;
        ((os << (n++ ? ", " : "") << args), ...);
    }, t);
    return os << ")";
}

template <typename... Args>
istream& operator>>(istream& is, tuple<Args...>& t) {
    apply([&is](auto&... args) {
        ((is >> args), ...);
    }, t);
    return is;
}

template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) {
    os << '{';
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << '}';
}
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream& operator>>(istream &is, T_container &v) {
    for (T &x : v) is >> x;
    return is;
}

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

const ll INF = LLONG_MAX >> 2;

// all primes necessary for the prime factorization of a number <= 100,000
const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 
    53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 
    137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 
    227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313};

bool prime(ll a) { if (a==1) return 0; ll cap = sqrt(a); for (int i=2;i<=cap;++i) if (a%i==0) return 0; return 1; }

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ hash<T2>{}(p.second); }
};

#define EPS 1e-9
#define each(i, x) for (auto &i : x)
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)
#define getx(a) a.first
#define gety(a) a.second


template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
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
	i128 dist2() const { return (i128)x*x + (i128)y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
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

typedef Point<ll> P;
pair<i128,int> hullDiameterCount(vector<P> S) {
	int n = sz(S), j = n < 2 ? 0 : 1;
	pair<i128, array<P, 2>> res({0, {S[0], S[0]}});
    vector<array<P,2>> arr;
	for (int i = 0; i < j; ++i) {
		for (;; j = (j + 1) % n) {
            pair<i128, array<P, 2>> can = {(S[i] - S[j]).dist2(), {S[i], S[j]}};
            if (can.first > res.first) {
                res.first = can.first;
                arr.clear();
                arr.push_back(can.second);
            } else if (can.first == res.first) {
                arr.push_back(can.second);
            }
			if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0)
				break;
		}
    }

    // remove duplicates
    set<tuple<ll,ll,ll,ll>> u;
    for (auto &p : arr) {
        u.emplace(p[0].x, p[0].y, p[1].x, p[1].y);
        u.emplace(p[1].x, p[1].y, p[0].x, p[0].y);
    }

	return {res.first, (int)u.size() >> 1};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    ll n, k; cin >> n >> k;
    vector<Point<ll>> pts(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
    }
    vector<int> ch = convexHull(pts);
    vector<Point<ll>> hull;
    for (int i : ch) hull.push_back(pts[i]);
    auto [dSqd, m] = hullDiameterCount(hull);
    
    // each diameter segment contributes 2 x its length
    // always optimal to pick diameter segments while they exist
    // if out of distinct diameter segments, can form segments of diameter - EPS by permuting diamter segments slightly
    
    // let d = diameter size and m = distinct diameter count
    // we find min c s.t. d * 2 * c >= k if c <= m
    // otherwise we find min c s.t. d * 2 * c > k
    
    // edge case: if diameter is an edge, then we remove it from diameter count since they aren't useable
    for (int i = 0; i < hull.size(); ++i) {
        int j = (i + 1) % hull.size();
        m -= (hull[i] - hull[j]).dist2() == dSqd;
    }

    // cout << dSqd << " " << m << endl;

    // to avoid floats, first we try to satisfy d * 2 * c >= k
    // d^2 * c^2 * 4 >= k^2
    // can bsearch

    ll cLo = 0;
    ll cHi = k * 2;
    i128 kSqd = (i128)k * k;
    auto calcLHS = [&](i128 c) {
        return dSqd * c * c * 4;
    };
    while (cLo != cHi) {
        ll c = (cLo + cHi) >> 1;
        if (calcLHS(c) < kSqd) {
            cLo = c+1;
        } else {
            cHi = c;
        }
    }
    ll c = cLo + (calcLHS(cLo) == kSqd && cLo > m);
    cout << c << "\n";
}