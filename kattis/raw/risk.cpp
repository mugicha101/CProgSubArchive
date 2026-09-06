// 2026-08-09 22:55:16 
/*
Diamond 5
3666 - Risk
meta: {"problemId": 3666, "titleKo": "리스크", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "리스크", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Risk", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 150, "level": 21, "votedUserCount": 27, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.646699905395508, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "binary_search", "isMeta": false, "bojTagId": 12, "problemCount": 1665, "displayNames": [{"language": "ko", "name": "이분 탐색", "short": "이분 탐색"}, {"language": "en", "name": "binary search", "short": "binary search"}, {"language": "ja", "name": "二分探索", "short": "二分探索"}], "aliases": [{"alias": "이분탐색"}, {"alias": "이진탐색"}]}, {"key": "parametric_search", "isMeta": false, "bojTagId": 170, "problemCount": 544, "displayNames": [{"language": "ko", "name": "매개 변수 탐색", "short": "매개 변수 탐색"}, {"language": "en", "name": "parametric search", "short": "parametric search"}, {"language": "ja", "name": "parametric search", "short": "parametric search"}], "aliases": [{"alias": "파라메트릭"}]}, {"key": "flow", "isMeta": false, "bojTagId": 45, "problemCount": 397, "displayNames": [{"language": "ko", "name": "최대 유량", "short": "최대 유량"}, {"language": "en", "name": "maximum flow", "short": "flow"}, {"language": "ja", "name": "最大フロー", "short": "flow"}], "aliases": [{"alias": "dinic"}, {"alias": "dinitz"}, {"alias": "ford"}, {"alias": "fulkerson"}, {"alias": "fordfulkerson"}, {"alias": "디닉"}, {"alias": "디니츠"}, {"alias": "포드풀커슨"}, {"alias": "플로우"}]}], "metadata": {}}
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
        // cout << s/2 << ":" << s % 2 << " " << t << " " << cap << endl;
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


struct MCMF {
	struct edge {
		int from, to, rev;
		ll cap, cost, flow;
	};
	int N;
	vector<vector<edge>> ed;
	vector<int> seen;
	vector<ll> dist, pi;
	vector<edge*> par;

	MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		if (from == to) return;
		ed[from].push_back(edge{ from,to,(int)ed[to].size(),cap,cost,0 });
		ed[to].push_back(edge{ to,from,(int)ed[from].size()-1,0,-cost,0 });
	}

	void path(int s) {
		fill(seen.begin(), seen.end(), 0);
		fill(dist.begin(), dist.end(), INF);
		dist[s] = 0; ll di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({ 0, s });

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (edge& e : ed[s]) if (!seen[e.to]) {
				ll val = di - pi[e.to] + e.cost;
				if (e.cap - e.flow > 0 && val < dist[e.to]) {
					dist[e.to] = val;
					par[e.to] = &e;
					if (its[e.to] == q.end())
						its[e.to] = q.push({ -dist[e.to], e.to });
					else
						q.modify(its[e.to], { -dist[e.to], e.to });
				}
			}
		}
		for(int i = 0; i < N; ++i) pi[i] = min(pi[i] + dist[i], INF);
	}

	pair<ll, ll> maxflow(int s, int t) {
		setpi(s);
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (edge* x = par[t]; x; x = par[x->from])
				fl = min(fl, x->cap - x->flow);

			totflow += fl;
			for (edge* x = par[t]; x; x = par[x->from]) {
				x->flow += fl;
				ed[x->to][x->rev].flow -= fl;
			}
		}
		for (int i = 0; i < N; ++i) for(edge& e : ed[i]) totcost += e.cost * e.flow;
		return {totflow, totcost/2};
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(pi.begin(), pi.end(), INF); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			for (int i = 0; i < N; ++i) if (pi[i] != INF)
			  for (edge& e : ed[i]) if (e.cap)
				  if ((v = pi[i] + e.cost) < pi[e.to])
					  pi[e.to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // want the min border tile to be max
    // bsearch on this min
    // let target min be v
    // split tile into 2:
    // - in_tile_i: units tile i starts with
    // - out_tile_i: units tile i ends with
    // for following, (i, j) must be neighboring tiles you own
    // src -(units[i])-> in_tile_i (represents having units[i] that it can transfer)
    // in_tile_i -(INF)-> out_tile_j (represents tile_i transfering units over minimum of 1 to tile_j)
    // in_tile_i -(INF)-> out_tile_i (represents tile_i keeping its units)
    // out_tile_i -(v)-> dst if i is a border tile (represents tile_i needing v units by end)
    // out_tile_i -(1)-> dst if i is not a border tile (represents tile_i needing 1 unit by end)
    // if max flow = sum of deficiencies from border tiles < min then this min is valid

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> units(n); vcin(units);
        vector<vector<bool>> adj(n, vector<bool>(n)); // adj mat
        vector<bool> isBorder(n);
        for (int i = 0; i < n; ++i) {
            string s; cin >> s;
            for (int j = 0; j < n; ++j) {
                adj[i][j] = s[j] == 'Y';
                isBorder[i] = isBorder[i] || (adj[i][j] && units[i] > 0 && units[j] == 0);
            }
        }
        int totalUnits = accumulate(all(units), 0);

        auto check = [&](int v) {
            int src = n*2;
            int dst = src+1;
            PushRelabel f(dst+1);
            int targetFlow = 0;
            for (int i = 0; i < n; ++i) {
                if (units[i] == 0) continue;

                f.addEdge(src, i * 2, units[i]);
                f.addEdge(i * 2, i * 2 + 1, totalUnits);
                int cap = isBorder[i] ? v : 1;
                targetFlow += cap;
                f.addEdge(i * 2 + 1, dst, cap);
                for (int j = 0; j < n; ++j) if (adj[i][j] && units[j]) f.addEdge(i * 2, j * 2 + 1, totalUnits);
            }
            int flow = f.calc(src, dst);
            // cout << v << " " << flow << " " << targetFlow << endl;
            return flow == targetFlow;
        };
        int l = 1;
        int r = totalUnits;
        while (l != r) {
            int m = (l + r + 1) >> 1;
            if (check(m)) {
                l = m;
            } else {
                r = m-1;
            }
        }
        cout << l << "\n";
    }
}
