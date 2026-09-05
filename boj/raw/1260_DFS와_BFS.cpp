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

#define all(x) x.begin(), x.end()

void dfs(vector<vector<int>> &adj, vector<bool> &visited, int curr) {
    cout << curr+1 << " ";
    visited[curr] = true;
    for (int next : adj[curr]) {
        if (!visited[next]) dfs(adj, visited, next);
    }
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, m, root;
    cin >> n >> m >> root;
    --root;

    vector<vector<int>> adj(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) sort(all(adj[i]));

    vector<bool> visited(n);
    dfs(adj, visited, root);
    fill(all(visited), 0);
    cout << endl;
    queue<int> q;
    q.push(root);
    visited[root] = true;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr+1 << " ";
        for (int next : adj[curr]) {
            if (!visited[next]) {
                q.push(next);
                visited[next] = true;
            }
        }
    }
    cout << endl;
}
