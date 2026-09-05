/*
Platinum 5
2887 - SVEMIR
meta: {"problemId": 2887, "titleKo": "행성 터널", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "행성 터널", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "SVEMIR", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 9042, "level": 16, "votedUserCount": 521, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.6784000396728516, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}, {"key": "mst", "isMeta": false, "bojTagId": 49, "problemCount": 257, "displayNames": [{"language": "ko", "name": "최소 스패닝 트리", "short": "최소 스패닝 트리"}, {"language": "en", "name": "minimum spanning tree", "short": "mst"}, {"language": "ja", "name": "最小全域木", "short": "最小全域木"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

// using namespace __gnu_pbds;
// template <class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000007

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
pair<T,U> operator-(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

struct UnionFind {
    vector<int> uf;
    vector<int> rank;
    int comps;
    UnionFind(int size) : uf(size), rank(size), comps(size) {
        iota(uf.begin(), uf.end(), 0);
    }

    int find(int x) {
        if (uf[x] != x) uf[x] = find(uf[x]);
        return uf[x];
    }

    bool merge(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) return false;

        --comps;
        if (ra > rb) {
            uf[rb] = ra;
        } else {
            uf[ra] = rb;
            rank[rb] += rank[ra] == rank[rb];
        }
        return true;
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);
    
    int n; cin >> n;
    vector<ll> px(n);
    vector<ll> py(n);
    vector<ll> pz(n);
    for (int i = 0; i < n; ++i) {
        cin >> px[i] >> py[i] >> pz[i];
    }

    // reduce to 1D for now
    // for A - B - C - D - E
    // C will only ever be connected with B and/or D since B is always closer to A than C and likewise for D - E
    // thus only need to consider edges B - C and C - D for node C
    // this holds for 3 dimensions due to how distance is formulated
    // kurskalls MST on this only requires 6n edges

    vector<tuple<ll,int,int>> edges;
    auto addEdges = [&](vector<ll> &pv) {
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int i, int j) {
            return pv[i] < pv[j];
        });
        for (int i = 1; i < n; ++i) {
            edges.emplace_back(abs(pv[order[i-1]] - pv[order[i]]), order[i-1], order[i]);
        }
    };
    addEdges(px); addEdges(py); addEdges(pz);
    sort(edges.begin(), edges.end());
    ll res = 0;
    UnionFind uf(n);
    for (auto [dist, curr, next] : edges) {
        if (uf.merge(curr, next)) res += dist;
    }
    cout << res << endl;
}
