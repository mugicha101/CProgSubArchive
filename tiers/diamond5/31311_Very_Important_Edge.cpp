/*
Diamond 5
31311 - Very Important Edge
meta: {"problemId": 31311, "titleKo": "Very Important Edge", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Very Important Edge", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 35, "level": 21, "votedUserCount": 7, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.17140007019043, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "trees", "isMeta": false, "bojTagId": 120, "problemCount": 1920, "displayNames": [{"language": "ko", "name": "트리", "short": "트리"}, {"language": "en", "name": "tree", "short": "tree"}, {"language": "ja", "name": "木", "short": "木"}], "aliases": [{"alias": "trees"}]}, {"key": "disjoint_set", "isMeta": false, "bojTagId": 81, "problemCount": 675, "displayNames": [{"language": "ko", "name": "분리 집합", "short": "분리 집합"}, {"language": "en", "name": "disjoint set", "short": "dsu"}, {"language": "ja", "name": "素集合データ構造", "short": "素集合データ構造"}], "aliases": [{"alias": "union"}, {"alias": "find"}, {"alias": "유니온"}, {"alias": "파인드"}, {"alias": "dsu"}]}, {"key": "mst", "isMeta": false, "bojTagId": 49, "problemCount": 257, "displayNames": [{"language": "ko", "name": "최소 스패닝 트리", "short": "최소 스패닝 트리"}, {"language": "en", "name": "minimum spanning tree", "short": "mst"}, {"language": "ja", "name": "最小全域木", "short": "最小全域木"}], "aliases": []}, {"key": "lca", "isMeta": false, "bojTagId": 41, "problemCount": 224, "displayNames": [{"language": "ko", "name": "최소 공통 조상", "short": "최소 공통 조상"}, {"language": "en", "name": "lowest common ancestor", "short": "lca"}, {"language": "ja", "name": "最下位共通祖先", "short": "lca"}], "aliases": []}], "metadata": {}}
*/

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
