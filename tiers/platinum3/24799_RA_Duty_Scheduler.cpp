/*
Platinum 3
24799 - RA Duty Scheduler
meta: {"problemId": 24799, "titleKo": "RA Duty Scheduler", "titles": [{"language": "en", "languageDisplayName": "en", "title": "RA Duty Scheduler", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 11, "level": 18, "votedUserCount": 4, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.4544999599456787, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "flow", "isMeta": false, "bojTagId": 45, "problemCount": 397, "displayNames": [{"language": "ko", "name": "최대 유량", "short": "최대 유량"}, {"language": "en", "name": "maximum flow", "short": "flow"}, {"language": "ja", "name": "最大フロー", "short": "flow"}], "aliases": [{"alias": "dinic"}, {"alias": "dinitz"}, {"alias": "ford"}, {"alias": "fulkerson"}, {"alias": "fordfulkerson"}, {"alias": "디닉"}, {"alias": "디니츠"}, {"alias": "포드풀커슨"}, {"alias": "플로우"}]}, {"key": "bipartite_matching", "isMeta": false, "bojTagId": 13, "problemCount": 231, "displayNames": [{"language": "ko", "name": "이분 매칭", "short": "이분 매칭"}, {"language": "en", "name": "bipartite matching", "short": "bipartite matching"}, {"language": "ja", "name": "2部マッチング", "short": "2部マッチング"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
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

int main() {
    cin.tie()->sync_with_stdio(0);
    cout << fixed << setprecision(12);

    // parametric search on maximum days an RA is scheduled for
    // for fixed max days k, do max flow to determine schedulability
    // bipartite: map RA to at most k days s.t. all days has RA
    // src -(k)-> RA -(1)-> days RA can be scheduled to -(2)-> dst
    // if flow = 2 * # days then schedulable
    // serialization:
    // RA_i = i
    // day_i = m + i
    // src = m + n
    // dst = m + n + 1
    int m, n; cin >> m >> n;
    vector<vector<int>> days(m);
    vector<string> name(m);
    for (int i = 0; i < m; ++i) {
        int d;
        cin >> name[i] >> d;
        days[i].resize(d);
        for (int &x : days[i]) { cin >> x; --x; }
    }
    auto check = [&](int k) {
        int src = m + n;
        int dst = src + 1;
        PushRelabel f(dst + 1);
        for (int i = 0; i < m; ++i) {
            f.addEdge(src, i, k);
            for (int d : days[i]) {
                f.addEdge(i, m + d, 1);
            }
        }
        for (int i = 0; i < n; ++i) {
            f.addEdge(m + i, dst, 2);
        }
        if (f.calc(src, dst) != n * 2) return false;
        
        vector<pair<int,int>> res; // (day, RA)
        for (int i = 0; i < m; ++i) {
            for (auto &e : f.g[i]) {
                if (e.f <= 0 || e.dest < m || e.dest >= m + n) continue;
                assert(e.f == 1);

                res.emplace_back(e.dest - m, i);
            }
        }
        sort(all(res));
        cout << k << "\n";
        for (int i = 0; i < n; ++i) {
            cout << "Day " << (i+1) << ": " + name[res[i*2].second] << " " << name[res[i*2+1].second] << "\n";
        }
        return true;
    };
    int k = 1;
    while (!check(k)) ++k;
}
