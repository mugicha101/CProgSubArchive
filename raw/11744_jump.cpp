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

    // randomly generate strings on remaining digits
    // if A has n/2 overlap with S and flipping 2 digits keeps n/2 then 1 dig wrong and 1 dig right otherwise both right or wrong
    // can form graph of components of opposite "rightness" where nodes in component are connected by right/wrong
    // DSU - connect components connected by right or wrong until only 2 remain (start with n components, each op has a 50% chance at adding an edge)
    // either component A should be flipped or component B should be flipped

    // to get to n+500 queries need to ensure information gained every query
    // assign 0 to component A
    // perform queries (i, j) where i in A and j unassigned
    // if in same component, j = A, otherwise j = B
    // n queries
    int n; cin >> n;
    int h = n >> 1;
    const int N = 1000;
    // bitset<N> b; for (int i = 0; i < n; ++i) b[i] = rand() & 1;
    bitset<N> x;
    // int qc = 0;
    auto query = [&]() {
        for (int i = 0; i < n; ++i) cout << x[i];
        cout << "\n";
        cout.flush();
        int r; cin >> r;
        return r;
        // ++qc;
        // int o = 0;
        // for (int i = 0; i < n; ++i) o += x[i] == b[i];
        // if (o == n) cout << "FOUND " << qc << "\n";
        // return (o == n || o == h) ? o : 0;
    };
    int qr = 0;
    while ((qr = query()) == 0) {
        for (int i = 0; i < n; ++i) x[i] = rand() & 1;
    }
    if (qr == n) return 0;

    vector<int> comp(n);
    x[0] = !x[0];
    for (int i = 1; i < n; ++i) {
        x[i] = !x[i];
        qr = query();
        x[i] = !x[i];

        if (qr == n) return 0; // edge case
        comp[i] = qr != 0; // true if in opposite components
    }
    x[0] = !x[0];

    // flip all in 0
    for (int i = 0; i < n; ++i) {
        if (comp[i] == 0) x[i] = !x[i];
    }
    if (query() == n) return 0;

    // flip all in 1
    for (int i = 0; i < n; ++i) x[i] = !x[i];
    query();
}
