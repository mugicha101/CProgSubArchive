/*
Gold 4
20040 - Cycle Game
meta: {"problemId": 20040, "titleKo": "사이클 게임", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "사이클 게임", "isOriginal": true}, {"language": "en", "languageDisplayName": "en", "title": "Cycle Game", "isOriginal": false}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 11359, "level": 12, "votedUserCount": 191, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 1.9494999647140503, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "disjoint_set", "isMeta": false, "bojTagId": 81, "problemCount": 675, "displayNames": [{"language": "ko", "name": "분리 집합", "short": "분리 집합"}, {"language": "en", "name": "disjoint set", "short": "dsu"}, {"language": "ja", "name": "素集合データ構造", "short": "素集合データ構造"}], "aliases": [{"alias": "union"}, {"alias": "find"}, {"alias": "유니온"}, {"alias": "파인드"}, {"alias": "dsu"}]}], "metadata": {}}
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

struct UnionFind {
    vector<int> uf;
    vector<int> rank;

    UnionFind(int n) : uf(n), rank(n) {
        iota(all(uf), 0);
    }

    int find(int a) {
        if (uf[a] != a) uf[a] = find(uf[a]);
        return uf[a];
    }

    bool merge(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) return false;

        if (rank[ra] >= rb) {
            rank[ra] += rank[ra] == rank[rb];
            uf[rb] = ra;
        } else {
            uf[ra] = rb;
        }
        return true;
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    // cycle formed when edge connects points in same component
    int n, m; cin >> n >> m;
    UnionFind uf(n);
    int turn = 0;
    for (; turn < m; ++turn) {
        int a, b; cin >> a >> b;
        if (!uf.merge(a, b)) break;
    }
    cout << (turn == m ? 0 : turn + 1) << endl;
}
