// 2024-02-21 23:24:08 
#include <bits/stdc++.h>

using namespace std;
#define INPUT false

typedef long long ll;
typedef long double ld;

typedef pair<int,int> point;
typedef pair<point,point> line;
typedef vector<vector<pair<int,int>>> Adj;
point zeroPoint = make_pair(0,0);
line zeroLine = make_pair(zeroPoint, zeroPoint);

void dfs(Adj &adj, vector<int> &parent, int curr) {
    for (auto &[next, color] : adj[curr]) {
        if (next == parent[curr]) continue;
        parent[next] = curr;
        dfs(adj, parent, next);
    }
}

void invalidate(Adj &adj, vector<bool> &good, vector<int> &parent, int curr) {
    good[curr] = false;
    for (auto &[next, color] : adj[curr]) {
        if (next == parent[curr]) continue;
        invalidate(adj, good, parent, next);
    }
}

// return flags: vroot set below or at (0b01), early exit (0b10)
char dfs2(Adj &adj, vector<bool> &good, vector<int> &parent, int &vroot, bool underVroot, int curr) {
    unordered_map<int, vector<int>> colorMap;
    for (auto &[next, color] : adj[curr])
        colorMap[color].push_back(next);
    char ret = 0b00;
    for (auto &[color, dests] : colorMap) {
        if (dests.size() == 1) continue;
        for (int d : dests) {
            if (d == parent[curr]) {
                // cout << "parent bad " << curr+1 << " " << underVroot << endl;
                if (!good[curr] || !underVroot) {
                    vroot = -1;
                    // cout << "early exit" << endl;
                    return 0b10;
                }
                // cout << "vroot = " << curr+1 << endl;
                vroot = curr;
                ret = 0b01;
            } else if (underVroot && good[curr]) invalidate(adj, good, parent, d);
        }
    }
    for (auto &[next, color] : adj[curr]) {
        if (next == parent[curr]) continue;
        char cret = dfs2(adj, good, parent, vroot, underVroot, next);
        if (cret & 0b10) return 0b10;
        underVroot &= (cret & 0b01) == 0;
    }
    if (!underVroot) ret = 0b01;
    // cout << "ret " << curr << " " << (int)ret << endl;
    return ret;
}

void getGood(Adj &adj, vector<bool> &good, vector<int> &parent, vector<int> &goodArr, int curr) {
    if (good[curr]) goodArr.push_back(curr+1);
    for (auto &[next, color] : adj[curr]) {
        if (next == parent[curr]) continue;
        getGood(adj, good, parent, goodArr, next);
    }
}

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif

    int n;
    cin >> n;
    Adj adj(n);
    for (int i = 1; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }
    vector<int> parent(n, -1);
    dfs(adj, parent, 0);

    // let node x be the intersection of k bad edges
    // any path coming from a good path is fine since can only pick one of the bad edges
    // any children with bad edge is marked bad by dfs (if node already bad ignore)
    // if parent edge is bad then
    // - if node is subtree of current virtual root, make this node new virtual root
    // - else nothing is good
    // if node not in virtual root subtree, is not good
    vector<bool> good(n, true);
    int vroot = 0;
    dfs2(adj, good, parent, vroot, true, 0);
    if (vroot == -1) {
        cout << 0 << endl;
        return 0;
    }
    vector<int> goodArr;
    getGood(adj, good, parent, goodArr, vroot);
    sort(goodArr.begin(), goodArr.end());
    cout << goodArr.size() << endl;
    for (int x : goodArr) cout << x << endl;
}

