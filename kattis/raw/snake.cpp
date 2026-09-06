// 2024-10-06 03:46:01 
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
