/*
Platinum 4
1014 - No Cheating (Small)
meta: {"problemId": 1014, "titleKo": "컨닝", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "컨닝", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "No Cheating (Small)", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 3133, "level": 17, "votedUserCount": 101, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 2.025899887084961, "official": true, "tags": [{"key": "bitmask", "isMeta": false, "bojTagId": 14, "problemCount": 1027, "displayNames": [{"language": "ko", "name": "비트마스킹", "short": "비트마스킹"}, {"language": "en", "name": "bitmask", "short": "bitmask"}, {"language": "ja", "name": "ビット表現", "short": "ビット表現"}], "aliases": [{"alias": "비트필드"}, {"alias": "비트마스크"}]}, {"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "flow", "isMeta": false, "bojTagId": 45, "problemCount": 397, "displayNames": [{"language": "ko", "name": "최대 유량", "short": "최대 유량"}, {"language": "en", "name": "maximum flow", "short": "flow"}, {"language": "ja", "name": "最大フロー", "short": "flow"}], "aliases": [{"alias": "dinic"}, {"alias": "dinitz"}, {"alias": "ford"}, {"alias": "fulkerson"}, {"alias": "fordfulkerson"}, {"alias": "디닉"}, {"alias": "디니츠"}, {"alias": "포드풀커슨"}, {"alias": "플로우"}]}, {"key": "dp_bitfield", "isMeta": false, "bojTagId": 87, "problemCount": 409, "displayNames": [{"language": "ko", "name": "비트필드를 이용한 다이나믹 프로그래밍", "short": "비트필드를 이용한 다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming using bitfield", "short": "bitfield dp"}, {"language": "ja", "name": "ビットを使用した動的計画法", "short": "ビットdp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "비트마스크"}, {"alias": "비트dp"}]}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

#define MOD 1000000007

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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

int rows, cols;
vector<vector<int>> memo;
bool grid[10][10];

int dfsRow(int, bitset<10>);

int dfsCol(int r, int c, bitset<10> m, bitset<10> nm) {
    if (c == cols) return dfsRow(r+1, nm);

    // skip
    nm[c] = 0;
    int res = dfsCol(r, c+1, m, nm);

    // put
    bool blocked = grid[r][c] || (c >= 0 && (nm[c-1] || m[c-1])) || (c+1 < cols && m[c+1]);
    if (!blocked) {
        nm[c] = 1;
        res = max(res, dfsCol(r, c+1, m, nm) + 1);
    }
    
    return res;
}

int dfsRow(int r, bitset<10> m) {
    if (r == rows) return 0;
    int &res = memo[r][m.to_ulong()];
    if (res != -1) return res;

    return res = dfsCol(r, 0, m, 0);
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);
    
    int tc; cin >> tc;
    while (tc--) {
        cin >> rows >> cols;
        for (int r = 0; r < rows; ++r) {
            string s; cin >> s;
            for (int c = 0; c < cols; ++c) {
                grid[r][c] = s[c] == 'x';
            }
        }

        // n * m <= 100
        // backtracking: optimal packing allows for n * (m/2) seats, so depth is n * (m/2) <= 50
        // each depth has 2 options: place seat at tile, remove seat from tile
        // 2^50 is too large, dp?
        // dp[i][m] = max students added from this row onward given previous row fills mask m
        // dp[n][m] = 0
        // dp[i][m] = max(dp[i+1][nm] + popcount(nm) for all valid nm)
        // valid transition always exists in the form of nm = 0
        // m has at most 2^10 options = 1024
        // i has at most 10 options = 10
        // states: 10 * 1024
        // each state dp[i][m] can transition to dp[i+1][nm] where nm is the assigned seats on the current row
        // this means each state has at most 2^10 = 1024 transitions
        // total transitions at most 2^10 * 2^10 * 10 = 10 * 2^20 = 10485760 < 2 * 10^7
        // memo dp should work
        // result = dp[0][0]

        memo = vector<vector<int>>(rows, vector<int>(1 << cols, -1));
        int res = dfsRow(0, 0);
        cout << res << "\n";
    }
}
