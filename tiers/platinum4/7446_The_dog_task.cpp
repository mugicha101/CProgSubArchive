/*
Platinum 4
7446 - The dog task
meta: {"problemId": 7446, "titleKo": "The dog task", "titles": [{"language": "en", "languageDisplayName": "en", "title": "The dog task", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 11, "level": 17, "votedUserCount": 3, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.1818000078201294, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "flow", "isMeta": false, "bojTagId": 45, "problemCount": 397, "displayNames": [{"language": "ko", "name": "최대 유량", "short": "최대 유량"}, {"language": "en", "name": "maximum flow", "short": "flow"}, {"language": "ja", "name": "最大フロー", "short": "flow"}], "aliases": [{"alias": "dinic"}, {"alias": "dinitz"}, {"alias": "ford"}, {"alias": "fulkerson"}, {"alias": "fordfulkerson"}, {"alias": "디닉"}, {"alias": "디니츠"}, {"alias": "포드풀커슨"}, {"alias": "플로우"}]}, {"key": "bipartite_matching", "isMeta": false, "bojTagId": 13, "problemCount": 231, "displayNames": [{"language": "ko", "name": "이분 매칭", "short": "이분 매칭"}, {"language": "en", "name": "bipartite matching", "short": "bipartite matching"}, {"language": "ja", "name": "2部マッチング", "short": "2部マッチング"}], "aliases": []}], "metadata": {}}
*/

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

#define EPS 1e-9
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

inline void madd(int &x, int v) {
    x += v;
    x = x >= MOD ? x - MOD : x;
}


struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f, c, oc;
    };
    vector<vector<Edge>> g;
    vector<ll> ec;
    vector<Edge*> cur;
    vector<vector<int>> hs; vector<int> H;
    vector<int> co;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n), co(2*n) {}

    void addEdge(int s, int t, ll cap, ll rcap=0) {
        if (s == t) return;
        assert(cap>=0);
        g[s].push_back({t, (int)g[t].size(), 0, cap, cap});
        g[t].push_back({s, (int)g[s].size()-1, 0, rcap, rcap});
    }

    void addFlow(Edge& e, ll f) {
        Edge &back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    ll calc(int s, int t) {
        int v = (int)g.size(); H[s] = v; ec[t] = 1;
        co[0] = v-1;
        for (int i = 0; i < v; ++i) cur[i] = g[i].data();
        for (Edge& e : g[s]) addFlow(e, e.c);

        for (int hi = 0;;) {
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            int u = hs[hi].back(); hs[hi].pop_back();
            while (ec[u] > 0)    // discharge u
                if (cur[u] == g[u].data() + (int)g[u].size()) {
                    H[u] = 1e9;
                    for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest]+1)
                        H[u] = H[e.dest]+1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v)
                        for (int i = 0; i < v; ++i) if (hi < H[i] && H[i] < v) --co[H[i]], H[i] = v + 1;
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
        }
    }
    bool leftOfMinCut(int a) { return H[a] >= (int)g.size(); }
    void reset() {
        for (auto &row : g) {
            for (auto &e : row) {
                e.f = 0;
                e.c = e.oc;
            }
        }
        fill(ec.begin(), ec.end(), 0);
        fill(H.begin(), H.end(), 0);
        fill(cur.begin(), cur.end(), nullptr);
        for (auto &v : hs) v.clear();
    }
};

double randDbl() {
    return (double)rand() / (double)RAND_MAX;
}
uint64_t microsecs() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

// [-pi, pi)
inline ld norm(ld a) {
    a = fmod(fmod(a + ROT_HALF, ROT_FULL) + ROT_FULL, ROT_FULL) - ROT_HALF;
    assert(a >= -ROT_HALF && a < ROT_HALF);
    return a;
}
inline ld rad2deg(ld a) {
    return a * 180.L / ROT_HALF;
}

int main() {
    cin.tie()->sync_with_stdio(0);
    cout << fixed << setprecision(12);

    int n, m; cin >> n >> m;
    vector<pair<int,int>> bob(n); for (auto &[x,y] : bob) cin >> x >> y;
    vector<pair<int,int>> pts(m); for (auto &[x,y] : pts) cin >> x >> y;
    
    // figure out which points p_i are reachable by dog as bob travels from bob[i] to bob[i+1] (denoted as b_i)
    // reachable by dog iff dist(bob[i] -> p_i -> bob[i+1]) <= 2*dist(bob[i] -> bob[i+1])
    // bijective bipartite matching from b_i to p_i
    // max flow
    int src = n+m-1;
    int dst = src+1;
    PushRelabel f(dst+1);
    auto dist = [](pair<int,int> a, pair<int,int> b) -> ld {
        a.first -= b.first;
        a.second -= b.second;
        return sqrt((ld)(a.first * a.first + a.second * a.second));
    };
    for (int i = 0; i+1 < n; ++i) {
        pair<int,int> a = bob[i], b = bob[i+1];
        f.addEdge(src, i, 1);
        for (int j = 0; j < m; ++j) {
            pair<int,int> c = pts[j];
            if (dist(a,b) * 2.L < dist(a,c) + dist(c,b)) continue;
            
            f.addEdge(i, n+j-1, 1);
        }
    }
    for (int j = 0; j < m; ++j) f.addEdge(n+j-1, dst, 1);
    f.calc(src, dst);
    vector<pair<int,int>> dog;
    for (int i = 0; i+1 < n; ++i) {
        dog.push_back(bob[i]);
        for (auto &e : f.g[i]) {
            if (e.f != 1) continue;
            dog.push_back(pts[e.dest - n + 1]);
        }
    }
    dog.push_back(bob[n-1]);
    cout << dog.size() << "\n";
    for (auto &[x,y] : dog) cout << x << " " << y << " ";
    cout << "\n";
}
