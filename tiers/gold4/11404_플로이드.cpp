/*
Gold 4
11404 - 플로이드
meta: {"problemId": 11404, "titleKo": "플로이드", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "플로이드", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 29752, "level": 12, "votedUserCount": 256, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.308500051498413, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "shortest_path", "isMeta": false, "bojTagId": 215, "problemCount": 990, "displayNames": [{"language": "ko", "name": "최단 경로", "short": "최단 경로"}, {"language": "en", "name": "shortest path", "short": "shortest path"}, {"language": "ja", "name": "最短経路", "short": "最短経路"}], "aliases": []}, {"key": "floyd_warshall", "isMeta": false, "bojTagId": 31, "problemCount": 193, "displayNames": [{"language": "ko", "name": "플로이드–워셜", "short": "플로이드–워셜"}, {"language": "en", "name": "floyd–warshall", "short": "floyd–warshall"}, {"language": "ja", "name": "ワーシャル–フロイド法", "short": "ワーシャル–フロイド法"}], "aliases": [{"alias": "플로이드"}, {"alias": "플로이드와셜"}, {"alias": "플로이드와샬"}]}], "metadata": {}}
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



int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, m; cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(n, INT_MAX >> 1));
    for (int i = 0; i < n; ++i) mat[i][i] = 0;
    for (int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c; --a; --b;
        mat[a][b] = min(mat[a][b], c);
    }

    // floyd warshall
    for (int k = 0; k < n; ++k) {
        for  (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }
    for (auto &row : mat) {
        for (int x : row) cout << (x == (INT_MAX >> 1) ? 0 : x) << " ";
        cout << "\n";
    }
}
