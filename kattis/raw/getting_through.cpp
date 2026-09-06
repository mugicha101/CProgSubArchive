// 2026-08-09 23:16:06 
/*
Platinum 2
9373 - Getting Through
meta: {"problemId": 9373, "titleKo": "복도 뚫기", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "복도 뚫기", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Getting Through", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 472, "level": 19, "votedUserCount": 62, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.44920015335083, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "geometry", "isMeta": false, "bojTagId": 100, "problemCount": 2046, "displayNames": [{"language": "ko", "name": "기하학", "short": "기하학"}, {"language": "en", "name": "geometry", "short": "geom"}, {"language": "ja", "name": "幾何学", "short": "幾何"}], "aliases": []}, {"key": "disjoint_set", "isMeta": false, "bojTagId": 81, "problemCount": 675, "displayNames": [{"language": "ko", "name": "분리 집합", "short": "분리 집합"}, {"language": "en", "name": "disjoint set", "short": "dsu"}, {"language": "ja", "name": "素集合データ構造", "short": "素集合データ構造"}], "aliases": [{"alias": "union"}, {"alias": "find"}, {"alias": "유니온"}, {"alias": "파인드"}, {"alias": "dsu"}]}, {"key": "mst", "isMeta": false, "bojTagId": 49, "problemCount": 257, "displayNames": [{"language": "ko", "name": "최소 스패닝 트리", "short": "최소 스패닝 트리"}, {"language": "en", "name": "minimum spanning tree", "short": "mst"}, {"language": "ja", "name": "最小全域木", "short": "最小全域木"}], "aliases": []}], "metadata": {}}
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

#define MOD 1000000009
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

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
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    }
    os << "]";
    return os;
}

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-12
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

inline void madd(int &x, int v) {
    x += v;
    x = x >= MOD ? x - MOD : x;
}

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
    cin.tie()->sync_with_stdio(0);
    cout << fixed << setprecision(12);
    
    // for circle - circle collision, can squeeze through with radius R iff extending all other circles (and edges) by R has gaps
    // first calculate dist between each circle/wall
    // sort by dist, add edges until connected
    int tc; cin >> tc;
    while (tc--) {
        ll w; cin >> w;
        int n; cin >> n;
        vector<tuple<ll,ll,ll>> circs(n);
        for (auto &[x,y,r] : circs) cin >> x >> y >> r;
        vector<tuple<ld,int,int>> edges;  // (dist, a, b)
        for (int i = 0; i < n; ++i) {
            auto [ax, ay, ar] = circs[i];
            edges.emplace_back(ax - ar, i, n); // left wall id = n
            edges.emplace_back(w - (ax + ar), i, n+1); // right wall id = n+1
            for (int j = i+1; j < n; ++j) {
                auto [bx, by, br] = circs[j];
                ll dx = bx - ax;
                ll dy = by - ay;
                edges.emplace_back(sqrt((ld)(dx * dx + dy * dy)) - (ld)(ar + br), i, j);
            }
        }
        edges.emplace_back(w, n, n+1); // wall - wall
        sort(all(edges));
        UnionFind uf(n+2);
        ld res = 0.L;
        for (int i = 0; i < (int)edges.size() && uf.find(n) != uf.find(n+1); ++i) {
            auto [d, a, b] = edges[i];
            res = d;
            uf.merge(a, b);
        }
        res = max(res * 0.5L, 0.L);
        cout << res << "\n";
    }
}
