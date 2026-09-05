/*
Gold 3
2206 - 벽 부수고 이동하기
meta: {"problemId": 2206, "titleKo": "벽 부수고 이동하기", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "벽 부수고 이동하기", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 33018, "level": 13, "votedUserCount": 377, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.989000082015991, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}, {"key": "grid_graph", "isMeta": false, "bojTagId": 221, "problemCount": 264, "displayNames": [{"language": "ko", "name": "격자 그래프", "short": "격자 그래프"}, {"language": "en", "name": "grid graph", "short": "grid graph"}], "aliases": []}], "metadata": {}}
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

void dfs(vector<pair<char,char>> &nodes, char curr, string &preorder, string &inorder, string &postorder) {
    pair<char,char> desc = nodes[curr - 'A'];
    preorder += curr;
    if (desc.first != '.') dfs(nodes, desc.first, preorder, inorder, postorder);
    inorder += curr;
    if (desc.second != '.') dfs(nodes, desc.second, preorder, inorder, postorder);
    postorder += curr;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int rows, cols; cin >> rows >> cols;
    vector<vector<vector<bool>>> visited(2, vector<vector<bool>>(rows, vector<bool>(cols, false)));
    vector<vector<bool>> walls(rows, vector<bool>(cols));
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            char v; cin >> v;
            walls[r][c] = v == '1';
        }
    }

    queue<tuple<int,int,int>> q;
    visited[0][0][0] = true;
    q.emplace(0, 0, 0);
    int dist = 0;
    auto endReached = [&]() {
        return visited[0][rows-1][cols-1] || visited[1][rows-1][cols-1];
    };
    while (!q.empty() && !endReached()) {
        ++dist;
        for (int qi = (int)q.size(); qi > 0; --qi) {
            auto [b, r, c] = q.front();
            q.pop();
            auto check = [&](int r, int c) {
                int nb = b + walls[r][c];
                if (nb == 2 || visited[nb][r][c]) return;

                visited[nb][r][c] = true;
                q.emplace(nb, r, c);
            };
            if (r) check(r-1, c);
            if (c) check(r, c-1);
            if (r+1 < rows) check(r+1, c);
            if (c+1 < cols) check(r, c+1);
        }

        /*
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                cout << (visited[0][r][c] ? '1' : visited[1][r][c] ? '2' : walls[r][c] ? '#' : '.');
            }
            cout << endl;
        }
        cout << endl;
        */
    }
    cout << (endReached()? dist + 1 : -1) << endl;
}
