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

    int n, m, src, dst; cin >> n >> m >> src >> dst;
    --src; --dst;
    auto valid = [n](int x) { assert(x >= 0 && x < n); };
    valid(src); valid(dst);

    vector<vector<tuple<int,int,int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int a, b, f, t;
        cin >> a >> b >> f >> t; --a; --b;
        adj[a].emplace_back(b, f, t);
        adj[b].emplace_back(a, f, t);
    }

    // want to find pareto front of (min fee, min time)
    // equivalent to mapping fee -> min time and keeping only min fee for same min time
    // should be monotonic: min fee increases, min time decreases
    // can do via multiobjective dijkstras and update pareto front
    using pareto_t = map<int,int>; // (min fee, min time)
    vector<pareto_t> minCost(n);
    
    // pareto monotonic property: fee increases, time decreases
    // let (f', t') be back of p and v = (f, t)
    // (f, t) dominates or matches (f', t') if f <= f' and t <= t'
    // O(n)
    auto paretoAdd = [](pareto_t &p, pair<int,int> v) {
        // find last f' <= f to check if v dominated
        auto it = p.upper_bound(v.first);
        if (it != p.begin() && (--it)->second <= v.second) return false;
        
        // remove dominated
        vector<int> del;
        for (auto [f, t] : p) {
            if (v.first <= f && v.second <= t) del.push_back(f);
        }
        for (int x : del) p.erase(x);

        // add v
        p[v.first] = v.second;
        return true;
    };

    // determines whether v = (f, t) in pareto front
    auto inFront = [](pareto_t &p, pair<int,int> v) {
        auto it = p.find(v.first);
        return it != p.end() && it->second == v.second;
    };
    using trans_t = tuple<int,int,int>;
    priority_queue<trans_t, vector<trans_t>, greater<trans_t>> q;
    auto check = [&](int dst, int fee, int time) {
        if (paretoAdd(minCost[dst], mp(fee, time))) q.emplace(dst, fee, time);
    };
    check(src, 0, 0);
    while (!q.empty()) {
        auto [curr,f,t] = q.top();
        q.pop();
        if (!inFront(minCost[curr], mp(f, t))) continue;
        // cout << curr << " " << f << " " << t << endl;

        for (auto &[next, df, dt] : adj[curr]) {
            check(next, f + df, t + dt);
        }
    }
    cout << minCost[dst].size() << endl;
    // for (int i = 0; i < n; ++i) {
    //     cout << i << ": ";
    //     for (auto &p : minCost[i]) cout << p << " ";
    //     cout << endl;
    // }
}
