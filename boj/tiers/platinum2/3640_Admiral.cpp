/*
Platinum 2
3640 - Admiral
meta: {"problemId": 3640, "titleKo": "제독", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "제독", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Admiral", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 930, "level": 19, "votedUserCount": 97, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.572000026702881, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "flow", "isMeta": false, "bojTagId": 45, "problemCount": 397, "displayNames": [{"language": "ko", "name": "최대 유량", "short": "최대 유량"}, {"language": "en", "name": "maximum flow", "short": "flow"}, {"language": "ja", "name": "最大フロー", "short": "flow"}], "aliases": [{"alias": "dinic"}, {"alias": "dinitz"}, {"alias": "ford"}, {"alias": "fulkerson"}, {"alias": "fordfulkerson"}, {"alias": "디닉"}, {"alias": "디니츠"}, {"alias": "포드풀커슨"}, {"alias": "플로우"}]}, {"key": "mcmf", "isMeta": false, "bojTagId": 48, "problemCount": 128, "displayNames": [{"language": "ko", "name": "최소 비용 최대 유량", "short": "최소 비용 최대 유량"}, {"language": "en", "name": "minimum cost maximum flow", "short": "mcmf"}, {"language": "ja", "name": "最小費用最大流問題", "short": "mcmf"}], "aliases": [{"alias": "dinic"}, {"alias": "dinitz"}, {"alias": "ford"}, {"alias": "fulkerson"}, {"alias": "fordfulkerson"}, {"alias": "디닉"}, {"alias": "디니츠"}, {"alias": "포드풀커슨"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;

#define MOD 1000000007

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
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

	void addEdge(int from, int to, ll cap, ll cost = 1) {
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

    // n <= 10^3, m <= 10^4
    // query: min sum cost of 2 distinct paths from a to b
    // mcmf
    // each node v represented by nodes x_v, y_v and edge x_v -> y_v (cost 0, cap 1)
    // each edge (u, v, w) represented by edge y_u -> x_v (cost w, cap 1)
    // edge s -> y_1 (cost 0, cap 2)
    // answer to query (a, b) = mcmf(s, x_n).cost
    // node ids: x_v = v * 2 - 1, y_v = v * 2, s = 0
    int n, m;
    while (cin >> n >> m) {
        MCMF f(n * 2 + 1);
        auto xv = [](int v) {
            return v * 2 - 1;
        };
        auto yv = [](int v) {
            return v * 2;
        };
        for (int v = 1; v <= n; ++v) {
            f.addEdge(xv(v), yv(v), 1, 0);
        }
        f.addEdge(0, 2, 2, 0);
        while (m--) {
            int a, b, w; cin >> a >> b >> w;
            f.addEdge(yv(a), xv(b), 1, w);
        }
        auto [flow, cost] = f.maxflow(0, xv(n));
        cout << cost << "\n";
    }
}
