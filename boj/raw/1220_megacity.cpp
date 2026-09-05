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

    // shortest path on grid
    // optimal to either pass through obstacle from left to right / top to bottom or go around
    // only need to consider grid lines that align with an obstacle's edge (or intersect src/dst)
    // this leaves at most 2002 x 2002 grid
    // dijkstras shortest path on this is straight forward
    vector<int> rows;
    vector<int> cols;
    auto addPt = [&](int r, int c) {
        rows.push_back(r); cols.push_back(c);
    };
    struct jam_t {
        int r1, c1, r2, c2, t;
    };
    pair<int,int> src, dst;
    cin >> src.first >> src.second >> dst.first >> dst.second;
    addPt(src.first, src.second); addPt(dst.first, dst.second);
    int n; cin >> n;
    vector<jam_t> jams(n);
    for (jam_t &j : jams) {
        cin >> j.r1 >> j.c1 >> j.r2 >> j.c2 >> j.t;
        addPt(j.r1, j.c1);
        addPt(j.r2, j.c2);
    }

    // v -> sorted unique pts in v, returns mapping from x in v to rank
    auto unq = [](vector<int> &v) {
        sort(all(v));
        v.resize(distance(v.begin(), unique(all(v))));
        unordered_map<int,int> m;
        for (int i = 0; i < (int)v.size(); ++i) {
            m[v[i]] = i;
        }
        v.push_back(INT_MAX >> 1);
        return m;
    };
    unordered_map<int,int> rmap = unq(rows);
    unordered_map<int,int> cmap = unq(cols);

    // compress coords
    auto compress = [&](int &r, int &c) {
        r = rmap[r];
        c = cmap[c];
    };
    compress(src.first, src.second);
    compress(dst.first, dst.second);
    for (auto &j : jams) {
        compress(j.r1, j.c1);
        compress(j.r2, j.c2);
    }

    // get transitions
    struct trans_t {
        ll tr = 0; // time to get to next row
        ll tc = 0; // time to get to next col
    };
    int nr = (int)rows.size()-1;
    int nc = (int)cols.size()-1;
    // cout << nr << " " << nc << endl;
    // for (int x : rows) cout << x << " "; cout << endl;
    // for (int x : cols) cout << x << " "; cout << endl;
    vector<vector<trans_t>> trans(nr, vector<trans_t>(nc));
    for (int r = 0; r < nr; ++r) {
        ll tr = (ll)(rows[r+1] - rows[r]) * 10LL;
        for (int c = 0; c < nc; ++c) {
            trans[r][c].tr = tr;
            trans[r][c].tc = (ll)(cols[c+1] - cols[c]) * 10LL;
        }
    }
    for (auto &j : jams) {
        for (int r = j.r1+1; r < j.r2; ++r) {
            for (int c = j.c1; c < j.c2; ++c) {
                trans[r][c].tc = (ll)j.t * (ll)(cols[c+1] - cols[c]);
            }
        }
        for (int r = j.r1; r < j.r2; ++r) {
            for (int c = j.c1+1; c < j.c2; ++c) {
                trans[r][c].tr = (ll)j.t * (ll)(rows[r+1] - rows[r]);
            }
        }
    }

    // dijkstras
    vector<vector<ll>> minDist(nr, vector<ll>(nc, INF));
    using dij_t = tuple<ll,int,int>;
    priority_queue<dij_t, vector<dij_t>, greater<dij_t>> q;
    auto check = [&](int br, int bc, ll bt) {
        if (minDist[br][bc] <= bt) return;
        minDist[br][bc] = bt;
        q.emplace(bt, br, bc);
    };
    check(src.first, src.second, 0);
    while (!q.empty()) {
        auto [at, ar, ac] = q.top();
        // cout << at << " " << ar << " " << ac << endl;
        // pause();
        q.pop();
        if (ar == dst.first && ac == dst.second) break;
        if (minDist[ar][ac] < at) continue;
        
        if (ar) check(ar-1, ac, at + trans[ar-1][ac].tr);
        if (ac) check(ar, ac-1, at + trans[ar][ac-1].tc);
        if (ar+1 < nr) check(ar+1, ac, at + trans[ar][ac].tr);
        if (ac+1 < nc) check(ar, ac+1, at + trans[ar][ac].tc);
    }
    cout << minDist[dst.first][dst.second] << "\n";
}
