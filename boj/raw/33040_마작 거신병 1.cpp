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

    int rows, cols; cin >> rows >> cols;
    int a, b; cin >> a >> b; // a 1s, b 9s

    if (rows > cols + 1) {
        cout << -1 << "\n";
        return 0;
    }

    // since we know a + b == rows * cols, just array of length rows that sum to b where last element < cols
    // can be done by constructing 0,1,2,3,4,... then adding from the back to cols
    vector<int> bs(rows);
    iota(all(bs), 0);
    b -= accumulate(all(bs), 0);
    if (b < 0) {
        cout << -1 << "\n";
        return 0;
    }
    for (int i = (int)bs.size()-1; b && i >= 0; --i) {
        int d = min(b, cols + 1 - rows);
        bs[i] += d;
        b -= d;
    }
    if (b > 0) {
        cout << -1 << "\n";
        return 0;
    }
    for (int x : bs) {
        for (int c = 0; c < cols; ++c) {
            cout << (c < x ? 9 : 1) << " ";
        }
        cout << "\n";
    }
}
