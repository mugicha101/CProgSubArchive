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

#include <bits/extc++.h> /** keep-include */
// To use most bits rather than just the lowest ones:
struct chash { // large odd number for C
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};
template<typename V>
using fast_unordered_map = __gnu_pbds::gp_hash_table<ll,int,chash>;

struct ColorSet;

int n;
vector<vector<int>> adj;
vector<int> colorTotal;
vector<fast_unordered_map<int>> counters;
vector<ColorSet> colorSets;
vector<ll> res;
fast_unordered_map<int> edgeIndex;

inline ll edgeKey(int a, int b) {
    return (ll)a << 32 | (ll)b;
}

struct ColorSet {
    fast_unordered_map<int> *colorCounter = nullptr;
    ll res;

    void initCounter(fast_unordered_map<int> *counter) {
        colorCounter = counter;
    }

    void initRes() {
        res = 0;
        for (auto &[color, amt] : *colorCounter) {
            res += (ll)amt * (ll)(colorTotal[color] - amt);
        }
    }

    void merge(ColorSet &&other) {
        // small to large merging
        if (other.colorCounter->size() > colorCounter->size()) {
            swap(other.colorCounter, colorCounter); // O(1)
            res = other.res;
        }

        // maintain res
        for (auto &[color, change] : *other.colorCounter) {
            int &amt = (*colorCounter)[color];
            res += (ll)change * (ll)(colorTotal[color] - 2LL * amt - change);
            amt += change;
        }
    }
};

void dfs(int parent, int curr) {
    for (int next : adj[curr]) {
        if (next == parent) continue;

        dfs(curr, next);
        res[edgeIndex[edgeKey(curr, next)]] = colorSets[next].res;
        colorSets[curr].merge(move(colorSets[next]));
    }
}

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    cin >> n;
    adj.resize(n);
    counters.resize(n);
    colorSets.resize(n);
    colorTotal.resize(n);
    res.resize(n-1);
    for (int i = 0; i < n; ++i) {
        colorSets[i].initCounter(&counters[i]);
        int c;
        cin >> c;
        ++colorTotal[c];
        (*colorSets[i].colorCounter)[c] = 1;
    }
    for (int i = 0; i < n; ++i) {
        colorSets[i].initRes();
    }
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edgeIndex[edgeKey(a, b)] = i;
        edgeIndex[edgeKey(b, a)] = i;
    }
    dfs(-1, 0);
    for (long long r : res) cout << r << "\n";
}
