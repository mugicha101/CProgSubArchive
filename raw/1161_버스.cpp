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

    // reduces to scheduling problem - cow = task
    // EDF - if cow at stop has earlier deadline than cow on shuttle, cow on shuttle replaced by cow at stop
    int k, n, c; cin >> k >> n >> c;
    map<int,int> dl; // deadline -> amount
    int p = 0; // number of cows on shuttle
    vector<tuple<int,int,int>> groups(k);
    for (auto &[s, e, m] : groups) cin >> s >> e >> m;
    sort(all(groups));
    int res = 0;
    for (auto &[s, e, m] : groups) {
        while (!dl.empty() && dl.begin()->first <= s) {
            int a = dl.begin()->second;
            res += a;
            p -= a;
            dl.erase(dl.begin());
        }
        dl[e] += m;
        p += m;
        while (p > c) {
            auto it = dl.end();
            --it;
            if (p-c >= it->second) {
                p -= it->second;
                dl.erase(it);
            } else {
                it->second -= p-c;
                p = c;
            }
        }
    }
    res += p;
    cout << res << "\n";
}
