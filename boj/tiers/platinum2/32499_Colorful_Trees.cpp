/*
Platinum 2
32499 - Colorful Trees
meta: {"problemId": 32499, "titleKo": "Colorful Trees", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Colorful Trees", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 47, "level": 19, "votedUserCount": 2, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.7446999549865723, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "trees", "isMeta": false, "bojTagId": 120, "problemCount": 1920, "displayNames": [{"language": "ko", "name": "트리", "short": "트리"}, {"language": "en", "name": "tree", "short": "tree"}, {"language": "ja", "name": "木", "short": "木"}], "aliases": [{"alias": "trees"}]}, {"key": "dp_tree", "isMeta": false, "bojTagId": 92, "problemCount": 597, "displayNames": [{"language": "ko", "name": "트리에서의 다이나믹 프로그래밍", "short": "트리에서의 다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming on trees", "short": "tree dp"}, {"language": "ja", "name": "木上の動的計画法", "short": "tree dp"}], "aliases": [{"alias": "트리dp"}]}, {"key": "smaller_to_larger", "isMeta": false, "bojTagId": 169, "problemCount": 179, "displayNames": [{"language": "ko", "name": "작은 집합에서 큰 집합으로 합치는 테크닉", "short": "작은 집합에서 큰 집합으로 합치는 테크닉"}, {"language": "en", "name": "smaller to larger technique", "short": "smaller to larger"}, {"language": "ja", "name": "smaller to larger technique", "short": "smaller to larger"}], "aliases": [{"alias": "merge heuristics"}, {"alias": "sack"}, {"alias": "small to large"}, {"alias": "작은거"}, {"alias": "큰거"}]}], "metadata": {}}
*/

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
