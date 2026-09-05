/*
Platinum 1
1210 - Mafia
meta: {"problemId": 1210, "titleKo": "마피아", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "마피아", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Mafia", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 647, "level": 20, "votedUserCount": 96, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.40339994430542, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "flow", "isMeta": false, "bojTagId": 45, "problemCount": 397, "displayNames": [{"language": "ko", "name": "최대 유량", "short": "최대 유량"}, {"language": "en", "name": "maximum flow", "short": "flow"}, {"language": "ja", "name": "最大フロー", "short": "flow"}], "aliases": [{"alias": "dinic"}, {"alias": "dinitz"}, {"alias": "ford"}, {"alias": "fulkerson"}, {"alias": "fordfulkerson"}, {"alias": "디닉"}, {"alias": "디니츠"}, {"alias": "포드풀커슨"}, {"alias": "플로우"}]}, {"key": "mfmc", "isMeta": false, "bojTagId": 167, "problemCount": 102, "displayNames": [{"language": "ko", "name": "최대 유량 최소 컷 정리", "short": "최대 유량 최소 컷 정리"}, {"language": "en", "name": "max-flow min-cut theorem", "short": "mfmc"}, {"language": "ja", "name": "最大フロー最小カット定理", "short": "mfmc"}], "aliases": []}], "metadata": {}}
*/

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;

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

#include <bits/extc++.h>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX >> 2;

struct Dinic {
    using ll = long long;
    using vi = vector<int>;
  
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, (int)adj[b].size(), c, c});
		adj[b].push_back({a, (int)adj[a].size() - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < (int)adj[v].size(); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1) {
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
            }
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		for(int L = 0; L < 31; ++L) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(q.size());
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
    struct CutEdge {
        int from, to;
        ll f, c;
    };
    pair<vector<CutEdge>, vector<bool>> minCut(int s, int t) {
        calc(s, t);
        queue<int> q;
        vector<CutEdge> mc;
        vector<bool> visited(adj.size());
        visited[s] = true;
        q.push(s);
        while (!q.empty()) {
            int from = q.front();
            q.pop();
            for (Edge &e : adj[from]) {
                if (visited[e.to] || (e.oc ? e.flow() == e.oc : adj[e.to][e.rev].flow() == 0)) continue;

                visited[e.to] = true;
                q.push(e.to);
            }
        }
        for (int from = 0; from < (int)adj.size(); ++from) {
            for (Edge &e : adj[from]) {
                if (e.flow() && visited[from] && !visited[e.to])
                    mc.push_back({from, e.to, e.flow(), e.oc});
            }
        }
        return make_pair(mc, visited);
    }
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, m;
    cin >> n >> m;
    int src, dst;
    cin >> src >> dst;
    --src; --dst;

    // use metanodes:
    // V' = V U {m_x :: x in V}
    // E' = {(m_x, y, INF) :: (x, y) in E} U {(x, m_x, cost(x)) :: x in V}
    // m_x = n + x
    Dinic d(n * 2);
    for (int i = 0; i < n; ++i) {
        ll c;
        cin >> c;
        d.addEdge(i, n + i, c);
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        d.addEdge(n + a, b, INF);
        d.addEdge(n + b, a, INF);
    }
    auto &&[mc, visited] = d.minCut(src, n + dst);
    vector<int> res;
    for (Dinic::CutEdge &e : mc) {
        res.push_back(e.from + 1);
    }
    sort(res.begin(), res.end());
    for (int x : res)
        cout << x << " ";
    cout << endl;
}
