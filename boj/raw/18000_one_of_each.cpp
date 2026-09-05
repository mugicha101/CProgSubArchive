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

    int n, k; cin >> n >> k;

    // value x must be picked before its last occurance
    // let x's interval be 0 to its last occurance
    // if we pick an x outside of an interval of y where y hasn't been picked yet, our solution will be invalid due to y being missing
    // thus we must pick the minimum x not chosen yet within the shortest interval as our next element
    // if multiple such instances, pick earliest in range

    vector<int> locc(k);
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i]; --arr[i];
        locc[arr[i]] = i;
    }
    set<pair<int,int>> active; // active value, index
    vector<bool> used(k);
    set<int> activeLoccs;
    for (int i = 0; i < k; ++i) activeLoccs.insert(locc[i]);
    int j = 0;
    int p = -1;
    for (int _ = 0; _ < k; ++_) {
        int f = *activeLoccs.begin();
        while (j <= f) {
            int x = arr[j];
            if (!used[x]) active.emplace(x, j);
            ++j;
        }
        int x = -1, i = -2;
        while (i <= p || used[x]) {
            auto v = active.begin();
            x = v->first;
            i = v->second;
            active.erase(v);
        }
        p = i;
        activeLoccs.erase(locc[x]);
        used[x] = true;
        cout << x+1 << " ";
    }
    cout << endl;
}
