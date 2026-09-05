// Title: Ancient Messages
// Problem C from ICPC World Finals 2011

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

template <typename T, size_t N>
ostream& operator<<(ostream& os, const array<T, N>& a) {
    os << "[";
    for (size_t i = 0; i < N; ++i) { 
        os << a[i]; 
        if (i != N - 1) 
            os << ", "; 
    }
    os << "]";
    return os;
}

template <typename T, size_t N>
istream& operator>>(istream& is, array<T, N> &a) {
    for (auto &x : a) {
        is >> x;
    }
    return is;
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
template<typename A, typename B> istream& operator>>(istream &is, pair<A, B> &p) { return is >> p.first >> p.second; }
template<typename T> istream& operator>>(istream &is, vector<T> &v) {
    for (auto &x : v) {
        is >> x;
    }
    return is;
}

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-12
#define each(i, x) for (auto &i : x)
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

bool solve(int tc) {
    int rows = 0, cols; cin >> rows >> cols;
    if (rows == 0) return false;

    cols <<= 2;

    vector<vector<int>> grid(rows, vector<int>(cols));
    for (int r = 0; r < rows; ++r) {
        string s; cin >> s;
        for (int c = 0; c < cols; ++c) {
            int si = c >> 2;
            int sj = 3 - (c & 0b11);
            int v = s[si] >= '0' && s[si] <= '9' ? s[si] - '0' : (s[si] - 'a') + 10;
            grid[r][c] = (v >> sj) & 1;
        }
    }

    auto debug = [&]() {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                cout << grid[r][c];
            }
            cout << endl;
        }
        cout << endl;
    };
    // debug();
    queue<pair<int,int>> q;
    auto start = [&](int r, int c) {
        if (grid[r][c]) return;
        grid[r][c] = 2;
        q.emplace(r,c);
    };
    for (int r = 0; r < rows; ++r) {
        start(r, 0);
        start(r, cols-1);
    }
    for (int c = 0; c < cols; ++c) {
        start(0, c);
        start(rows-1, c);
    }
    while (!q.empty()) {
        auto [r,c] = q.front();
        q.pop();
        auto check = [&](int nr, int nc) {
            if (grid[nr][nc]) return;
            grid[nr][nc] = 2;
            q.emplace(nr,nc);
        };
        if (r) check(r-1, c);
        if (c) check(r, c-1);
        if (r+1 < rows) check(r+1, c);
        if (c+1 < cols) check(r, c+1);
    }
    int nextCid = 3;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] != 1) continue;

            int cid = nextCid++;
            grid[r][c] = cid;
            q.emplace(r,c);
            while (!q.empty()) {
                auto [r,c] = q.front();
                q.pop();
                auto check = [&](int nr, int nc) {
                    if (grid[nr][nc] != 1) return;
                    grid[nr][nc] = cid;
                    q.emplace(nr,nc);
                };
                if (r) check(r-1, c);
                if (c) check(r, c-1);
                if (r+1 < rows) check(r+1, c);
                if (c+1 < cols) check(r, c+1);
            }
        }
    }
    vector<int> numHoles(nextCid);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c]) continue;

            grid[r][c] = 2;
            q.emplace(r,c);
            int enclosingCid = -1;
            while (!q.empty()) {
                auto [r,c] = q.front();
                q.pop();
                auto check = [&](int nr, int nc) {
                    if (grid[nr][nc]) {
                        if (grid[nr][nc] > 2) enclosingCid = grid[nr][nc];
                        return;
                    }
                    grid[nr][nc] = 2;
                    q.emplace(nr,nc);
                };
                if (r) check(r-1, c);
                if (c) check(r, c-1);
                if (r+1 < rows) check(r+1, c);
                if (c+1 < cols) check(r, c+1);
            }
            if (enclosingCid != -1) numHoles[enclosingCid]++;
        }
    }
    const char holeMap[] = {'W', 'A', 'K', 'J', 'S', 'D'};
    string out;
    for (int cid = 3; cid < nextCid; ++cid) {
        out.push_back(holeMap[numHoles[cid]]);
    }
    sort(all(out));
    // debug();
    cout << "Case " << tc << ": " << out << "\n";

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);
    int tc = 0;
    while (solve(++tc));
}
