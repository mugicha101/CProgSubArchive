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
