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

    // n shops (n <= 10^4)
    // want to buy x_i ramen from ith shop (x_i <= 10^4)
    // 3 ops:
    // - cost 3: x_i -= 1
    // - cost 5: x_i, x_{i+1} -= 1
    // - cost 7: x_i, x_{i+1}, x_{i+2} -= 1
    // optimal to maximize 3rd op
    // only 10^8 total
    // greedy: maximize widest ops
    // edge case - 1 2 1 1
    // 1 2 1 1 -7-> 0 1 0 1 -3-> 0 0 0 1 -3-> 0 0 0 0: cost 13
    // 1 2 1 1 -5-> 0 1 1 1 -7-> 0 0 0 0: cost 12
    // if x_{i+1} > x_{i+2} then triple at x_i can cost triple at x_{i+1} while losing potential pairs
    int n; cin >> n;
    vector<int> arr(n); vcin(arr);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        // op 2
        if (i+2 < n && arr[i+1] > arr[i+2]) {
            int a = min(arr[i+1] - arr[i+2], arr[i]);
            res += a * 5;
            arr[i] -= a;
            arr[i+1] -= a;
        }

        // op 3
        if (i+2 < n) {
            int a = min({arr[i], arr[i+1], arr[i+2]});
            res += a * 7;
            arr[i] -= a;
            arr[i+1] -= a;
            arr[i+2] -= a;
        }

        // op 2
        if (i+1 < n) {
            int a = min(arr[i], arr[i+1]);
            res += a * 5;
            arr[i] -= a;
            arr[i+1] -= a;
        }

        // op 1
        res += arr[i] * 3;
        arr[i] = 0;
    }
    cout << res << endl;
}
