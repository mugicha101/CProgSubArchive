/*
Gold 1
9328 - Keys
meta: {"problemId": 9328, "titleKo": "열쇠", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "열쇠", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Keys", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 6374, "level": 15, "votedUserCount": 393, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.4967000484466553, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}, {"key": "grid_graph", "isMeta": false, "bojTagId": 221, "problemCount": 264, "displayNames": [{"language": "ko", "name": "격자 그래프", "short": "격자 그래프"}, {"language": "en", "name": "grid graph", "short": "grid graph"}], "aliases": []}], "metadata": {}}
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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int tc; cin >> tc;
    while (tc--) {
        int rows, cols; cin >> rows >> cols;
        vector<string> grid(rows+2);
        for (int r = 0; r < rows; ++r) {
            string s; cin >> s;
            grid[r+1] = "." + s + ".";
        }
        grid.front() = string(cols + 2, '.');
        grid.back() = string(cols + 2, '.');
        rows += 2;
        cols += 2;

        string keyStr; cin >> keyStr;
        bitset<32> keys;
        if (keyStr != "0") {
            for (char c : keyStr) keys[c-'a'] = true;
        }

        // flood fill
        using pos_t = pair<int,int>;
        queue<pair<pos_t,char>> q;
        array<vector<pos_t>,26> doorQueues;
        int docs = 0;
        q.emplace(mp(0,0), '.');
        grid[0][0] = '*';
        auto debug = [&]() {
            for (auto &s : grid) cout << s << endl;
            cout << "keys: ";
            for (int i = 0; i < 26; ++i) if (keys[i]) cout << (char)('a'+i);
            cout << endl;
        };

        while (!q.empty()) {
            auto [pos, type] = q.front();
            q.pop();

            if (type >= 'A' && type <= 'Z') {
                // door
                if (keys[type-'A']) q.emplace(pos, '.'); // unlocked, treat as empty
                else doorQueues[type-'A'].emplace_back(pos);
            } else {
                if (type >= 'a' && type <= 'z') {
                    // key
                    if (!keys[type-'a']) {
                        keys[type-'a'] = true;
                        for (auto pos : doorQueues[type-'a'])
                            q.emplace(pos, '.');
                        doorQueues[type-'a'].clear();
                    }
                }

                // doc or free space
                auto check = [&](int r, int c) {
                    if (grid[r][c] == '*') return;

                    q.emplace(mp(r, c), grid[r][c]);
                    grid[r][c] = '*';
                };
                
                docs += type == '$';
                auto [r, c] = pos;
                if (r) check(r-1, c);
                if (c) check(r, c-1);
                if (r+1 < rows) check(r+1, c);
                if (c+1 < cols) check(r, c+1);
            }
        }
        cout << docs << endl;
    }
}
