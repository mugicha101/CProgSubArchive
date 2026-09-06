// 2024-02-18 00:44:12
#include <bits/stdc++.h>

using namespace std;
#define INPUT false
typedef long long ll;
typedef long double ld;

struct Edge {
	int a, b;
	ll w;
	Edge() {}
};

struct UnionFind {
	vector<int> uf;
	UnionFind(int size) {
		uf.resize(size);
		iota(uf.begin(), uf.end(), 0);
	}

	int find(int a) {
		if (uf[a] != a)
			uf[a] = find(uf[a]);
		return uf[a];
	}

	bool merge(int a, int b) {
		int ra = find(a);
		int rb = find(b);
		if (ra == rb)
			return false;
		uf[ra] = rb;
		return true;
	}
};

struct EdgeRef {
	int dst;
	ll w;
	int edgeId;
	EdgeRef(int dst, ll w, int edgeId) : dst(dst), w(w), edgeId(edgeId) {}
	EdgeRef() : EdgeRef(-1, -1, -1) {}
};

typedef vector<vector<EdgeRef>> AdjList;

void constructMST(AdjList& adjList, vector<bool>& inMST, vector<int>& depth, vector<EdgeRef>& parent, int node) {
	for (auto& nb : adjList[node]) {
		if (!inMST[nb.edgeId] || nb.dst == parent[node].dst)
			continue;
		parent[nb.dst].dst = node;
		parent[nb.dst].edgeId = nb.edgeId;
		depth[nb.dst] = depth[node] + 1;
		constructMST(adjList, inMST, depth, parent, nb.dst);
	}
}

int main(int argc, char **argv) {
	// env setup
	ios_base::sync_with_stdio(false);
	cout << setprecision(12) << fixed;
	#if INPUT
	freopen("./input.txt","r",stdin);
	#endif
	
	// input
	int V, E;
	cin >> V >> E;
	AdjList adjList(V);
	vector<Edge> edges(E);
	for (int i = 0; i < E; ++i) {
		cin >> edges[i].a >> edges[i].b >> edges[i].w;
		--edges[i].a;
		--edges[i].b;
	}

	// construct graph
	sort(edges.begin(), edges.end(), [](Edge& e, Edge& f) {
		return e.w < f.w;
	});
	for (int i = 0; i < E; ++i) {
		adjList[edges[i].a].emplace_back(edges[i].b, edges[i].w, i);
		adjList[edges[i].b].emplace_back(edges[i].a, edges[i].w, i);
	}

	// find most vital edge (MVE)

	// kurskalls
	UnionFind uf(V);
	ll mstW = 0;
	vector<bool> inMST(E);
	for (int i = 0; i < E; ++i) {
		Edge& e = edges[i];
		inMST[i] = uf.merge(e.a, e.b);
		mstW += inMST[i] ? e.w : 0;
	}

	// construct MST
	vector<EdgeRef> parent(E);
	vector<int> depth(E, -1);
	depth[0] = 0;
	constructMST(adjList, inMST, depth, parent, 0);

	// find leaving edges for all entering edges
	vector<vector<int>> leavingEdges(E);
	uf = UnionFind(V);
	for (int i = 0; i < E; ++i) {
		if (inMST[i])
			continue;
		Edge& e = edges[i];
		while (true) {
			int ra = uf.find(e.a);
			int rb = uf.find(e.b);
			if (ra == rb)
				break;
			int u = depth[ra] > depth[rb] ? ra : rb;
			leavingEdges[i].push_back(parent[u].edgeId);
			uf.merge(u, parent[u].dst);
		}
	}

	// calc MVE from MST
	ll mveW = mstW;
	for (int i = 0; i < E; ++i) {
		for (int j : leavingEdges[i]) {
			ll w = mstW - edges[j].w + edges[i].w;
			mveW = max(mveW, w);
		}
	}
	cout << mveW << endl;
}
