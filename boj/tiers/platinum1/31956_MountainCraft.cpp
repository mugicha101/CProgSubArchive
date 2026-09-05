/*
Platinum 1
31956 - MountainCraft
meta: {"problemId": 31956, "titleKo": "MountainCraft", "titles": [{"language": "en", "languageDisplayName": "en", "title": "MountainCraft", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 46, "level": 20, "votedUserCount": 8, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.8478000164031982, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "segtree", "isMeta": false, "bojTagId": 65, "problemCount": 1714, "displayNames": [{"language": "ko", "name": "세그먼트 트리", "short": "세그먼트 트리"}, {"language": "en", "name": "segment tree", "short": "segtree"}, {"language": "ja", "name": "セグメント木", "short": "セグ木"}], "aliases": [{"alias": "구간트리"}, {"alias": "세그트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "lazyprop", "isMeta": false, "bojTagId": 66, "problemCount": 405, "displayNames": [{"language": "ko", "name": "느리게 갱신되는 세그먼트 트리", "short": "느리게 갱신되는 세그먼트 트리"}, {"language": "en", "name": "segment tree with lazy propagation", "short": "lazyprop"}, {"language": "ja", "name": "遅延評価セグメント木", "short": "遅延評価セグ木"}], "aliases": [{"alias": "레이지"}, {"alias": "레이지프로퍼게이션"}, {"alias": "레이지프로파게이션"}, {"alias": "구간트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "coordinate_compression", "isMeta": false, "bojTagId": 161, "problemCount": 314, "displayNames": [{"language": "ko", "name": "값 / 좌표 압축", "short": "값 / 좌표 압축"}, {"language": "en", "name": "value / coordinate compression", "short": "compression"}, {"language": "ja", "name": "value / coordinate compression", "short": "compression"}], "aliases": [{"alias": "zip"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;

const int MOD = 1000000007;
 
typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
// #define endl "\n"

// keeps track of length of covered range of intervals
// lazy prop segtree
struct ItvTree {
    ItvTree *left = nullptr;
    ItvTree *right = nullptr;
    int lx; int rx; // covered range
    int count = 0; // number of times completely covered by an interval
    int subCoverLen  = 0; // length of covered range of children (if count > 0, the true cover is just rx - lx)

    // note: points must be sorted
    ItvTree(vector<int> &points, int begin = 0, int end = -1) {
        if (end == -1) end = points.size() - 1;
        int itvs = end - begin;
        lx = points[begin];
        rx = points[end];
        if (itvs >= 2) {
            int mid = begin + (itvs >> 1);
            left = new ItvTree(points, begin, mid);
            right = new ItvTree(points, mid, end);
        }
    }

    // note: if input values are not valid points, will fail assertion

    // gets cover length of range [l, r]
    int query(int l, int r) {
        if (r <= lx || l >= rx) return 0;
        if (count > 0) return min(r, rx) - max(l, lx);
        if (l <= lx && r >= rx) return subCoverLen;
        assertNonleaf(l, r);
        return left->query(l, r) + right->query(l, r);
    }

    // inserts an interval
    // returns true iff coverLen changed
    bool insert(int l, int r) {
        if (r <= lx || l >= rx) return false;
        if (l <= lx && r >= rx) return ++count == 1;
        assertNonleaf(l, r);
        if (!left->insert(l, r) & !right->insert(l, r)) return false;
        subCoverLen = left->coverLen() + right->coverLen();
        return count <= 0;
    }

    // removes an interval
    // returns true iff coverLen changed
    bool erase(int l, int r) {
        if (r <= lx || l >= rx) return false;
        if (l <= lx && r >= rx) return --count == 0;
        assertNonleaf(l, r);
        if (!left->erase(l, r) & !right->erase(l, r)) return false;
        subCoverLen = left->coverLen() + right->coverLen();
        return count <= 0;
    }

    inline int len() const { return rx - lx; }
    inline bool leaf() const { return !left; }
    inline int coverLen() const { return count > 0 ? len() : subCoverLen; }
    inline void assertNonleaf(int opL, int opR) const {
        if (leaf()) {
            cerr << "is a leaf: [" << lx << "," << rx << "] op range: [" << opL << "," << opR << "]" << endl;
            exit(-1);
        }
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // input
    int q, w; cin >> q >> w;
    map<pair<int,int>, int> idMap; // maps peak (x, y) to its id
    vector<pair<int,int>> peakRanges; // peak id -> range
    vector<bool> enabled; // peak id -> enabled
    set<int> basePoints;
    basePoints.insert(0);
    basePoints.insert(w);
    auto getId = [&](int x, int y) {
        auto it = idMap.find({x, y});
        if (it == idMap.end()) {
            int id = idMap.size();
            idMap[{x, y}] = id;
            int l = max(x - y, 0);
            int r = min(x + y, w);
            peakRanges.emplace_back(l, r);
            basePoints.insert(l);
            basePoints.insert(r);
            enabled.push_back(false);
            return id;
        } else {
            return it->second;
        }
    };
    vector<int> queries(q);
    for (int &id : queries) {
        int x, y; cin >> x >> y;
        id = getId(x, y);
    }

    // construct interval tree
    vector<int> itvPoints(basePoints.begin(), basePoints.end());
    ItvTree itvTree(itvPoints);

    // handle queries
    const ld M = 2.L / (ld)M_SQRT2;
    for (int id : queries) {
        auto [l, r] = peakRanges[id];
        if (enabled[id]) {
            itvTree.erase(l, r);
        } else {
            itvTree.insert(l, r);
        }
        enabled[id] = !enabled[id];
        cout << (ld)itvTree.query(0, w) * M << "\n";
    }
}
