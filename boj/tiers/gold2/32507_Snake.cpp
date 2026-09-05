/*
Gold 2
32507 - Snake
meta: {"problemId": 32507, "titleKo": "Snake", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Snake", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 21, "level": 14, "votedUserCount": 3, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.809500217437744, "official": true, "tags": [{"key": "backtracking", "isMeta": false, "bojTagId": 5, "problemCount": 656, "displayNames": [{"language": "ko", "name": "백트래킹", "short": "백트래킹"}, {"language": "en", "name": "backtracking", "short": "backtrack"}, {"language": "ja", "name": "バックトラック法", "short": "バックトラック"}], "aliases": [{"alias": "백트래킹"}, {"alias": "퇴각검색"}, {"alias": "퇴각 검색"}]}, {"key": "dfs", "isMeta": false, "bojTagId": 127, "problemCount": 964, "displayNames": [{"language": "ko", "name": "깊이 우선 탐색", "short": "깊이 우선 탐색"}, {"language": "en", "name": "depth-first search", "short": "dfs"}, {"language": "ja", "name": "深さ優先探索", "short": "dfs"}], "aliases": [{"alias": "depth first"}, {"alias": "depthfirst"}]}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}], "metadata": {}}
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

int h2i(char h) {
    return h >= 'a' && h <= 'f' ? h - 'a' + 10 : h - '0';
}

int i2h(int i) {
    return i >= 10 ? 'a' + i - 10 : '0' + i;
}

int ar, ac;

void db(vector<vector<char>> &grid, deque<pair<int,int>> &snake) {
    return;

    int rows = grid.size();
    int cols = grid[0].size();
    vector<string> out(rows, string(cols, '.'));

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            out[r][c] = grid[r][c] ? '+' : '.';
        }
    }
    out[ar][ac] = 'A';

    int v = 0;
    for (auto [r, c] : snake) {
        out[r][c] = i2h(v++);
    }
    for (string &s : out) {
        for (char c : s) cout << c << " ";
        cout << endl;
    }
    cout << endl;
}


// O(2.64^16)
bool dfs(vector<vector<char>> &grid, deque<pair<int,int>> &snake, int t) {
    db(grid, snake);

    auto [fr, fc] = snake.front();
    auto [br, bc] = snake.back();

    // if (t > snake.size() + 1 /* + grid.size() + grid[0].size() */) return false;
    // if (reachable(grid, fr, fc, br, bc)) {
    //     db(grid, snake);
    //     return true;
    // }
    // if (snake.front().first == ar && snake.front().second == ac) return true;

    // move head
    auto check = [&](int r, int c) {
        if ((r == ar && c == ac) || (snake.size() != 2 && r == br && c == bc)) return true;
        if (grid[r][c]) return grid[r][c] == 2;

        grid[br][bc] = 2;
        snake.pop_back();
        grid[r][c] = 1;
        snake.emplace_front(r, c);

        bool res = dfs(grid, snake, t+1);

        grid[r][c] = 0;
        snake.pop_front();
        grid[br][bc] = 1;
        snake.emplace_back(br, bc);
        
        return res;
    };
    return (fr && check(fr-1, fc))
        || (fc && check(fr, fc-1))
        || (fr+1 < grid.size() && check(fr+1, fc))
        || (fc+1 < grid[0].size() && check(fr, fc+1));
}

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    int rows, cols;
    cin >> rows >> cols;

    vector<vector<char>> grid(rows, vector<char>(cols, 0));
    vector<pair<int,int>> snakePos;
    ar = -1;
    ac = -1;
    for (int r = 0; r < rows; ++r) {
        string input;
        cin >> input;
        for (int c = 0; c < cols; ++c) {
            if (input[c] == '.') continue;
            if (input[c] == 'A') {
                ar = r;
                ac = c;
                continue;
            }
            
            int v = h2i(input[c]);
            if (snakePos.size() <= v) snakePos.resize(v+1);
            snakePos[v] = make_pair(r, c);
        }
    }

    deque<pair<int,int>> snake;
    reverse(snakePos.begin(), snakePos.end());
    for (auto &[r, c] : snakePos) {
        snake.emplace_front(r, c);
        grid[r][c] = true;
    }

    cout << (int)dfs(grid, snake, 0) << endl;
    return 0;
}
