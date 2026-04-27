/*
Gold 1
11689 - GCD(n, k) = 1
meta: {"problemId": 11689, "titleKo": "GCD(n, k) = 1", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "GCD(n, k) = 1", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 6014, "level": 15, "votedUserCount": 391, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.4209001064300537, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "number_theory", "isMeta": false, "bojTagId": 95, "problemCount": 1889, "displayNames": [{"language": "ko", "name": "정수론", "short": "정수론"}, {"language": "en", "name": "number theory", "short": "number theory"}, {"language": "ja", "name": "整数論", "short": "整数論"}], "aliases": []}, {"key": "euler_phi", "isMeta": false, "bojTagId": 151, "problemCount": 62, "displayNames": [{"language": "ko", "name": "오일러 피 함수", "short": "오일러 피 함수"}, {"language": "en", "name": "euler totient function", "short": "euler phi function"}, {"language": "ja", "name": "euler totient function", "short": "euler phi function"}], "aliases": [{"alias": "오일러 파이"}, {"alias": "토션트"}, {"alias": "eulerphi"}, {"alias": "euler phi"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned int uint;
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
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

#include <bits/stdc++.h>
using namespace std;

struct LCATree {
    vector<vector<int>> children;
    vector<int> parent;
    vector<int> depth;
    vector<int> lift;
    LCATree(vector<vector<int>> &adj, int root = 0) : children(adj.size()), parent(adj.size()), depth(adj.size()), lift(adj.size()) {
        vector<int> anc;
        lift[root] = root;
        build(adj, anc, root);
    }

    void build(vector<vector<int>> &adj, vector<int> &anc, int curr) {
        depth[curr] = (int)anc.size();
        anc.push_back(curr);
        int jump = anc[(int)anc.size() - ((depth[curr] + 1) & (-depth[curr] - 1))];
        for (int next : adj[curr]) {
            if (next == parent[curr]) continue;

            children[curr].push_back(next);
            parent[next] = curr;
            lift[next] = jump;
            build(adj, anc, next);
        }
        anc.pop_back();
    }

    int lca(int a, int b) {
        if (depth[a] > depth[b]) swap(a, b);
        while (depth[b] > depth[a]) {
            b = depth[lift[b]] >= depth[a] ? lift[b] : parent[b];
        }
        while (a != b) {
            bool skip = lift[a] != lift[b];
            a = skip ? lift[a] : parent[a];
            b = skip ? lift[b] : parent[b];
        }
        return a;
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // prime decomp (# primes is O(lgn))
    ll n; cin >> n;
    queue<ll> q;
    q.push(n);
    unordered_set<ll> primeFactors;
    unordered_set<ll> visited;
    while (!q.empty()) {
        ll curr = q.front();
        q.pop();
        if (curr == 1) continue;

        ll d = 2;
        while (d * d <= curr && curr % d) ++d;
        if (d * d > curr) {
            primeFactors.insert(curr);
        } else {
            ll e = curr / d;
            if (visited.insert(d).second) q.push(d);
            if (visited.insert(e).second) q.push(e);
        }
    }

    // euler totient
    __int128_t num = n;
    __int128_t den = 1;
    for (ll p : primeFactors) {
        num *= p - 1;
        den *= p;
    }
    ll res = num / den;
    cout << res << endl;
}
