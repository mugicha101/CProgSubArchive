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

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // acyclic
    // find the set of edges that are in a longest path
    // can do toposort and track longest distance to reach each vertex as well as which edges are on that
    // trivially, longest path must use longest distance to each vertex in it
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    vector<int> indeg(n);
    vector<int> maxDist(n, 0);
    vector<vector<int>> maxDistEdges(n); // incoming edges on any max dist path to this node
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        adj[a].emplace_back(b, c);
        ++indeg[b];
    }

    // toposort to find max dist paths
    int dest = 0;
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0) q.push(i);
    }
    for (int i = 0; i < n; ++i) {
        int curr = q.front();
        dest = curr;
        q.pop();
        for (auto [next, cost] : adj[curr]) {
            int dist = maxDist[curr] + cost;
            
            if (dist >= maxDist[next]) {
                if (dist > maxDist[next]) {
                    maxDist[next] = dist;
                    maxDistEdges[next].clear();
                }
                maxDistEdges[next].push_back(curr);
            }

            if (--indeg[next] == 0) q.push(next);
        }
    }

    // backwards traversal on each longest path
    int maxPathRoads = 0;
    vector<bool> visited(n);
    q.push(dest);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        maxPathRoads += (int)maxDistEdges[curr].size();
        for (int prev : maxDistEdges[curr]) {
            if (visited[prev]) continue;

            visited[prev] = true;
            q.push(prev);
        }
    }
    cout << maxDist[dest] << endl;
    cout << maxPathRoads << endl;
}
