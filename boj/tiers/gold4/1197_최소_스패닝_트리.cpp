/*
Gold 4
1197 - 최소 스패닝 트리
meta: {"problemId": 1197, "titleKo": "최소 스패닝 트리", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "최소 스패닝 트리", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 26986, "level": 12, "votedUserCount": 363, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 2.593400001525879, "official": true, "tags": [{"key": "mst", "isMeta": false, "bojTagId": 49, "problemCount": 257, "displayNames": [{"language": "ko", "name": "최소 스패닝 트리", "short": "최소 스패닝 트리"}, {"language": "en", "name": "minimum spanning tree", "short": "mst"}, {"language": "ja", "name": "最小全域木", "short": "最小全域木"}], "aliases": []}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
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
#define sz(x) ((int)x.size())

struct UnionFind {
    vector<int> e;
    int comps;
    UnionFind(int n) : e(n, -1), comps(n) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        --comps;
        return true;
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, k; cin >> n >> k;
    vector<tuple<int,int,int>> edges(k);
    for (auto &[w, a, b] : edges) {
        cin >> a >> b >> w; --a; --b;
    }
    sort(all(edges));
    UnionFind uf(n);
    ll sum = 0;
    for (auto &[w, a, b] : edges) {
        sum += uf.join(a, b) ? w : 0;
    }
    cout << sum << endl;
}
