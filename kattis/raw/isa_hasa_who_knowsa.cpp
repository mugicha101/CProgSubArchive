// 2024-10-22 18:42:26
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

int parents[20][2];
char genes[20][2]; // assigned genes, genes[i] is hidden and is 0 if not reached yet
char best[20]; // best hidden reached
int n;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    unordered_map<string,int> id_map;
    vector<unordered_set<int>> isa;
    vector<vector<int>> adj;
    vector<unordered_set<int>> hasa;
    vector<int> indeg;

    auto get_id = [&](string &s) {
        auto it = id_map.find(s);
        if (it != id_map.end()) return it->second;
        int id = id_map.size();
        id_map[s] = id;
        isa.emplace_back();
        hasa.emplace_back();
        adj.emplace_back();
        indeg.push_back(0);
        isa[id].insert(id);
        return id;
    };

    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        string a, op, b;
        cin >> a >> op >> b;
        int aid = get_id(a);
        int bid = get_id(b);
        if (op == "is-a") {
            isa[aid].insert(bid);
            adj[bid].push_back(aid);
            ++indeg[aid];
        } else {
            hasa[aid].insert(bid);
        }
    }

    // topo to do isa inheritance
    queue<int> q;
    for (int i = 0; i < (int)indeg.size(); ++i) {
        if (indeg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int next : adj[curr]) {
            for (int x : hasa[curr]) hasa[next].insert(x);
            for (int x : isa[curr]) isa[next].insert(x);
            if (--indeg[next]) continue;

            q.push(next);
        }
    }

    // queries
    vector<int> a_has(id_map.size(), 0);
    int nonce = 0;
    for (int i = 0; i < k; ++i) {
        string a, op, b;
        cin >> a >> op >> b;
        int aid = get_id(a);
        int bid = get_id(b);
        bool res = false;
        if (op == "is-a") {
            // check if aid isa bid
            res = isa[aid].contains(bid);
        } else {
            // check if anything aid has includes a value that isa bid
            // can have cycles so need to avoid by keeping a visited list
            queue<int> q;
            q.emplace(aid);
            ++nonce;
            while (!res && !q.empty()) {
                int curr = q.front();
                q.pop();
                for (int next : hasa[curr]) {
                    if (a_has[next] == nonce) continue;

                    a_has[next] = nonce;
                    res |= isa[next].contains(bid);
                    q.push(next);
                }
            }
        }
        cout << "Query " << (i+1) << ": " << (res ? "true" : "false") << endl;
    }
}
